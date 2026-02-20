#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

extern ARM_DRIVER_USART Driver_USART3; 

void Init_UART_GPS(void);

int main()
{
	Init_UART_GPS();
	
	
	
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
	}