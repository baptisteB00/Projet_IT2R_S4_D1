#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART
#include "RTE_Components.h"             // Component selection
#include "GLCD_Config.h"                // Board Support:Graphic LCD
#include "Board_GLCD.h"                 // Board Support:Graphic LCD
#include "stdio.h"



extern ARM_DRIVER_USART Driver_USART1;
extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

void Identification(unsigned char badge[], unsigned char recu[]);

void Init_UART(void){ 
	Driver_USART1.Initialize(NULL); 
	Driver_USART1.PowerControl(ARM_POWER_FULL); 
	Driver_USART1.Control( ARM_USART_MODE_ASYNCHRONOUS | 
	ARM_USART_DATA_BITS_8 | 
	ARM_USART_STOP_BITS_1 | 
	ARM_USART_PARITY_NONE | 
	ARM_USART_FLOW_CONTROL_NONE, 
	115200); 
	Driver_USART1.Control(ARM_USART_CONTROL_TX,1); 
	Driver_USART1.Control(ARM_USART_CONTROL_RX,1); 
}


int main(){
	unsigned char chaine_lue[10];
	unsigned char badge[10] = {0,0,0,5,0,8,4,6,2,6};
	
	Init_UART();
	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	
	while (1){
		Driver_USART1.Receive(chaine_lue,10);
		Identification(chaine_lue, badge);
	}	
	return 0;
}

void Identification(unsigned char tab[], unsigned char recu[]){
	int i, b = 0;
	uint8_t texte[24];
	for(i=0;i<10;i++){
		if (tab[i] == recu[i]) b++;
	}
	if (b == 10){
		sprintf(texte,"Badge reconnu");
	}
	else{
		sprintf(texte,"Badge non reconnu");
	}

}
