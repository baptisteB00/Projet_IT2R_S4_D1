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
void T_ClignotantsG(void);
void T_ClignotantsD(void);
void T_PharesArriere(void);
void T_Disco(void);
void T_Tout(void);

void Init_LEDs(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);

osThreadId_t ID_T_PharesAvant, ID_T_ClignotantsD, ID_T_PharesArriere, ID_T_Disco, ID_T_ClignotantsG, ID_T_Tout;
osMutexId_t ID_EnvoiSPI,ID_ModifTAB;

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
	
	ID_ModifTAB = osMutexNew(NULL);
	ID_EnvoiSPI = osMutexNew(NULL);
	
	//ID_T_PharesAvant = osThreadNew ((osThreadId_t)T_PharesAvant,NULL,NULL);
	//ID_T_ClignotantsG = osThreadNew((osThreadId_t)T_ClignotantsG,NULL,NULL);
	ID_T_ClignotantsD = osThreadNew((osThreadId_t)T_ClignotantsD,NULL,NULL);
	//ID_T_PharesArriere = osThreadNew ((osThreadId_t)T_PharesArriere,NULL,NULL);
	//ID_T_Disco = osThreadNew((osThreadFunc_t)T_Disco,NULL,NULL);
	//ID_T_Tout = osThreadNew((osThreadId_t)T_Tout,NULL,NULL);
	
	osKernelStart ();                         // start thread execution 
	
}

void T_Tout(void){
	int i;
	int result;
  while (1) {
		result = osThreadFlagsWait ((1<<0)|(1<<1),osFlagsWaitAny,osWaitForever);
		if((result & (1<<1))==(1<<1)){
			for(i=0;i<2;i++){
				osMutexAcquire(ID_ModifTAB,osWaitForever);
				for(i=0;i<15;i++) allumer1LED(i,ROUGE);
				osMutexRelease(ID_ModifTAB);
				osMutexAcquire(ID_EnvoiSPI,osWaitForever);
				Driver_SPI1.Send(tab,(NbLEDs+1)*4);
				osMutexRelease(ID_EnvoiSPI);
				osDelay(100);
				osMutexAcquire(ID_ModifTAB,osWaitForever);
				for(i=0;i<15;i++) eteindre1LED(i);
				osMutexRelease(ID_ModifTAB);
				osMutexAcquire(ID_EnvoiSPI,osWaitForever);
				Driver_SPI1.Send(tab,(NbLEDs+1)*4);
				osMutexRelease(ID_EnvoiSPI);
				osDelay(100);
			}
		}
		else if((result & (1<<0))==(1<<0)){
			for(i=0;i<2;i++){
				osMutexAcquire(ID_ModifTAB,osWaitForever);
				for(i=0;i<15;i++) allumer1LED(i,VERT);
				osMutexRelease(ID_ModifTAB);
				osMutexAcquire(ID_EnvoiSPI,osWaitForever);
				Driver_SPI1.Send(tab,(NbLEDs+1)*4);
				osMutexRelease(ID_EnvoiSPI);
				osDelay(100);
				osMutexAcquire(ID_ModifTAB,osWaitForever);
				for(i=0;i<15;i++) eteindre1LED(i);
				osMutexRelease(ID_ModifTAB);
				osMutexAcquire(ID_EnvoiSPI,osWaitForever);
				Driver_SPI1.Send(tab,(NbLEDs+1)*4);
				osMutexRelease(ID_EnvoiSPI);
				osDelay(100);
			}
		}
		//osThreadFlagsSet((osThreadId_t)ID_T_Clignotants1,0x08);
  }
}

void T_PharesAvant(void){
	
  while (1) {
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(1,BLANC_Fort);
		allumer1LED(2,BLANC_Fort);
		allumer1LED(3,BLANC_Fort);
		allumer1LED(4,BLANC_Fort);
		allumer1LED(5,BLANC_Fort);
		allumer1LED(6,BLANC_Fort);
		allumer1LED(7,BLANC_Fort);
		allumer1LED(8,BLANC_Fort);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		
		//osThreadFlagsSet((osThreadId_t)ID_T_Clignotants1,0x08);
  }
}

void T_ClignotantsD(void){

  while (1) {
		//osThreadFlagsWait (0x08,osFlagsWaitAll,osWaitForever);
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(9,ORANGE);
		allumer1LED(12,ORANGE);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(500);
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		eteindre1LED(9);
		eteindre1LED(12);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		
		osDelay(500);
  }
}

void T_ClignotantsG(void){

  while (1) {
		//osThreadFlagsWait (0x08,osFlagsWaitAll,osWaitForever);
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(0,ORANGE);
		allumer1LED(15,ORANGE);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(500);
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		eteindre1LED(0);
		eteindre1LED(15);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		
		osDelay(500);
  }
}

void T_PharesArriere(void){
	
  while (1) {
		
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(13,ROUGE);
		allumer1LED(14,ROUGE);
		osMutexRelease(ID_ModifTAB);


		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
  }
}

void T_Disco(void){
	
	while(1){
		
		//Etat 1
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(1,BLANC_Fort);
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,BLANC_Fort);
		allumer1LED(6,Eteint);
		allumer1LED(7,Eteint);
		allumer1LED(8,Eteint);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		
		//Etat 2
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,BLANC_Fort);
		allumer1LED(3,Eteint);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		allumer1LED(6,BLANC_Fort);
		allumer1LED(7,Eteint);
		allumer1LED(8,Eteint);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		
		//Etat 3
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,Eteint);
		allumer1LED(3,BLANC_Fort);
		allumer1LED(4,Eteint);
		allumer1LED(5,Eteint);
		allumer1LED(6,Eteint);
		allumer1LED(7,BLANC_Fort);
		allumer1LED(8,Eteint);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
		
		//Etat4
		osMutexAcquire(ID_ModifTAB,osWaitForever);
		allumer1LED(1,Eteint);
		allumer1LED(2,Eteint);
		allumer1LED(3,Eteint);
		allumer1LED(4,BLANC_Fort);
		allumer1LED(5,Eteint);
		allumer1LED(6,Eteint);
		allumer1LED(7,Eteint);
		allumer1LED(8,BLANC_Fort);
		osMutexRelease(ID_ModifTAB);
		
		osMutexAcquire(ID_EnvoiSPI,osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+1)*4);
		osMutexRelease(ID_EnvoiSPI);
		osDelay(100);
		
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


