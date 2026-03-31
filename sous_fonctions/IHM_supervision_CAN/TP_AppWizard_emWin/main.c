#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f7xx_hal.h"              // Device:STM32Cube HAL:Common
#include "Driver_CAN.h"                 // CMSIS Driver:CAN

extern void configuration_overclock(void);
extern int Init_GUIThread (void);

typedef struct {
	char data[8];
	int id;
}Message_Can;


int main(void)
{
  configuration_overclock(); //pour pouvoir utiliser l'écran LCD
	
	/**********************************
	Début Initialisation périphérique
	**********************************/
	
	//Initialiser vos périphériques ici
	
	/**********************************
	Fin Initialisation périphérique
	**********************************/
	
	/**********************************
	Utilisation RTOS (Keil RTX5)
	**********************************/
	#ifdef RTE_CMSIS_RTOS2
	  /* Initialize CMSIS-RTOS2 */
	  osKernelInitialize ();
		
	  /* Create thread functions that start executing */
		Init_GUIThread();
		
	  /* Start thread execution */
	  osKernelStart();
	#endif



}

void init_can_(){

	extern ARM_DRIVER_CAN Driver_CAN1;
	Driver_CAN1.Initialize(NULL,NULL);
	Driver_CAN1.PowerControl(ARM_POWER_FULL);
	Driver_CAN1.SetMode(ARM_CAN_MODE_INITIALIZATION);
	Driver_CAN1.SetBitrate(
	ARM_CAN_BITRATE_NOMINAL, // débit fixe
	125000, // 125 kbits/s (LS)
	ARM_CAN_BIT_PROP_SEG(5U) | // prop. seg = 5 TQ
	ARM_CAN_BIT_PHASE_SEG1(1U) | // phase seg1 = 1 TQ
	ARM_CAN_BIT_PHASE_SEG2(1U) | // phase seg2 = 1 TQ
	ARM_CAN_BIT_SJW(1U) // Resync. Seg = 1 TQ
	);

	Driver_CAN1.ObjectConfigure(1,ARM_CAN_OBJ_TX); // Objet 1 pour émission
	Driver_CAN1.ObjectConfigure(0,ARM_CAN_OBJ_RX); // Objet 0 pour réception
	Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL); // fin initialisation

}

