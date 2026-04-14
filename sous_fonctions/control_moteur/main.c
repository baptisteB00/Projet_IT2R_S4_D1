/*------------------------------------
Projet IT2R 2026 S4
Auteurs : Alexandre Ho, Lucas VINCENTI

repris sur base Baptiste Bousset
--------------------------------------
Programme Controle moteur wireless avec rtos
-------------------------------------*/

/* ------------- Bibliotheques -------------------*/
#include "Driver_I2C.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "stdio.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Driver_USART.h"  
#include "cmsis_os2.h"

/*................PIN....................
P0.23 => moteur de la voiture
P2.25 => servo moteur de direction
.......................................*/

volatile uint32_t VAL_PWM_SERVO = 37500;
extern ARM_DRIVER_USART Driver_USART1;
enum sens {AVANT, ARRIERE, STOP_HAUT,STOP_BAS,DESACTIVE};
enum return_vit{vitOK,vitERROR};

int i;

/* ------------ Prototypes des fonctions -----------*/
void init_moteur_motricite(void);
void init_servo_moteur();
enum return_vit control_vitesse(uint8_t val_vitesse);
void direction_roue(int16_t angle);
void control_hacheur(enum sens direction );
void USART_Init(void);

/* ------------ Parametres Threads -----------*/
osThreadId_t ID_Thread_Bluetooth; // Définition de l'identifiant de la tâche 
void Thread_Bluetooth(void const * argument); // Prototype de la fonction de la tâche 
osThreadAttr_t configT1 = {.priority = osPriorityNormal} ;
osMutexId_t mut_bl;
extern GLCD_FONT GLCD_Font_16x24;
int main(void){
	SystemCoreClockUpdate();
	USART_Init();
  init_moteur_motricite();
	
	init_servo_moteur();
	osKernelInitialize();         
	LPC_PWM1->MR2 =500;

	direction_roue(90);
	control_hacheur(AVANT);
	
	GLCD_Initialize();// Initialisation du LCD
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	
	ID_Thread_Bluetooth = osThreadNew((osThreadFunc_t)Thread_Bluetooth, NULL, &configT1);
	
	osKernelStart();        
	for (;;) {}
}
/* --------------------------------------------
Definitions Thread
----------------------------------------------*/
//Thread Nunchuck
void Thread_Bluetooth(void const * argument){
	(void)argument;
	signed char cmd_bluth[3],tab[32],tab2[32];
	while(1){
	osMutexAcquire(mut_bl,osWaitForever);
	Driver_USART1.Receive(cmd_bluth, 3);
		while (Driver_USART1.GetRxCount() == 0);
		osDelay(20);
		
		// Serialisation
		sprintf(tab," S%02X  Dir%d ",cmd_bluth[0],cmd_bluth[1]);
		sprintf(tab2," Vit%d",cmd_bluth[2]);
		// Affichage LCD
		GLCD_DrawString(10,10,tab);
		GLCD_DrawString(10,50,tab2);
		for ( i =0; i>200;i++); // delay 
		
		// Controle Direction
		direction_roue(cmd_bluth[1]);
		// Controle Vitesse
		control_vitesse (cmd_bluth[2]);
		// Controle Sens
		if((cmd_bluth[0] & 0x04) == 0x04){control_hacheur(AVANT);}
		else if((cmd_bluth[0] & 0x04) == 0x00){control_hacheur(ARRIERE);}
	osMutexRelease(mut_bl);
	}
}

/* --------------------------------------------
Definititons Fonctions
----------------------------------------------*/
void USART_Init(void){
		Driver_USART1.Initialize(NULL);
	Driver_USART1.PowerControl(ARM_POWER_FULL);
	Driver_USART1.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		|
							ARM_USART_FLOW_CONTROL_NONE,
							115200);
	Driver_USART1.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART1.Control(ARM_USART_CONTROL_RX,1);

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

