#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f4xx.h"                  // Device header


//# define VERT 0xF000FF00
//# define ROUGE 0xF00000FF
//# define BLEU 0xF0FF0000
//# define ORANGE
//# define BLANC_Fort 0xFEFFFFFF
//# define JAUNE 0xF0FF00FF

//# define Eteint 0xE0000000
//# define NbLEDs 0

# define VERT 0x00FF00F0
# define ROUGE 0xFF0000F0
# define BLEU 0x0000FFF0
# define ORANGE
# define BLANC_Fort 0xFFFFFFFE
# define JAUNE 0xFF00FFF0

# define Eteint 0x000000E0
# define NbLEDs 0

extern ARM_DRIVER_SPI Driver_SPI1;

void mySPI_Thread (void);                             // thread function
void Clignoter (void);                             // thread function
void Init_LEDs(void);
void Allumer1(void);

void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);

osThreadId_t tid_mySPI_Thread, ID_Allumer1;

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
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(ID_Allumer1, 0x01);
																							break;
		
		default : break;
	}
}

void Init_SPI(void){
	Driver_SPI1.Initialize(Allumer1_callback);
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
	NVIC_SetPriority(SPI1_IRQn,2);
	
	//tid_mySPI_Thread = osThreadNew ((osThreadId_t)mySPI_Thread, NULL, NULL); // Create application main thread
	ID_Allumer1 = osThreadNew ((osThreadId_t)Allumer1,NULL,NULL);
	
	osKernelStart ();                         // start thread execution 
	
	osDelay(osWaitForever);
	
}

void mySPI_Thread (void) {

	
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

void Allumer1(void){
	
	Init_LEDs();
	
  while (1) {

		allumer1LED(10,VERT);
		allumer1LED(15,BLEU);
		allumer1LED(20,ROUGE);
		allumer1LED(25,VERT);
		allumer1LED(60,BLANC_Fort);
		allumer1LED(61,JAUNE);
		allumer1LED(120,BLEU);
		Driver_SPI1.Send(tab,62*4);
		osDelay(2000);
			
  }
}

void allumer1LED(uint8_t numLED, uint32_t COLOR){
	tab[numLED]=COLOR;
}

void Init_LEDs(void){
	int i;
	tab[0]=0;
	for(i=0;i<120;i++){
	tab[i] = Eteint;
	}
}
 //


