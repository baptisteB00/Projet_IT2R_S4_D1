/* --------------------------------------------------------------------------
 * Projet BUT2 Semestre 4 : L'embarqué pour véhicule intelligent et communicant 
 * Auteurs : Groupe IT2R1
 * 
 * Objectif de ce code : Analyse environnement à l'aide d'un lidar
 * 
 * Utilisation d'un Lidar A2M6 -> Voir protocole/datasheet sur le site SLAMTEC (dans support)
 * Programmé sur carte KEIL
 * -------------------------------------------------------------------------- */

#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART
#include "Board_GLCD.h"                 // Board Support:Graphic LCD
#include "GLCD_Config.h"                // Board Support:Graphic LCD
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

extern ARM_DRIVER_USART Driver_USART0;
extern ARM_DRIVER_USART Driver_USART1;
extern GLCD_FONT GLCD_Font_16x24;				
extern GLCD_FONT GLCD_Font_6x8; 

#define LED_P1_28 	0
#define LED_P1_29 	1
#define LED_P1_31 	2
#define LED_P2_2 		3
#define LED_P2_3 		4
#define LED_P2_4 		5
#define LED_P2_6 		6

#define ANGLE_0 		0.0
#define ANGLE_45 		45.0
#define ANGLE_90 		90.0
#define ANGLE_135 	135.0
#define ANGLE_180 	180.0
#define ANGLE_225 	225.0 
#define ANGLE_270 	270.0
#define ANGLE_315 	315.0
#define ANGLE_360 	360.0

#define DETECTER     1
#define TOUR_COMPLET 1

#define MAX_POINTS 350


/*-------------- Prototypes des fonctions --------------*/

void Init_UART_Lidar(void);
void SCAN(void);
void Analyse_environnement_4_secteurs(float distance_mm, float angle_degree, char flag);
void Analyse_environnement_8_secteurs(float distance_mm, float angle_degree, char flag);
void Init_LED(void);
void Init_Bluetooth(void);
void Bluetooth_C_Pyt(unsigned short angle_q6, unsigned short distance_q2);
void Allumer_LED(char Num_LED);
void Eteindre_LED(char Num_LED);
void Init_Moteur_Lidar(void);
void Allumer_Moteur_Lidar(void);


void tache_lidar (void *argument);

/*-------------- Variables globales --------------*/

char detect_obst_0_90 = 0, detect_obst_90_180 = 0, detect_obst_180_270 = 0, detect_obst_270_360 = 0; 			// 360 / 4

char detect_obst_0_45 = 0, detect_obst_45_90 = 0, detect_obst_90_135 = 0, detect_obst_135_180 = 0, 				// 360 / 8
		 detect_obst_180_225 = 0, detect_obst_225_270 = 0, detect_obst_270_315 = 0, detect_obst_315_360 = 0; 

unsigned short angle[ MAX_POINTS ], dist[ MAX_POINTS ]; 

osThreadId_t ID_TacheLidar ; 

void tache_lidar (void *argument) {
  (void)argument;
	
	char cmd[2];
	char descriptor[7];
	char reception[5];
	char LSB_angle, MSB_angle, LSB_distance, MSB_distance;
	char flag, octet_0;
	
	unsigned short angle_q6, distance_q2; 
	
	float angle_degree, distance_mm;
	
	cmd[0] = 0xA5;	 															// Deux octets à envoyer pour que le Lidar comprenne que c'est bien la commande SCAN -> Protocole p.16 pour détails
	cmd[1] = 0x20;
	
	Allumer_Moteur_Lidar(); 
	
	osDelay(500);
	
	Driver_USART0.Send(cmd, 2);										// Envoie des commandes CMD pour activer le SCAN
	while(Driver_USART0.GetTxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets DESCRIPTOR
	
  while(1)
	{
		
			Driver_USART0.Receive(reception, 5); 				// On receptionne les paquets RECEPTION
			while(Driver_USART0.GetRxCount()				< 5); 
			
			octet_0 = reception[0];				
			LSB_angle = reception[1];
			MSB_angle = reception[2];             
			LSB_distance = reception[3];
			MSB_distance = reception[4];
			
			angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  					// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits -> Protocole pour précision
			distance_q2 =  (MSB_distance << 8) | LSB_distance ;	
			
			flag = octet_0 & 0x01;																		// Masquage pour isoler le premier bit, qui correspond au flag (pour chaque tour = 1)
			angle_degree = angle_q6 / 64.0;
			distance_mm = distance_q2 / 4.0;
			
			Analyse_environnement_4_secteurs(distance_mm, angle_degree, flag);
	}
}

osThreadAttr_t config_Tache_Lidar = { .priority = osPriorityNormal };

/*-------------- Programme principal --------------*/

int main()
{
	SystemCoreClockUpdate();
	osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	Init_UART_Lidar();
	Init_Bluetooth();
	Init_LED();
	Init_Moteur_Lidar();
	
	//SCAN();
	
	

	
	ID_TacheLidar = osThreadNew ( (osThreadFunc_t) tache_lidar , NULL , &config_Tache_Lidar) ;
	
	osKernelStart();                      // Start thread execution
	return 0; 
}

/* --------------------------------------------------------
 * Fonction : void Init_UART_Lidar(void)
 *
 * Initialisation de l'UART0 pour le lidar (P0.2 (RX)/ P0.3 (TX))
 *
 * Fonctionne avec 8 bits de donnée, 1 bit de stop, pas de parité et travaille avec 115 200 bps
 *-------------------------------------------------------*/

void Init_UART_Lidar(void)
{
	Driver_USART0.Initialize(NULL);			
	Driver_USART0.PowerControl(ARM_POWER_FULL);
	Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS | 
												ARM_USART_DATA_BITS_8 | 
												ARM_USART_STOP_BITS_1 | 
												ARM_USART_PARITY_NONE | 
												ARM_USART_FLOW_CONTROL_NONE , 115200); 
	
	Driver_USART0.Control(ARM_USART_CONTROL_RX, 1);			// réception
	Driver_USART0.Control(ARM_USART_CONTROL_TX, 1);			// transmission
}

/* --------------------------------------------------------
 * Fonction : void SCAN(void)
 *
 * Request packet (2 octets): 0xA5, 0x20
 * Response descriptor (7 octets): 0xA5, 0x5A, 0x05, 0x00, 0x00, 0x40, 0x81
 * Data response length : 5 octets 
 * Response mode : Multiple
 * 
 * Envoie des commandes et reception des données du Lidar dont l'angle et la distance (et autres),
 * Ajout de fonction Analyse_environnement pour tester et afficher avec des LEDS
 *
 * Pour plus de détails sur le fonctionnement -> Protocole SLAMTEC page 16
 *-------------------------------------------------------*/

void SCAN(void)
{
	char cmd[2];
	char descriptor[7];
	char reception[5];
	char LSB_angle, MSB_angle, LSB_distance, MSB_distance;
	char flag, octet_0;
	
	unsigned short angle_q6, distance_q2; 
	
	int i;
	
	float angle_degree, distance_mm;
	
	cmd[0] = 0xA5;	 															// Deux octets à envoyer pour que le Lidar comprenne que c'est bien la commande SCAN -> Protocole p.16 pour détails
	cmd[1] = 0x20;
	
	Allumer_Moteur_Lidar(); 
	
	for(i = 0; i < 2000000; i++); 								// Delais pour laisser au moteur de tourner 
	
	Driver_USART0.Send(cmd, 2);										// Envoie des commandes CMD pour activer le SCAN
	while(Driver_USART0.GetTxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets DESCRIPTOR
	while(Driver_USART0.GetRxCount() < 7);
	
	while(1)
	{		
			Driver_USART0.Receive(reception, 5); 				// On receptionne les paquets RECEPTION
			while(Driver_USART0.GetRxCount()				< 5); 
			
			octet_0 = reception[0];				
			LSB_angle = reception[1];
			MSB_angle = reception[2];             
			LSB_distance = reception[3];
			MSB_distance = reception[4];
			
			angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  					// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits -> Protocole pour précision
			distance_q2 =  (MSB_distance << 8) | LSB_distance ;	
			
			angle[i] = angle_q6;
			dist[i] = distance_q2;
		
			flag = octet_0 & 0x01;																		// Masquage pour isoler le premier bit, qui correspond au flag (pour chaque tour = 1)
			angle_degree = angle_q6 / 64.0;
			distance_mm = distance_q2 / 4.0;
			
			Analyse_environnement_4_secteurs(distance_mm, angle_degree, flag);
			
			
	}
}

/* --------------------------------------------------------
 * Fonction : void Analyse_environnement_4_secteurs(float distance_mm, float angle_degree, char flag)
 *
 * Analyse l'environnement sur 4 secteurs, affiche sur 4 LEDS.
 *-------------------------*/

void Analyse_environnement_4_secteurs(float distance_mm, float angle_degree, char flag)
	{
		if(flag == TOUR_COMPLET) 		// 1 tour effectué
			{
				if(detect_obst_0_90) 			Allumer_LED(LED_P2_2) ; 	else Eteindre_LED(LED_P2_2);
				if(detect_obst_90_180) 		Allumer_LED(LED_P1_31); 	else Eteindre_LED(LED_P1_31);
				if(detect_obst_180_270) 	Allumer_LED(LED_P1_29); 	else Eteindre_LED(LED_P1_29);
				if(detect_obst_270_360) 	Allumer_LED(LED_P1_28); 	else Eteindre_LED(LED_P1_28);
			
				detect_obst_0_90 = 0; // on reset tout à 0 a chaque tour
				detect_obst_90_180 = 0;
				detect_obst_180_270 =0;
				detect_obst_270_360 = 0;
			}
			
		if(distance_mm > 100.0 && distance_mm < 300.0) // 100.0 car peut avoir des erreurs donc dist = 0 -> protocole 
			{
				if(angle_degree > 0.0 && angle_degree < 90.0) 		detect_obst_0_90 = 1;
				if(angle_degree > 90.0 && angle_degree < 180.0) 	detect_obst_90_180 = 1;
				if(angle_degree > 180.0 && angle_degree < 270.0) 	detect_obst_180_270 = 1;
				if(angle_degree > 270.0 && angle_degree < 360.0)	detect_obst_270_360 = 1;
			}	
	}
	
/* --------------------------------------------------------
 * Fonction : void Analyse_environnement_8_secteurs(float distance_mm, float angle_degree, char flag)
 *
 * Analyse l'environnement sur 8 secteurs, affiche sur 7 LEDS (car un des GPIO est relié au moteur du lidar).
 *--------------------------------------------------------*/

void Analyse_environnement_8_secteurs(float distance_mm, float angle_degree, char flag)
	{
		if(flag == 1) 								// 1 tour effectué
			{
				if(detect_obst_0_45) 			Allumer_LED(LED_P2_2) ; 	else Eteindre_LED(LED_P2_2);
				if(detect_obst_45_90) 		Allumer_LED(LED_P1_31); 	else Eteindre_LED(LED_P1_31);
				if(detect_obst_90_135)  	Allumer_LED(LED_P1_29); 	else Eteindre_LED(LED_P1_29);
				if(detect_obst_135_180) 	Allumer_LED(LED_P1_28); 	else Eteindre_LED(LED_P1_28);
				if(detect_obst_180_225) 	Allumer_LED(LED_P2_3) ; 	else Eteindre_LED(LED_P2_3);
				if(detect_obst_225_270) 	Allumer_LED(LED_P2_4); 		else Eteindre_LED(LED_P2_4);
				if(detect_obst_270_315) 	Allumer_LED(LED_P2_6); 		else Eteindre_LED(LED_P2_6);
				if(detect_obst_315_360) 	Allumer_LED(LED_P1_31); 	else Eteindre_LED(LED_P1_31); // Meme led qu'une autre car pas assez de LED..
			
				detect_obst_0_45 = 0; 		// on reset tout à 0 a chaque tour
				detect_obst_45_90 = 0;
				detect_obst_90_135 = 0;
				detect_obst_135_180 = 0;
				detect_obst_180_225 = 0; 
				detect_obst_225_270 = 0;
				detect_obst_270_315 = 0;
				detect_obst_315_360 = 0;
			}
			
		if(distance_mm > 100.0 && distance_mm < 300.0) // 100.0 car peut avoir des erreurs donc dist = 0 -> protocole 
			{
				if(angle_degree > 0.0 && angle_degree < 45.0) 		detect_obst_0_45 = 1;
				if(angle_degree > 45.0 && angle_degree < 90.0) 		detect_obst_45_90 = 1;
				if(angle_degree > 90.0 && angle_degree < 135.0) 	detect_obst_90_135 = 1;
				if(angle_degree > 135.0 && angle_degree < 180.0) 	detect_obst_135_180 = 1;
				if(angle_degree > 180 && angle_degree < 225.0) 		detect_obst_180_225 = 1;
				if(angle_degree > 225.0 && angle_degree < 270.0) 	detect_obst_225_270 = 1;
				if(angle_degree > 270.0 && angle_degree < 315.0) 	detect_obst_270_315 = 1;
				if(angle_degree > 315.0 && angle_degree < 360.0) 	detect_obst_315_360 = 1;
			}	
	}	


void Init_Bluetooth(void)
	{
		Driver_USART1.Initialize(NULL);			
		Driver_USART1.PowerControl(ARM_POWER_FULL);
		
		Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS | ARM_USART_DATA_BITS_8 | ARM_USART_STOP_BITS_1 | ARM_USART_PARITY_NONE | ARM_USART_FLOW_CONTROL_NONE , 115200);
		Driver_USART1.Control(ARM_USART_CONTROL_RX, 1);			// réception
		Driver_USART1.Control(ARM_USART_CONTROL_TX, 1);			// transmission
	}

	
void Bluetooth_C_Pyt(unsigned short angle_q6, unsigned short distance_q2)
	{
		unsigned char data[4]; // a voir
		char LSB_angle_q6, MSB_angle_q6, LSB_distance_q2, MSB_distance_q2;  // Les données sont brutes ! 
	
		LSB_angle_q6 = angle_q6 & 0xFF;																			// & pour faire une lecture de angle (8 bits => LSB)
		MSB_angle_q6 = (angle_q6 >> 8) & 0xFF;															// Pour le MSB on decale jusqu'au bit 8 pour avoir les 8 bits les plus à gauche (MSB)
		LSB_distance_q2 = distance_q2 & 0xFF;
		MSB_distance_q2 = (distance_q2 >> 8) & 0xFF;
		
		data[0] = LSB_angle_q6;
		data[1] = MSB_angle_q6;
		data[2] = LSB_distance_q2;
		data[3] = MSB_distance_q2; 
		
		Driver_USART1.Send(data, 4);																				// On envoie les paquets
		while(Driver_USART1.GetTxCount() < 4);
	}
	
/* --------------------------------------------------------
 * Fonction : void Init_Moteur_Lidar(void)
 *
 * Initialisation du moteur du lidar
 *--------------------------------------------------------*/

void Init_Moteur_Lidar(void){ LPC_GPIO2->FIODIR0 |= 0x20; }	

/* --------------------------------------------------------
 * Fonction : void Allumer_Moteur_Lidar(void)
 *
 * Allume le moteur du lidar
 *--------------------------------------------------------*/

void Allumer_Moteur_Lidar(void){ LPC_GPIO2->FIOPIN0 |= 0x20;  }				
	
/*--------------------------------------------------------
 * Fonction : void Init_LED(void)
 *
 * Configuration des LEDS de la carte
 *--------------------------------------------------------*/

void Init_LED(void)
	{
		LPC_GPIO2->FIODIR0 |= 0x5C; // Configuration des LEDS P2.2, P2.3, P2.4 et P2.6 en sortie 
		LPC_GPIO1->FIODIR3 |= 0xB0; // Configuration des LEDS P1.28, P1.29 P1.31 en sortie
	}

/*--------------------------------------------------------
 * Fonction : void Allumer_LED(char Num_LED)
 * 
 * Allume la LED choisi en paramètre -> Utiliser les constantes définit au début du code ou numéro des cases.. 	
 *--------------------------------------------------------*/

void Allumer_LED(char Num_LED)
	{
		switch (Num_LED)
			{
				case 0: LPC_GPIO1->FIOPIN3 |= (1<<4); 	break;		// LED P1.28
				case 1: LPC_GPIO1->FIOPIN3 |= (1<<5); 	break;		// LED P1.29
				case 2: LPC_GPIO1->FIOPIN3 |= (1<<7); 	break;		// LED P1.31
				case 3: LPC_GPIO2->FIOPIN0 |= (1<<2); 	break;		// LED P2.2
				case 4: LPC_GPIO2->FIOPIN0 |= (1<<3); 	break;		// LED P2.3
				case 5: LPC_GPIO2->FIOPIN0 |= (1<<4); 	break;		// LED P2.4
				case 6: LPC_GPIO2->FIOPIN0 |= (1<<6); 	break;		// LED P2.6
			}
	}

/*--------------------------------------------------------
 * Fonction : void Eteindre(char Num_LED)
 *
 * Eteint la LED choisi en paramètre -> Utiliser les constantes définit au début du code ou numéro des cases..	
 *---------------------------------------------------------*/
	
void Eteindre_LED(char Num_LED)
	{
		switch (Num_LED)
			{
				case 0: LPC_GPIO1->FIOPIN3 &= ~(1<<4); 	break;		// LED P1.28
				case 1: LPC_GPIO1->FIOPIN3 &= ~(1<<5); 	break;		// LED P1.29
				case 2: LPC_GPIO1->FIOPIN3 &= ~(1<<7); 	break;		// LED P1.31
				case 3: LPC_GPIO2->FIOPIN0 &= ~(1<<2); 	break;		// LED P2.2
				case 4: LPC_GPIO2->FIOPIN0 &= ~(1<<3); 	break;		// LED P2.3
				case 5: LPC_GPIO2->FIOPIN0 &= ~(1<<4); 	break;		// LED P2.4
				case 6: LPC_GPIO2->FIOPIN0 &= ~(1<<6); 	break;		// LED P2.6
			}
	}

