#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f7xx_hal.h"              // Device:STM32Cube HAL:Common
#include "Driver_CAN.h"                 // CMSIS Driver:CAN

#include "GUI.h"        // Nécessaire pour GUI_Lock() / GUI_Unlock()
#include "Resource.h"

#include "stdio.h"
#include "Board_LED.h"                  // Board Support:LED

extern void configuration_overclock(void);
extern int Init_GUIThread (void);
extern   ARM_DRIVER_CAN        Driver_CAN1;

void CANthreadR(void);

osThreadId_t id_CANthreadR;

osThreadAttr_t config = {.priority=osPriorityRealtime7};

void init_CAN1();
typedef struct {
	char data[8];
	int id;
}Message_Can;

void myCAN1_callback(uint32_t obj_idx, uint32_t event)
{
    if (event & ARM_CAN_EVENT_RECEIVE)
    {
        /* 	Message was received successfully by the obj_idx object.  */
        osThreadFlagsSet(id_CANthreadR, 1<<0); //réveille la tâche de réception
    }
}

int main(void)
{
  configuration_overclock(); //pour pouvoir utiliser l'écran LCD
	
	/**********************************
	Début Initialisation périphérique
	**********************************/
	
	//Initialiser vos périphériques ici
	LED_Initialize();
	/**********************************
	Fin Initialisation périphérique
	**********************************/
	
	/**********************************
	Utilisation RTOS (Keil RTX5)
	**********************************/
	init_CAN1();
	#ifdef RTE_CMSIS_RTOS2
	  /* Initialize CMSIS-RTOS2 */
	  osKernelInitialize ();
		id_CANthreadR = osThreadNew((osThreadFunc_t)CANthreadR, NULL, &config);
	  /* Create thread functions that start executing */
		Init_GUIThread();
		
	  /* Start thread execution */
	  osKernelStart();
	#endif



}



void init_CAN1(void){

Driver_CAN1.Initialize(NULL,myCAN1_callback);
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
// Filtre objet 0 sur Identifiants de 0x120 à 0x126
Driver_CAN1.ObjectSetFilter( 0, ARM_CAN_FILTER_ID_RANGE_ADD , ARM_CAN_STANDARD_ID(0x0),ARM_CAN_STANDARD_ID(0x126)) ;
Driver_CAN1.ObjectConfigure(2,ARM_CAN_OBJ_TX); // Objet 1 pour émission
Driver_CAN1.ObjectConfigure(0,ARM_CAN_OBJ_RX); // Objet 0 pour réception
Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL); // fin initialisation
}



void CANthreadR(void)
{
	ARM_CAN_MSG_INFO rx_msg_info;
	uint8_t data_buf[8];
	char text[25];

	init_CAN1();
	
	while (1) {
		osThreadFlagsWait(1<<0, osFlagsWaitAll, osWaitForever);		// sommeil en attente fin emission
		// Code pour reception trame + affichage Id et Data sur LCD
		//.............
		
		Driver_CAN1.MessageRead(0, &rx_msg_info, data_buf, 8); // 8 data max
		GUI_Lock();
		switch ( rx_msg_info.id){
			case 296:
				sprintf(text,"%d",data_buf[0]);
			APPW_SetText(ID_SCREEN_FEUX,ID_RTEXT_2,text);
				if (data_buf[0]>50){
					LED_Off(0);
				APPW_SetVarData(ID_Var_ClignoG, 1);
				}else{
					LED_On(0);
				APPW_SetVarData(ID_Var_ClignoG, 0);
				}

					 int val = APPW_GetVarData(ID_VAR_Phare, 0); 

    // 2. Préparer la structure du message CAN
    ARM_CAN_MSG_INFO tx_msg_info;

    tx_msg_info.id = ARM_CAN_STANDARD_ID(rx_msg_info.id); 
		tx_msg_info.rtr = 0;

    Driver_CAN1.MessageSend(2, &tx_msg_info, data_buf, 4);
				
			 break;
		}
		GUI_Unlock(); // Débloque la tâche GUI

	}		
}
