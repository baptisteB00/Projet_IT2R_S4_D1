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
# define NbLEDs 12

extern ARM_DRIVER_SPI Driver_SPI1;

void Init_LEDs(void);
void Init_SPI(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);

uint32_t tab[12];

ADC_HandleTypeDef ADC1_Hand;

int main(void){
	int valeur;
	
	ADC_Initialize(&ADC1_Hand,1);
	Init_SPI();
	Init_LEDs();
	
	while(1){
		HAL_ADC_Start(&ADC1_Hand);
		while(HAL_ADC_PollForConversion(&ADC1_Hand, 1000) != HAL_OK);
		valeur = HAL_ADC_GetValue(&ADC1_Hand);
		if(valeur<4095){
			allumer1LED(2,BLANC_Fort);
			allumer1LED(4,BLANC_Fort);
			allumer1LED(6,BLANC_Fort);
			allumer1LED(8,BLANC_Fort);
			Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		}
		else{
			allumer1LED(2,Eteint);
			allumer1LED(4,Eteint);
			allumer1LED(6,Eteint);
			allumer1LED(8,Eteint);
			Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		}
		
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
	tab[11]=0xFFFFFFFF;
	for(i=1;i<11;i++){
	tab[i] = Eteint;
	}
}
//sduhif