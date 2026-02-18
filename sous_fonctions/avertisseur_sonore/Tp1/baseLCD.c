#include "Board_GLCD.h"                 // ::Board Support:Graphic LCD
#include "GLCD_Config.h"                // Keil.MCB1700::Board Support:Graphic LCD
#include "stdio.h"
#include "Driver_USART.h" 


extern ARM_DRIVER_USART Driver_USART1;
extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

int main (void){
	
	Driver_USART1.Initialize(NULL); // début initialisation
	Driver_USART1.PowerControl(ARM_POWER_FULL); // alimentation périphérique
	Driver_USART1.Control( ARM_USART_MODE_ASYNCHRONOUS |

	ARM_USART_DATA_BITS_8 |
	ARM_USART_STOP_BITS_1 |
	ARM_USART_PARITY_NONE |
	ARM_USART_FLOW_CONTROL_NONE ,
	9600);
	
	return 0;
}
