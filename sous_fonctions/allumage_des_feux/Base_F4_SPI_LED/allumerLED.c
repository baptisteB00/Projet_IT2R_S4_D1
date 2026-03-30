#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f4xx.h"                  // Device header

# define VERT 0xF000FF00
# define ROUGE 0xF00000FF
# define BLEU 0xF0FF0000
# define ORANGE
# define BLANC_Fort 0xFEFFFFFF

# define Eteint 0xE0000000
# define NbLEDs 0

extern ARM_DRIVER_SPI Driver_SPI1;

void mySPI_Thread (void);                             // thread function
void Clignoter (void);                             // thread function

void allumerLED(uint8_t numLED);
void eteindreLED(uint8_t numLED);

osThreadId_t tid_mySPI_Thread, ID_Clignoter;

//fonction de CB lancee si Event T ou R
void mySPI_callback(uint32_t event){
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(tid_mySPI_Thread, 0x01);
																							break;
		
		default : break;
	}
}

void Clignoter_callback(uint32_t event){
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(ID_Clignoter, 0x01);
																							break;
		
		default : break;
	}
}

void Init_SPI(void){
	Driver_SPI1.Initialize(/*mySPI_callback*/ Clignoter_callback);
	Driver_SPI1.PowerControl(ARM_POWER_FULL);
	Driver_SPI1.Control(ARM_SPI_MODE_MASTER | 
											//ARM_SPI_CPOLXX_CPHAXX |   // Choisir en fonction datasheet
											ARM_SPI_MSB_LSB | 
											ARM_SPI_SS_MASTER_UNUSED |
											ARM_SPI_DATA_BITS(8), 1000000);
	Driver_SPI1.Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
}

int main (void){
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// initialize peripherals here
	
	Init_SPI();
	NVIC_SetPriority(SPI1_IRQn,2);
	
	//tid_mySPI_Thread = osThreadNew ((osThreadId_t)mySPI_Thread, NULL, NULL); // Create application main thread
	ID_Clignoter = osThreadNew ((osThreadId_t)Clignoter,NULL,NULL);
	
	osKernelStart ();                         // start thread execution 
	
	osDelay(osWaitForever);
	
}

void mySPI_Thread (void) {
	/*
	int tab[22+16];
	
	// StartFrame des LEDs
	tab[0] = 0x00000000;

	
	// Frame des LEDs
	tab[1] = 0xF000FF00;
	tab[2] = 0xF000FF00;
	tab[3] = 0xF000FF00;
	tab[4] = 0xF000FF00;
	tab[5] = 0xF000FF00;
	
	//EndFrame des LEDs
	tab[6]= 0xFFFFFFFF;
	
  while (1) {
		
		tab[5]=0xe0000000;
		Driver_SPI1.Send(tab,28);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(1000);
		
		tab[5]=0xf0ffffff;
		Driver_SPI1.Send(tab,28);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(1000);
			
  }*/
	
	int tab[22+16];
	int tabC2[50];
	
	// StartFrame des LEDs
	tab[0] = 0x00000000;
	tabC2[0] = 0x00000000;
	
	// Frame des LEDs
	tab[1] = 0xF000FF00;
	tab[2] = 0xF000FF00;
	tab[3] = 0xF000FF00;
	tab[4] = 0xF000FF00;
	tab[5] = 0xF000FF00;
	
	tabC2[1] = 0xE0000000;
	tabC2[2] = 0xE0000000;
	tabC2[3] = 0xE0000000;
	tabC2[4] = 0xE0000000;
	tabC2[5] = 0xE0000000;
	
	//EndFrame des LEDs
	tab[6]= 0xFFFFFFFF;
	tabC2[6]= 0xFFFFFFFF;
	
  while (1) {
		
		Driver_SPI1.Send(tab,28);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(250);
		
		Driver_SPI1.Send(tabC2,28);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(250);
			
  }
}

void Clignoter(void){
		
	int tabC1[130];
	int tabC2[130];
	int i;
	
	// StartFrame des LEDs
	tabC1[0] = 0x00000000;
	tabC2[0] = 0x00000000;
	
	// Frame des LEDs
	
	for(i=1;i<12;i++){
		tabC1[i] = ROUGE;
	}
	
	for(i=1;i<122;i++){
		tabC2[i] = Eteint;
	}
	
	
	//EndFrame des LEDs
	tabC1[124]= 0xFFFFFFFF;
	tabC2[124]= 0xFFFFFFFF;
	
  while (1) {
		
		Driver_SPI1.Send(tabC1,492);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(250);
		
		Driver_SPI1.Send(tabC2,492);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		osDelay(250);
			
  }
}

//what


