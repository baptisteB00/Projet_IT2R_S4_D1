/* --------------------------------------------------------------------------
 * Projet BUT2 Semestre 4 : L'embarqué pour véhicule intelligent et communicant 
 * Auteurs : Groupe IT2R1
 * 
 * Objectif de ce code : Position GPS
 * 
 * Utilisation d'un PmodGPS -> Voir doc sur GitHub
 * Programmé sur carte STM32F4
 * -------------------------------------------------------------------------- */

#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART3; 

void Init_UART_GPS(void);

int main()
{
	char message[100];

	Init_UART_GPS();
	
	while(1)
	{
		Driver_USART3.Receive(message, 100);
		while(Driver_USART3.GetRxCount() < 100);
		
	}
	return 0;
}


void Init_UART_GPS(void)
	{
		Driver_USART3.Initialize(NULL);
		Driver_USART3.PowerControl(ARM_POWER_FULL);
		Driver_USART3.Control( ARM_USART_MODE_ASYNCHRONOUS |
													 ARM_USART_DATA_BITS_8			 |
													 ARM_USART_STOP_BITS_1			 |
													 ARM_USART_PARITY_NONE			 |
													 ARM_USART_FLOW_CONTROL_NONE, 
													 115200);
		Driver_USART3.Control(ARM_USART_CONTROL_RX, 1);			// réception
		Driver_USART3.Control(ARM_USART_CONTROL_TX, 1);			// transmission
	}