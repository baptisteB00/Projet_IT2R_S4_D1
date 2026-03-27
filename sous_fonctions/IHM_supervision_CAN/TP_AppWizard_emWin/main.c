#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source

extern void configuration_overclock(void);
extern int Init_GUIThread (void);

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
