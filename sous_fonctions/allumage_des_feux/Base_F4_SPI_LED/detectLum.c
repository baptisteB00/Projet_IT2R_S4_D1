#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f4xx.h"                  // Device header
#include "adc_F4.h"

# define VERT 0x00FF00F0						
# define ROUGE 0xFF0000F0						
# define BLEU 0x0000FFF0						
# define ORANGE 0xCF0F00F0
# define BLANC_Fort 0xFFFFFFFE			
# define JAUNE 0xFFFF00F0						
# define Eteint 0x000000E0
# define NbLEDs 16

extern ARM_DRIVER_SPI Driver_SPI1;

void Init_LEDs(void);
void Init_SPI(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);

uint32_t tab[18];

ADC_HandleTypeDef ADC1_Hand;

int main(void){

	
	ADC_Initialize(&ADC1_Hand,1);
	Init_SPI();
	Init_LEDs();
	
	while(1){
			
		allumer1LED(2,BLANC_Fort);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		
		allumer1LED(2,Eteint);
		allumer1LED(3,BLANC_Fort);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,BLANC_Fort);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,BLANC_Fort);
		allumer1LED(5,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
	}
	
}

void Init_SPI(void){
	Driver_SPI1.Initialize(NULL);
	Driver_SPI1.PowerControl(ARM_POWER_FULL);
	Driver_SPI1.Control(ARM_SPI_MODE_MASTER | 
											//ARM_SPI_CPOLXX_CPHAXX |   // Choisir en fonction datasheet
											ARM_SPI_MSB_LSB | 
											ARM_SPI_SS_MASTER_UNUSED |
											ARM_SPI_DATA_BITS(8), 1000000);
	Driver_SPI1.Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
}

void allumer1LED(uint8_t numLED, uint32_t COLOR){
	tab[numLED]=COLOR;
}

void Init_LEDs(void){
	int i;
	tab[0]=0;
	tab[17]=0xFFFFFFFF;
	for(i=1;i<16;i++){
	tab[i] = Eteint;
	}
}
//sduhif