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
# define NbLEDs 60

extern ARM_DRIVER_SPI Driver_SPI1;


void T_PharesAvant(void);
void T_Clignotants1(void);
void T_PharesArriere(void);
void T_Test(void);

void Init_LEDs(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);

osThreadId_t ID_T_PharesAvant, ID_T_Clignotants1, ID_T_PharesArriere, ID_T_Test;
osMutexId_t ID_EnvoiSPI;

uint32_t tab[18];

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

int main (void){
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// initialize peripherals here
	
	Init_SPI();
	Init_LEDs();
	NVIC_SetPriority(SPI1_IRQn,2);
	
	ID_EnvoiSPI = osMutexNew(NULL);
	
	ID_T_PharesAvant = osThreadNew ((osThreadId_t)T_PharesAvant,NULL,NULL);
	ID_T_Clignotants1 = osThreadNew((osThreadId_t)T_Clignotants1,NULL,NULL);
	ID_T_PharesArriere = osThreadNew ((osThreadId_t)T_PharesArriere,NULL,NULL);
	
	osKernelStart ();                         // start thread execution 
	
	osDelay(osWaitForever);
	
}


void T_PharesAvant(void){
	
  while (1) {
		/*
		allumer1LED(25,BLANC_Fort);
		allumer1LED(24,BLANC_Fort);
		allumer1LED(23,BLANC_Fort);

		allumer1LED(35,BLANC_Fort);
		allumer1LED(36,BLANC_Fort);
		allumer1LED(37,BLANC_Fort);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		*/
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		allumer1LED(1,BLANC_Fort);
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,BLANC_Fort);
		allumer1LED(6,Eteint);
		allumer1LED(7,Eteint);
		allumer1LED(8,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,BLANC_Fort);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		allumer1LED(6,BLANC_Fort);
		allumer1LED(7,Eteint);
		allumer1LED(8,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,Eteint);
		allumer1LED(3,BLANC_Fort);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		allumer1LED(6,Eteint);
		allumer1LED(7,BLANC_Fort);
		allumer1LED(8,Eteint);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,BLANC_Fort);
		allumer1LED(5,Eteint);
		allumer1LED(6,Eteint);
		allumer1LED(7,Eteint);
		allumer1LED(8,BLANC_Fort);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		//osThreadFlagsSet((osThreadId_t)ID_T_Clignotants1,0x08);
  }
}

void T_Clignotants1(void){
  while (1) {
		//osThreadFlagsWait (0x08,osFlagsWaitAll,osWaitForever);
		
		allumer1LED(0,VERT);
		allumer1LED(9,VERT); 
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osDelay(500);
		
		eteindre1LED(0);
		eteindre1LED(9);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
		
		osDelay(500);
  }
}

void T_PharesArriere(void){
	
  while (1) {

		allumer1LED(13,ROUGE);
		allumer1LED(14,ROUGE);


		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(ID_EnvoiSPI);
  }
}

void allumer1LED(uint8_t numLED, uint32_t COLOR){
	tab[numLED]=COLOR;
}
void eteindre1LED(uint8_t numLED){
	tab[numLED]=Eteint;
}
void Init_LEDs(void){
	int i;
	//tab[0]=0;
	tab[17]=0xFFFFFFFF;
	for(i=0;i<17;i++){
	tab[i] = Eteint;
	}
}


