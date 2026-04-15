#define GUI_CONST_STORAGE  const __attribute__((aligned(4)))

#include "stm32f7xx.h"                  // Device header
#include "AppWizard.h"
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stm32f7xx_hal.h"              // Device:STM32Cube HAL:Common
#include "Driver_CAN.h"                 // CMSIS Driver:CAN


#include "GUI.h"                        // Graphics:CORE


#include "Resource.h"

#include "stdio.h"
#include "Board_LED.h"                  // Board Support:LED
//--------------------------------------------------
extern void configuration_overclock(void);
extern int Init_GUIThread (void);
extern   ARM_DRIVER_CAN        Driver_CAN1;

void CANthreadR(void);

osThreadId_t id_CANthreadR;

osThreadAttr_t config = {.priority=osPriorityAboveNormal};
osMessageQueueId_t ID_BAL;

extern GUI_CONST_STORAGE APPW_CONTENT ID_CONTENT_000_Data;

#define ID_CAN_RADAR 0x010
#define ID_CAN_lidar 0x011
#define ID_CAN_Panneau 0x012
#define ID_CAN_Nunchuk 0x020
#define ID_CAN_Vmoteur 0x021
#define ID_CAN_Phare 0x030
#define ID_CAN_GestionPORTE 0x031
#define ID_CAN_SonDFP 0x032
#define ID_CAN_Capteur 0x033
#define ID_CAN_GPS 0x034

//--------structure--------------------------------------------

void init_CAN1();
typedef struct {
	char data[8];
	int id;
}Message_Can;

typedef struct
{
	ARM_CAN_MSG_INFO rx_msg_info;
	uint8_t data_buf[8];
}VarMailbox_t;

//-------------------------------------------------------
void myCAN1_callback(uint32_t obj_idx, uint32_t event)
{
	
		VarMailbox_t mail;
    if (event == ARM_CAN_EVENT_RECEIVE)
		{
        /* 	Message was received successfully by the obj_idx object.  */
				Driver_CAN1.MessageRead(0, &mail.rx_msg_info, mail.data_buf, 2); // 8 data max
        //osThreadFlagsSet(id_CANthreadR, 1<<0); //réveille la tâche de réception
				osMessageQueuePut (ID_BAL, &mail, 0, 0);
    }
		
		 
}

//-------------------------------------------------------------
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
	#ifdef RTE_CMSIS_RTOS2
	  /* Initialize CMSIS-RTOS2 */
	  osKernelInitialize ();
	
		ID_BAL = osMessageQueueNew(16, sizeof(VarMailbox_t), NULL);
		id_CANthreadR = osThreadNew((osThreadFunc_t)CANthreadR, NULL, &config);
		

	  /* Create thread functions that start executing */
		Init_GUIThread();
		
	  /* Start thread execution */
	  osKernelStart();
	#endif



}

//-------------------------------------------------------------

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
//Driver_CAN1.ObjectSetFilter( 0, ARM_CAN_FILTER_ID_RANGE_ADD , ARM_CAN_STANDARD_ID(0x0),ARM_CAN_STANDARD_ID(0x200)) ;
	Driver_CAN1.ObjectSetFilter(0,ARM_CAN_FILTER_ID_EXACT_ADD , ARM_CAN_STANDARD_ID(0x128),0);
Driver_CAN1.ObjectConfigure(2,ARM_CAN_OBJ_TX); // Objet 2 pour émission
Driver_CAN1.ObjectConfigure(0,ARM_CAN_OBJ_RX); // Objet 0 pour réception
Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL); // fin initialisation
}

//---------------------------------------------------------------------------------
void CANthreadR(void)
{

	uint8_t data_buf[8]= {0,0,0,0,0,0,0};
	char text[25];
	VarMailbox_t mail;

	init_CAN1();
		LED_Initialize();
	//LED_On(0);
	
	ARM_CAN_MSG_INFO tx_msg_info;

  tx_msg_info.id = ARM_CAN_STANDARD_ID(0x128); 
	tx_msg_info.rtr = 0;

    Driver_CAN1.MessageSend(2, &tx_msg_info, data_buf, 4);

	while (1) {
		//osThreadFlagsWait(1<<0, osFlagsWaitAll, osWaitForever);		// sommeil en attente fin emission
		osMessageQueueGet(ID_BAL, &mail, NULL, osWaitForever);

		switch ( mail.rx_msg_info.id){
			case ID_CAN_GestionPORTE:
			{
				if ((mail.data_buf[0]==1)&&(mail.data_buf[1]==0)){
					APPW_SetVarData(ID_VAR_Cadena, 1);
				}
				else if ((mail.data_buf[0]==1)&&(mail.data_buf[1]==1)){
					APPW_SetVarData(ID_VAR_Cadena, 0);
				}
		case 0x033: // ID_CAN_Capteur (ou celui de ton huile)
    {
        // On récupère l'octet en hexa (0x00 à 0x64)
        uint8_t valeurHexa = data_buf[7]; 
				if(valeurHexa==0x64){
					valeurHexa=100;
				}
				if(valeurHexa==0x32){
					valeurHexa=50;
				}
				if(valeurHexa==0x00){
					valeurHexa=0;
				}
        // Pas besoin de conversion compliquée si tu as mis le Max à 100 dans AppWizard,
        // car 0x64 en hexa est lu directement comme 100 par le C.
        
        // On envoie la valeur à la variable AppWizard
        APPW_SetVarData(ID_VAR_HUILE, 50);
    }
    break;
			}
		}

	}		
}
