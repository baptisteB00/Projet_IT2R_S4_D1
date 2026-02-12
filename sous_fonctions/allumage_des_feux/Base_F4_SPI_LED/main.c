#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f4xx.h"                  // Device header



extern ARM_DRIVER_SPI Driver_SPI1;

void mySPI_Thread (void);                             // thread function
osThreadId_t tid_mySPI_Thread;

//fonction de CB lancee si Event T ou R
void mySPI_callback(uint32_t event)
{
	switch (event) {
		
		
		case ARM_SPI_EVENT_TRANSFER_COMPLETE  : 	 osThreadFlagsSet(tid_mySPI_Thread, 0x01);
																							break;
		
		default : break;
	}
}

void Init_SPI(void){
	Driver_SPI1.Initialize(mySPI_callback);
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
	
	tid_mySPI_Thread = osThreadNew ((osThreadId_t)mySPI_Thread, NULL, NULL); // Create application main thread
	
	osKernelStart ();                         // start thread execution 
	
	osDelay(osWaitForever);
	
}

void mySPI_Thread (void) {
	
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
		
		Driver_SPI1.Send(tab,28);
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);	// sommeil fin emission
		
		osDelay(1000);
			
			
  }
}