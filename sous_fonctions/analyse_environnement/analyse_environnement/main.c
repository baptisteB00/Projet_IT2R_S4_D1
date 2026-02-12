#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART0;

/*-------------- Prototypes des fonctions --------------*/

void Init_UART_Lidar(void);
void SCAN(void);

int main()
{
	LPC_GPIO2->FIODIR0 |= 0x20; // Configuration de la broche P2.5 en sortie pour le moteur du Lidar
	LPC_GPIO2->FIODIR0 &= 0xA3; // Configuration des LEDS P2.2, P2.3, P2.4 et P2.6 en entrée 
	LPC_GPIO2->FIOPIN0 |= 0x20;	// Allume Moteur Lidar 
	
	SCAN();
	while(1)
	{
		//LPC_GPIO2->FIOPIN0 &= 0xD0;	// Eteint Moteur Lidar 
	
	}
	
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

void SCAN(void)
{
	char cmd[2];
	char descriptor[7];
	char reception[5];
	char LSB_angle, MSB_angle, LSB_distance, MSB_distance;
	
	unsigned short angle_q6, distance_q2; 
	
	float angle_degree, distance_mm;
	
	cmd[0] = 0xA5;
	cmd[1] = 0x20;
	
	Driver_USART0.Send(cmd, 2);
	while(Driver_USART0.GetRxCount() < 2);
	
	Driver_USART0.Receive(descriptor, 7); 				// On receptionne les paquets
	while(Driver_USART0.GetRxCount() < 7);
	
	while(1)
	{
		Driver_USART0.Receive(reception, 5); 		// On receptionne les paquets
		while(Driver_USART0.GetRxCount() < 5); 	// Boucle while pour mettre un délais
						
		LSB_angle = reception[1];
		MSB_angle = reception[2];
		LSB_distance = reception[3];
		MSB_distance = reception[4];
		
		angle_q6 = (MSB_angle << 7) | (LSB_angle >> 1);  					// angle_q6 et distance_q2 => données brutes, << et >> décalage des bits
		distance_q2 =  (MSB_distance << 8) | LSB_distance ;
		
		angle_degree = angle_q6 / 64.0;
		distance_mm = distance_q2 / 4.0;
		
		if( (angle_degree > 0) && (angle_degree < 90) && (distance_mm > 0) && (distance_mm > 300) )
		{
			LPC_GPIO2->FIOPIN0 |= 0x04;
		}			
		
		else 
		{
			LPC_GPIO2->FIOPIN0 &= 0xFB;
		}
	
			
			
				
		
	}
}

