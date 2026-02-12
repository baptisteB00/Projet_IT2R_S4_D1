#include "LPC17xx.h"                    // Device header

#include "Driver_USART.h"
extern ARM_DRIVER_USART Driver_USART1; // "déclaration" structure UART1
void Init_UART(void)
{

Driver_USART1.Initialize(NULL); // début initialisation
Driver_USART1.PowerControl(ARM_POWER_FULL); // alimentation périphérique
Driver_USART1.Control( ARM_USART_MODE_ASYNCHRONOUS |

ARM_USART_DATA_BITS_8 |
ARM_USART_STOP_BITS_1 |
ARM_USART_PARITY_NONE |
ARM_USART_FLOW_CONTROL_NONE ,
9600);

Driver_USART1.Control(ARM_USART_CONTROL_TX,1); // validation émission
Driver_USART1.Control(ARM_USART_CONTROL_RX,1); // validation réception
}

int main (void)
{
	int i;
	char reset[10];
	char cmd[10];
	uint8_t tab[50];
	Init_UART();
	
	reset[0]=0x7E;
	reset[1]=0xFF;
	reset[2]=0x06;
	reset[3]=0x0C;
	reset[4]=0x00;
	reset[5]=0x00;
	reset[6]=0x00;
	reset[7]=0xFE;
	reset[8]=0xF7;
	reset[9]=0xEF;
	
	cmd[0]=0x7E;
	cmd[1]=0xFF;
	cmd[2]=0x06;
	cmd[3]=0x03;
	cmd[4]=0x00;
	cmd[5]=0x00;
	cmd[6]=0x01;
	cmd[7]=0xFE;
	cmd[8]=0xF6;
	cmd[9]=0xEF;
	uint8_t selectTF[10] = {0x7E,0xFF,0x06,0x09,0x00,0x00,0x02,0xFE,0xF0,0xEF};
	for(i=0;i<8000000;i++);
	// RESET
//	Driver_USART1.Send(reset,10);
//	while (Driver_USART1.GetStatus().tx_busy);
	
	for(i=0;i<800000;i++);
	// SD CARD
	Driver_USART1.Send(selectTF,10);
	while (Driver_USART1.GetStatus().tx_busy);
	for(i=0;i<800000;i++);
	// play
	Driver_USART1.Send(cmd,10);
	while (Driver_USART1.GetStatus().tx_busy);
		for(i=0;i<800000;i++);
	

}










