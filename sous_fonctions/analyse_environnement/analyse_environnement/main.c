#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART0;

/*-------------- Prototypes des fonctions --------------*/

void Init_UART_Lidar(void);
void SCAN(void);



int main()
{
	// short i;
	Init_UART_Lidar();
	
	LPC_GPIO2->FIODIR0 |= 0x20; // Configuration de la broche P2.5 en sortie pour le moteur du Lidar (à 100%)
	LPC_GPIO2->FIODIR0 |= 0x5C; // Configuration des LEDS P2.2, P2.3, P2.4 et P2.6 en sortie 
	LPC_GPIO1->FIODIR3 |= 0xB0; // Configuration des LEDS P1.28, P1.29 P1.31 en sortie
	LPC_GPIO2->FIOPIN0 |= 0x20;	// Allume Moteur Lidar 
	
	// for(i=0; i<100000; i++); // Pour laisser le temps au lidar d'activer les moteurs (car le scan fonctionne pas si c'est pas stable -> Protocole avec les schémas) 
	//LPC_GPIO2->FIOPIN0 |= 0x04; // allume
	
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
	// char flag, octet_0;
	// char ang_0_90, ang_90_180, ang_180_270, ang_270_360;
	unsigned short angle_q6, distance_q2; 
	
	float angle_degree, distance_mm;
	
	cmd[0] = 0xA5;
	cmd[1] = 0x20;
	
	
	
	Driver_USART0.Send(cmd, 2);
	while(Driver_USART0.GetTxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets descriptors
	while(Driver_USART0.GetRxCount() < 7);
	
	LPC_GPIO2->FIOPIN0 |= 0x04; // allume
	
	while(1)
	{
		LPC_GPIO2->FIOPIN0 |= 0x08; // allume
		
		Driver_USART0.Receive(reception, 5); 		// On receptionne les paquets
		while(Driver_USART0.GetRxCount() < 5); 	// Boucle while pour mettre un délais
		
		
		//octet_0 = reception[0];	// Pour mettre le bit de flag pour connaitre chaque tour 			
		LSB_angle = reception[1];
		MSB_angle = reception[2];
		LSB_distance = reception[3];
		MSB_distance = reception[4];
		
		angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  					// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits
		distance_q2 =  (MSB_distance << 8) | LSB_distance ;	

		//flag = octet_0 & 0x01;	// masquage pour isoler le premier bit, qui correspond au flag (pour chaque tour = 1)
		angle_degree = angle_q6 / 64.0;
		distance_mm = distance_q2 / 4.0;
		
		/*
		if(flag == 1) // 1 tour effectué
		{
		if(ang_0_90) // Led allumé; else  Led éteinte // entre chaque tour on laisse allumer ou eteindre (très vite donc pour nous pas de clignotement)
		if(ang_90_180) // Led allumé; else  Led éteinte
		if(ang_180_270) // Led allumé; else  Led éteinte
		if(ang_270_360) // Led allumé; else  Led éteinte

		ang_0_90 = 0; // on reset tout à 0 a chaque tour
		ang_90_180 = 0;
		ang_180_270 =0;
		ang_270_360 = 0;
		}

		if(distance_mm > 100.0 && distance_mm < 500.0) // 100.0 car peut avoir des erreurs donc dist = 0 -> protocole 
		{
		if(angle_degree > 0.0 && angle_degree < 90.0) ang_0_90 =1;
		if(angle_degree > 90.0 && angle_degree < 180.0) ang_90_180 =1;
		if(angle_degree > 180.0 && angle_degree < 270.0) ang_180_270 =1;
		if(angle_degree > 270.0 && angle_degree < 360.0) ang_270_360 =1;
		}
		*/



		
		/* 0 - 90 */ 
		if( (distance_mm > 0.0) && (distance_mm < 500.0) )
		{
			if( (angle_degree > 0.0) && (angle_degree < 90.0) )
				{
					LPC_GPIO2->FIOPIN0 |= 0x04; // allume P2.2
				}
			else 
				{
					LPC_GPIO2->FIOPIN0 &= 0xFB; // eteint		
				}				
		}
		

		/* 90 - 180 */ 
		if( (distance_mm > 0.0) && (distance_mm < 500.0) )
		{
			if( (angle_degree > 90.0) && (angle_degree < 180.0) )
				{
					LPC_GPIO1->FIOPIN3 |= 0x80; // allume P1.31
				}
			else 
				{
					LPC_GPIO1->FIOPIN3 &= 0x7F; // eteint		
				}				
		}
		
			
		/* 180 - 270 */ 
		if( (distance_mm > 0.0) && (distance_mm < 500.0) )
		{
			if( (angle_degree > 180.0) && (angle_degree < 270.0) )
				{
					LPC_GPIO1->FIOPIN3 |= 0x20; // allume P1.29
				}
			else 
				{
					LPC_GPIO1->FIOPIN3 &= 0xDF; // eteint		
				}				
		}
		
		/* 270 - 360 */ 
		if( (distance_mm > 0.0) && (distance_mm < 500.0) )
		{
			if( (angle_degree > 270.0) && (angle_degree < 360.0) )
				{
					LPC_GPIO1->FIOPIN3 |= 0x10; // allume P1.28
				}
			else 
				{
					LPC_GPIO1->FIOPIN3 &= 0xEF; // eteint		
				}				
		}
	

					//LPC_GPIO2->FIOPIN0 &= 0xF7; // eteint	
//					if((angle_degree == 90.0) )
//				{
//					LPC_GPIO2->FIOPIN0 |= 0x04; // allume
//				}
//			else 
//				{
//					LPC_GPIO2->FIOPIN0 &= 0xFB; // eteint		
//				}				

			
					
//				if( (angle_degree > 0.0) && (angle_degree < 90.0) )
//		{
//			if( (distance_mm > 0.0) && (distance_mm < 300.0) )
//				{
//					LPC_GPIO2->FIOPIN0 |= 0x04; // allume
//				}
//			else 
//				{
//					LPC_GPIO2->FIOPIN0 &= 0xFB; // eteint		
//				}				
//		}
		
		
	
		
	}
}

