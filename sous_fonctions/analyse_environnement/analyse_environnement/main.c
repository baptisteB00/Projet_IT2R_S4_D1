#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART0;

#define LED_P1_28 	0
#define LED_P1_29 	1
#define LED_P1_31 	2
#define LED_P2_2 		3
#define LED_P2_3 		4
#define LED_P2_4 		5
#define LED_P2_6 		6

/*-------------- Prototypes des fonctions --------------*/

void Init_UART_Lidar(void);
void SCAN(void);
void Secteur_angle_4_parts(char dist_max);
void Secteur_angle_8_parts(char dist_max);
void Init_LED(void);
void Allumer_LED(char Num_LED);
void Eteindre_LED(char Num_LED);

int main()
{
	Init_UART_Lidar();
	Init_LED();
	
	LPC_GPIO2->FIODIR0 |= 0x20; // Configuration de la broche P2.5 en sortie pour le moteur du Lidar (à 100%)
	
	SCAN();
	
	return 0; 
}

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

/*********************************************************
Fonction : void SCAN(void)

Request packet (2 octets): 0xA5, 0x20
Response descriptor (7 octets): 0xA5, 0x5A, 0x05, 0x00, 0x00, 0x40, 0x81
Data response length : 5 octets 
Response mode : Multiple
*********************************************************/

void SCAN(void)
{
	char cmd[2];
	char descriptor[7];
	char reception[5];
	char LSB_angle, MSB_angle, LSB_distance, MSB_distance;
	char flag, octet_0;
	char ang_0_90 = 0, ang_90_180 = 0, ang_180_270 = 0, ang_270_360 = 0;
	
	unsigned short angle_q6, distance_q2; 
	
	int i;
	
	float angle_degree, distance_mm;
	
	cmd[0] = 0xA5;
	cmd[1] = 0x20;
	
	LPC_GPIO2->FIOPIN0 |= 0x20;										// Allume le moteur Lidar
	
	for(i = 0; i < 2000000; i++); 								// Delais pour laisser au moteur de tourner 
	
	Driver_USART0.Send(cmd, 2);										// Envoie des commandes CMD pour activer le SCAN
	while(Driver_USART0.GetTxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets DESCRIPTOR
	while(Driver_USART0.GetRxCount() < 7);
	
	while(1)
	{
		Driver_USART0.Receive(reception, 5); 				// On receptionne les paquets RECEPTION
		while(Driver_USART0.GetRxCount() < 5); 
		
		/* Reception des octets du SCAN */ 
		
	  octet_0 = reception[0];				
		LSB_angle = reception[1];
		MSB_angle = reception[2];
		LSB_distance = reception[3];
		MSB_distance = reception[4];
		
		angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  					// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits
		distance_q2 =  (MSB_distance << 8) | LSB_distance ;	

		flag = octet_0 & 0x01;	// masquage pour isoler le premier bit, qui correspond au flag (pour chaque tour = 1)
		angle_degree = angle_q6 / 64.0;
		distance_mm = distance_q2 / 4.0;
		
		
		if(flag == 1) // 1 tour effectué
		{

		if(ang_0_90) 		Allumer_LED(LED_P2_2); else Eteindre_LED(LED_P2_2);
		if(ang_90_180) 	Allumer_LED(LED_P1_31); else Eteindre_LED(LED_P1_31);
		if(ang_180_270) Allumer_LED(LED_P1_29); else Eteindre_LED(LED_P1_29);
		if(ang_270_360) Allumer_LED(LED_P1_28); else Eteindre_LED(LED_P1_28);
			
		ang_0_90 = 0; // on reset tout à 0 a chaque tour
		ang_90_180 = 0;
		ang_180_270 =0;
		ang_270_360 = 0;
		}

		if(distance_mm > 100.0 && distance_mm < 300.0) // 100.0 car peut avoir des erreurs donc dist = 0 -> protocole 
		{
		if(angle_degree > 0.0 && angle_degree < 90.0) ang_0_90 = 1;
		if(angle_degree > 90.0 && angle_degree < 180.0) ang_90_180 = 1;
		if(angle_degree > 180.0 && angle_degree < 270.0) ang_180_270 = 1;
		if(angle_degree > 270.0 && angle_degree < 360.0) ang_270_360 = 1;
		}
	
	}
}
/*********************************************************
Fonction : void Init_LED(void)

Configuration des LEDS de la carte
*********************************************************/

void Init_LED(void)
	{
		LPC_GPIO2->FIODIR0 |= 0x5C; // Configuration des LEDS P2.2, P2.3, P2.4 et P2.6 en sortie 
		LPC_GPIO1->FIODIR3 |= 0xB0; // Configuration des LEDS P1.28, P1.29 P1.31 en sortie
	}

/*********************************************************
Fonction : void Allumer_LED(char Num_LED)

Allume la LED choisi en paramètre -> Utiliser les constantes définit au début du code ou numéro des cases..
*********************************************************/

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

/*********************************************************
Fonction : void Eteindre(char Num_LED)

Eteint la LED choisi en paramètre -> Utiliser les constantes définit au début du code ou numéro des cases..
*********************************************************/
	
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

