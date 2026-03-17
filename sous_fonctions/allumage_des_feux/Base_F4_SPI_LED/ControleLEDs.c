#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f4xx.h"                  // Device header

# define VERT 0x00FF00F0						
# define ROUGE 0xFF0000F0						
# define BLEU 0x0000FFF0						
# define ORANGE 0xCF0F00F0
# define BLANC_Fort 0xFFFFFFFE			
# define JAUNE 0xFFFF00F0						

# define Eteint 0x000000E0
# define NbLEDs 60

extern ARM_DRIVER_SPI Driver_SPI1;

void mySPI_Thread (void);                             // thread function
void Clignoter (void);                             // thread function
void Init_LEDs(void);
void PharesAvant(void);
void Clignotants1(void);

void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);

osThreadId_t tid_mySPI_Thread, ID_PharesAvant,ID_Clignotants1;

uint32_t tab[62];

//fonction de CB lancee si Event T ou R
void mySPI_callback(uint32_t event){
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(tid_mySPI_Thread, 0x01);
																							break;
		
		default : break;
	}
}

void Allumer1_callback(uint32_t event){
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(ID_PharesAvant, 0x02);
																							break;
		
		default : break;
	}
}
void Clignotants1_callback(uint32_t event){
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(ID_Clignotants1, 0x04);
																							break;
		
		default : break;
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

int main (void){
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// initialize peripherals here
	
	Init_SPI();
	Init_LEDs();
	NVIC_SetPriority(SPI1_IRQn,2);
	
	//tid_mySPI_Thread = osThreadNew ((osThreadId_t)mySPI_Thread, NULL, NULL); // Create application main thread
	ID_PharesAvant = osThreadNew ((osThreadId_t)PharesAvant,NULL,NULL);
	ID_Clignotants1 = osThreadNew((osThreadId_t)Clignotants1,NULL,NULL);
	
	osThreadFlagsSet((osThreadId_t)ID_PharesAvant,0x10);
	
	osKernelStart ();                         // start thread execution 
	
	osDelay(osWaitForever);
	
}

void mySPI_Thread (void) {

}

void PharesAvant(void){
  while (1) {
		osThreadFlagsWait(0x10, osFlagsWaitAll,osWaitForever);
		allumer1LED(25,BLANC_Fort);
		allumer1LED(24,BLANC_Fort);
		allumer1LED(23,BLANC_Fort);

		allumer1LED(35,BLANC_Fort);
		allumer1LED(36,BLANC_Fort);
		allumer1LED(37,BLANC_Fort);

		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osThreadFlagsSet((osThreadId_t)ID_Clignotants1,0x08);
  }
}
void Clignotants1(void){
  while (1) {
		osThreadFlagsWait (0x08,osFlagsWaitAll,osWaitForever);
		
		allumer1LED(15,ORANGE);
		allumer1LED(45,ORANGE);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osDelay(500);
		
		eteindre1LED(15);
		eteindre1LED(45);
		
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osDelay(500);
		osThreadFlagsSet((osThreadId_t)ID_PharesAvant,0x10);
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
	tab[0]=0;
	tab[61]=0xFFFFFFFF;
	for(i=1;i<60;i++){
	tab[i] = Eteint;
	}
}



