#include "Driver_CAN.h"                 // CMSIS Driver:CAN
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Board_GLCD.h"                 // Board Support:Graphic LCD
#include "GLCD_Config.h"                // Board Support:Graphic LCD
#include <stdio.h>
#include "LPC17xx.h"                    // Device header


extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern   ARM_DRIVER_CAN         Driver_CAN1;

osThreadId_t id_CANthreadR;
osMessageQueueId_t ID_BAL_RECEIVE_CAN;

 // CAN1 utilisé pour reception
void myCAN1_callback(uint32_t obj_idx, uint32_t event)
{
    if (event & ARM_CAN_EVENT_RECEIVE)
    {
        /* 	Message was received successfully by the obj_idx object.  */
        osThreadFlagsSet(id_CANthreadR, 1<<0); //reveille la tâche de reception
    }
}
 
// CAN1 utilisé pour reception
void InitCan1 (void) {
	Driver_CAN1.Initialize(NULL,myCAN1_callback);
	
	// Code d'initialisation du CAN1 en RX
	//.............
	Driver_CAN1.PowerControl(ARM_POWER_FULL);
	
	Driver_CAN1.SetMode(ARM_CAN_MODE_INITIALIZATION);
	Driver_CAN1.SetBitrate( ARM_CAN_BITRATE_NOMINAL,
													125000,
													ARM_CAN_BIT_PROP_SEG(5U)   |         // Set propagation segment to 5 time quanta
                          ARM_CAN_BIT_PHASE_SEG1(1U) |         // Set phase segment 1 to 1 time quantum (sample point at 87.5% of bit time)
                          ARM_CAN_BIT_PHASE_SEG2(1U) |         // Set phase segment 2 to 1 time quantum (total bit is 8 time quanta long)
                          ARM_CAN_BIT_SJW(1U));                // Resynchronization jump width is same as phase segment 2
                          
	
	Driver_CAN1.ObjectConfigure(0,ARM_CAN_OBJ_RX);				// Objet 0 du CAN1 pour r?ception
	
	// Mettre ici les filtres ID de r?ception sur objet 0
	//....................................................
	
	Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL);					// fin init
	
}
 // tâche reception
void CANthreadR(void)
{
	ARM_CAN_MSG_INFO                rx_msg_info;
	uint8_t data_buf[8];
	char heure[00];
	char latitude[20];
	char nord_sud[20];
	char longitude[20];
	char est_ouest[20];
	uint32_t id;
	
	osStatus_t status;

	InitCan1(); //initialise le CAN utilisée pour la r?ception
	
	while (1) {
		osThreadFlagsWait(1<<0, osFlagsWaitAll, osWaitForever);		// sommeil en attente fin emission
		// Code pour reception trame + affichage Id et Data sur LCD
		//.............
		
		
		//status = osMessageQueueGet(ID_BAL_EMET_CAN, &data_buf, NULL, osWaitForever); // On attend recevoir la mailbox du thread Recept UART
		
		//if (status == osOK) 
		
			Driver_CAN1.MessageRead(0, &rx_msg_info,data_buf,5 );
			
			sprintf (heure, " Temps :  ",data_buf[0]);
			sprintf (latitude, " Latitude :  ",data_buf[1]);
			sprintf (nord_sud, " N/S :  ",data_buf[2]);
			sprintf (longitude, " Longitude :  ",data_buf[3]);
			sprintf (est_ouest, " E/O :  ",data_buf[4]);
			
			GLCD_DrawString(1,20,(char *)heure);
			GLCD_DrawString(1,20,(char *)latitude);
			GLCD_DrawString(1,20,(char *)nord_sud);
			GLCD_DrawString(1,20,(char *)longitude);
			GLCD_DrawString(1,20,(char *)est_ouest);
		
	}		
}

int main (void)
{

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	// initialize peripherals here

	// initialize peripherals here
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 | 0x0000aaaa;
	
	GLCD_Initialize();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
	//GLCD_SetForegroundColor(GLCD_COLOR_YELLOW);
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_DrawString(0,0,"TP CAN IT2R 2026");
	
	//creation de tâches
	id_CANthreadR = osThreadNew((osThreadFunc_t)CANthreadR, NULL, NULL);    // tâche CAN2 reçoit
  osKernelStart();                      // Start thread execution
  for (;;) {}

}