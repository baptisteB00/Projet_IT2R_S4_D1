#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART1;

/*-------------- Prototypes des fonctions --------------*/

void Init_UART_Lidar(void);


int main()
{
	LPC_GPIO2->FIODIR0 |= 0x20; // Configuration de la broche P2.5 en sortie pour le moteur du Lidar
	
	while(1)
	{
		//LPC_GPIO2->FIOPIN0 &= 0xD0;	// Eteint Moteur Lidar 
		LPC_GPIO2->FIOPIN0 |= 0x20;	// Allume Moteur Lidar 
	}
	
	return 0; 
}

void Init_UART_Lidar(void)
{
	Driver_USART1.Initialize(NULL);			
	Driver_USART1.PowerControl(ARM_POWER_FULL);
	Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS | 
												ARM_USART_DATA_BITS_8 | 
												ARM_USART_STOP_BITS_1 | 
												ARM_USART_PARITY_NONE | 
												ARM_USART_FLOW_CONTROL_NONE , 115200); 
	
	Driver_USART1.Control(ARM_USART_CONTROL_RX, 1);			// reception
	Driver_USART1.Control(ARM_USART_CONTROL_TX, 1);			// transmission
}


	
	
	
	
	


