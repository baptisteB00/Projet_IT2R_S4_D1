/*------------------------------------
Projet IT2R 2026 S4
Auteurs :  Carl Roy DESCALLAR-SINOPOLI

repris sur base Baptiste Bousset,Ho Alexandre,Lucas VINCENTI
--------------------------------------
Programme acquisition Trames Bluetooth
-------------------------------------*/

#include "Driver_I2C.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "Board_ADC.h"                  // Board Support:A/D Converter
#include "cmsis_os2.h"                  // CMSIS:RTOS2
#include "Driver_USART.h"
#include "algo.h"
#include <math.h>
#include "constantes.h"


/*................PIN....................
P0.23 => moteur de la voiture
P2.25 => servo moteur de direction
.......................................*/

extern ARM_DRIVER_USART Driver_USART0;

#define DETECTER     1
#define TOUR_COMPLET 1
#define MAX_POINTS 	350

volatile uint32_t VAL_PWM_SERVO = 37500;

enum sens {AVANT, ARRIERE, STOP_HAUT,STOP_BAS,DESACTIVE};
enum return_vit{vitOK,vitERROR};

void init_moteur_motricite(void);
void init_servo_moteur();

enum return_vit control_vitesse(uint8_t val_vitesse);
void direction_roue(int16_t angle);
void control_hacheur(enum sens direction );

void USART0_Init(void);

void Init_Moteur_Lidar(void);
void Allumer_Moteur_Lidar(void);

void TacheControlMoteur(void);

void TacheEnvoiRecept (void);
void TacheTraitement (void);

osThreadId_t ID_TacheLidar, ID_Envoie_et_Reception, ID_TacheTraitement, ID_DataStock ,ID_TacheControlMoteur;
osMessageQueueId_t MSQ_BAL_DATA_UART, MSQ_BAL_DATA, MSQ_BAL_BLUETOOTH, MSQ_BAL_STOCK;

int16_t LUT_TRIGO_INT[NB_LUT]; // Tableau global (à la place de float LUT_TRIGO) /////////prendre ca

typedef struct{
	unsigned short angle_q6;
	unsigned short distance_q2;
} DataBrut;

typedef struct{
	char reception[5];
} DataRecept;


typedef struct{
	char flag;
	unsigned short distance_mm, angle_degree;
} DataLidar;

void UART_Callback_Lidar(unsigned int event){
	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE) osThreadFlagsSet(ID_Envoie_et_Reception, 0x0001);
}

void USART0_Init(void){
	Driver_USART0.Initialize(NULL);
	Driver_USART0.PowerControl(ARM_POWER_FULL);
	Driver_USART0.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		|
							ARM_USART_FLOW_CONTROL_NONE,
							115200);
	Driver_USART0.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART0.Control(ARM_USART_CONTROL_RX,1);

}

void TIMER0_IRQHandler(void){
	volatile static char stat = 0 ; // variable servant a savoir si l'ont est a l'etat haut ou bas
	LPC_TIM0->IR = 1; // baissse le flag

	if (stat == 1 ){
	 LPC_TIM0->MR0 = 500000 - VAL_PWM_SERVO;// temps a l'etat bas
	}
	else
	{
		LPC_TIM0->MR0 = VAL_PWM_SERVO; //temps a l'etat haut
	}
	
	stat ^=1;// change de l'etat haut vers bas ou vis versa
	LPC_GPIO3->FIOPIN3 ^= (1<<2); // change la valeur de P3.26 pour realiser la PWM
	
}

int main(void){

	USART0_Init();
	Init_Moteur_Lidar();
	
	SystemCoreClockUpdate();
	osKernelInitialize();
	
	MSQ_BAL_DATA_UART = osMessageQueueNew(10, sizeof(DataRecept),NULL);
	MSQ_BAL_DATA 		 =  osMessageQueueNew(10, sizeof(DataLidar), NULL);
	MSQ_BAL_BLUETOOTH = osMessageQueueNew(10, sizeof(DataBrut), NULL);
	MSQ_BAL_STOCK 	  = osMessageQueueNew(10, sizeof(DataLidar), NULL);

	ID_Envoie_et_Reception = osThreadNew ( (osThreadFunc_t) TacheEnvoiRecept , NULL , NULL) ;
	ID_TacheTraitement 		 = osThreadNew ( (osThreadFunc_t) TacheTraitement  , NULL , NULL) ;
	ID_TacheControlMoteur	 = osThreadNew ( (osThreadFunc_t) TacheControlMoteur,NULL ,NULL);
	//ID_DataStock					 = osThreadNew ( (osThreadFunc_t) thread_DataStock 	 , NULL	, &configDataStock);
	
	osKernelStart();                      // Start thread execution

}

void init_servo_moteur(){
		LPC_GPIO3->FIODIR3|=(1<<2); // active la sortie utiliser par l'interuption du timer
		// Validation des 4 TIMERS   
		LPC_SC->PCONP = LPC_SC->PCONP | 0x00C00006;   
	
		LPC_TIM0->PR = 0;  // le registre PR prend la valeur du prescaler
		LPC_TIM0->MR0 = 499999;    // debut le timer a 50hz
		LPC_TIM0->MCR=LPC_TIM0->MCR | 0x00000003; // active le reset on mr0 et les interuptions
	
		LPC_TIM0->TCR = 1;  // active le timer
		
		NVIC_SetPriority(TIMER0_IRQn,0);//active l'interuption sur MR0
		NVIC_EnableIRQ(TIMER0_IRQn);// met la priorite maximal sur l'interruption de MR0
}

//interruption gerant la PWM du servo moteur

void TacheControlMoteur(void){
	
	init_moteur_motricite();
	init_servo_moteur();
	ADC_Initialize();
	LPC_PWM1->MR2 = 500;
	direction_roue(0);
	control_hacheur(AVANT);
	
	DistancesZones distance;
	commande_voiture commandes = {0.0, 0.0};
	remplir_liste_couple(NB_VITESSE_DWA, NB_ANGLE_DWA);
	
	DataLidar DataStock;
	/*
	for (int i = 0; i < NB_LUT; i++)/////////////////////////////////////////
	{
			// On calcule le float, on le multiplie par l'échelle Q15, et on force la conversion en int16_t
			LUT_TRIGO_INT[i] = (int16_t)(cos((float)i / (NB_LUT - 1) * M_PI/2) * 32767.0f);
	}*/
	
		while (1){
				// osMessageQueueGet(MSQ_BAL_DATA, &DataStock, NULL, osWaitForever);
			/*
			  LidarScan lidarscan ;////////////////////////////////////
        lidarscan.nb_mesures = LIDAR_NB_RAYON;/////////////////////////////////////////
        //lidarscan.distances = car.Lidar.distances;///////////////////////////////////
        distance = ALGO_analyser_zones_moyenne(&lidarscan);//////////////////////////////////////////////////////////////////////////////////////////////////////uniquement V1 v2
        ALGO_decision_V2(&distance,&commandes);//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			*/
			
			direction_roue(-15);
			control_vitesse(20);
			
/*--------------------------------Qlqch ici-------------------------------------------------------*/	
/*		// Reception Bluetooth
		Driver_USART1.Receive(cmd_bluth, 3);
		while (Driver_USART1.GetRxCount() == 0);
		
		direction_roue((valeur * 180.0f)-90);
		//control_vitesse(valeur*100);
		
		if((LPC_GPIO1->FIOPIN & (1<<23))==1<<23){
			control_hacheur(ARRIERE);
		}else if ((LPC_GPIO1->FIOPIN & (1<<25))==1<<25){
			control_hacheur(AVANT);
		}
		// Controle Direction
//		if(cmd_bluth[1] == 0x7F){direction_roue(0);}
//		else if(cmd_bluth[1] == 0x80){direction_roue(60);}
//		else{direction_roue(30);}
		
		direction_roue(cmd_bluth[1]+30);
		
		control_vitesse (cmd_bluth[2]);
		// Controle Vitesse
//		if (cmd_bluth[2]== 0x7F){control_hacheur(AVANT);}
//		else if (cmd_bluth[2]== 0x80){control_hacheur(ARRIERE);}
		if((cmd_bluth[0] & 0x04) == 0x04){control_hacheur(AVANT);}
		else if((cmd_bluth[0] & 0x04) == 0x00){control_hacheur(ARRIERE);}
		//else{control_hacheur(DESACTIVE);}*/
/*----------------------------------------Qqlch la--------------------------------------*/
	}
}

void TacheTraitement (void){
	
	DataLidar DataEnvoi;
	DataRecept DataRecept;
	DataBrut DataBrut;
	
	char LSB_angle, MSB_angle, LSB_distance, MSB_distance;
	char octet_0;
	
	unsigned short angle_q6, distance_q2; 
	
	while(1)
	{
		osMessageQueueGet(MSQ_BAL_DATA_UART, &DataRecept, NULL, osWaitForever);	// On reçoit le BAL du thread EnvoiRecept 
		
		octet_0 = DataRecept.reception[0];				// Octet contenant le drapeau 
		LSB_angle = DataRecept.reception[1];			// Octet contenant la partie LSB de l'angle	
		MSB_angle = DataRecept.reception[2];      // Octet contenant la partie MSB de l'angle     
		LSB_distance = DataRecept.reception[3];		// Octet contenant la partie LSB de la distance
		MSB_distance = DataRecept.reception[4];		// Octet contenant la partie MSB de la distance
			
		angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  		// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits -> Protocole pour précision
		distance_q2 =  (MSB_distance << 8) | LSB_distance ;	// On décale le MSB de 8 et on effectue un OU pour que les deux OCTETS deviennent un SHORT 
			
		DataBrut.angle_q6 = angle_q6;					// Pour envoyer l'angle brut (sans division) au thread Bluetooth
		DataBrut.distance_q2 = distance_q2; 	// Pour envoyer la distance brut (sans division) au thread Bluetooth
		
		DataEnvoi.flag = octet_0 & 0x01;					// Masquage pour isoler le premier bit, qui correspond au flag (pour chaque tour = 1)
		DataEnvoi.angle_degree = angle_q6 / 64;		// Divisé par 64 car la doc le précise
		DataEnvoi.distance_mm = distance_q2 / 4;	// Divisé par 4 car la doc le précise	

		osMessageQueuePut(MSQ_BAL_DATA, &DataEnvoi, NULL, osWaitForever);			// BAL pour le thread LED
		//osMessageQueuePut(MSQ_BAL_STOCK, &DataEnvoi, NULL, osWaitForever);			// BAL pour le thread DataStock
		//osMessageQueuePut(MSQ_BAL_BLUETOOTH, &DataBrut, NULL, osWaitForever);	// BAL pour le thread Bluetooth
	}
}

void TacheEnvoiRecept (void) {
	
	DataRecept DataRecept;
	
	char cmd[2];
	char descriptor[7];
	unsigned int flag;
	
	cmd[0] = 0xA5;	 															// Deux octets à envoyer pour que le Lidar comprenne que c'est bien la commande SCAN -> Protocole p.16 pour détails
	cmd[1] = 0x20;
	
	Allumer_Moteur_Lidar(); 
	
	osDelay(500); 																// Le temps que le moteur s'allume
	
	Driver_USART0.Send(cmd, 2);										// Envoie des commandes CMD pour activer le SCAN
	while(Driver_USART0.GetTxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets DESCRIPTOR
	
	while(1)
	{
		flag = osThreadFlagsWait(0x0001, osFlagsWaitAll, osWaitForever);	
		if (flag == 0x0001) Driver_USART0.Receive(DataRecept.reception, 5); 	// On receptionne les paquets RECEPTION
		osMessageQueuePut(MSQ_BAL_DATA_UART, &DataRecept, NULL, osWaitForever);
	}
}

void thread_DataStock(void *argument) // Tache pour Baptiste 
{
	(void)argument;
	
	DataLidar DataStock;
	
	unsigned short angle[ MAX_POINTS ];
	unsigned short distance[ MAX_POINTS ];
	static int i = 0;
	
	while(1)
	{
		osMessageQueueGet(MSQ_BAL_STOCK, &DataStock, NULL, osWaitForever); // Reception du BAL du thread traitement
		
		if(i < MAX_POINTS)
		{
			angle[i] = DataStock.angle_degree;
			distance[i] = DataStock.distance_mm;
			i++;
		}
		else { i = 0; }
	}
}

void Init_Moteur_Lidar(void){LPC_GPIO2->FIODIR0 |= 0x20;}
void Allumer_Moteur_Lidar(void){LPC_GPIO2->FIOPIN0 |= 0x20;}

void init_moteur_motricite(void){
LPC_SC->PCONP |= 0x00000040; // Enable PWM1
LPC_PINCON->PINSEL7 |= (3<<18); // Broches P3.25
LPC_PWM1->PR = 0; // Prescaler
LPC_PWM1->MR0 = 2499; // MR0+1=25000, comptage à 10kHz
LPC_PWM1->MCR |= 0x00000002; // RAZ on MR0
LPC_PWM1->LER |= 0x0000000F; // Autorise Modification PWM en cours de fonctionnement
LPC_PWM1->PCR |= 0x00000E00; // Autorise les sorties PWM1/2/3
LPC_PWM1->TCR |= 0x00000001; // Démarrage Timer
LPC_PWM1->MR2=0; // desactive la vitesse au debut 
	
LPC_GPIO0->FIODIR |= (1<<19)|(1<<18)|(1<<17)|(1<<16);
	
}

// valeur possible AVANT, ARRIERE, STOP_HIGH, STOP_LOW
/* pinout
EN A : P0.19
EN B : P0.18 

IN A : P0.16
IN B : P0.17
*/

void control_hacheur(enum sens direction) {
    switch (direction){
        case AVANT:
            // Active les 4 quadrants (pins 18 et 19) et IN A : HAUT (pin 16)
            LPC_GPIO0->FIOSET = (1<<19) | (1<<18) | (1<<16);
            
            // IN B : BAS (pin 17)
            LPC_GPIO0->FIOCLR = (1<<17);
            break;
        
        case ARRIERE:
            // Active les 4 quadrants (pins 18 et 19) et IN B : HAUT (pin 17)
            LPC_GPIO0->FIOSET = (1<<19) | (1<<18) | (1<<17);
            
            // IN A : BAS (pin 16)
            LPC_GPIO0->FIOCLR = (1<<16);
            break;
        
        default:
        case STOP_BAS:
            // IN A et IN B BAS (pins 16 et 17)
            LPC_GPIO0->FIOCLR = (1<<17) | (1<<16);
            break;
    
        case STOP_HAUT:
            // IN A et IN B HAUT (pins 16 et 17)
            LPC_GPIO0->FIOSET = (1<<17) | (1<<16);
            break;
        
        case DESACTIVE:
            // Désactive les 4 quadrants (pins 18 et 19)
            LPC_GPIO0->FIOCLR = (1<<19) | (1<<18);
            break;
    }
} 


//valeur entre 0 et 100
enum return_vit control_vitesse(uint8_t val_vitesse){
	if(val_vitesse<=100 && val_vitesse>=0){
	LPC_PWM1->MR2 = (uint16_t)(val_vitesse * 2499.0)/100.0; //*24.99 car MR0 entre 0 et 2499
		return vitOK;
	}else {
		LPC_PWM1->MR2 =0;
		return vitERROR;
	}

}

//angle : valeur en degrees
void direction_roue(int16_t angle){

	if ( angle <= 90 && angle >= -90){
	
		angle += 90; // value between 0 and 180 
		VAL_PWM_SERVO = ((angle) * 25000.0/180)+25000; // valeur entre 25 000 (1ms) and 50 000 (2ms)
	}
}

