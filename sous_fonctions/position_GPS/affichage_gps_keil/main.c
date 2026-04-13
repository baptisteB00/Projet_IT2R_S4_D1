#include "Driver_CAN.h"                 // CMSIS Driver:CAN
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Board_GLCD.h"                 // Board Support:Graphic LCD
#include "GLCD_Config.h"                // Board Support:Graphic LCD
#include <stdio.h>
#include "string.h"
#include "LPC17xx.h"                    // Device header


extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

extern   ARM_DRIVER_CAN         Driver_CAN1;

osThreadId_t id_thread_ReceptionCAN;
osMessageQueueId_t ID_BAL_RECEIVE_CAN;

typedef struct {
    int niveau_liquide;   // En %
    char temps[11];       // HHMMSS
    char latitude[11];
    char longitude[12];
} Affichage;

Affichage monAffiche; 

 // CAN1 utilisé pour reception
void myCAN1_callback(uint32_t obj_idx, uint32_t event)
{
    if (event & ARM_CAN_EVENT_RECEIVE)
    {
        /* 	Message was received successfully by the obj_idx object.  */
        osThreadFlagsSet(id_thread_ReceptionCAN, 1<<0); //reveille la tâche de reception
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
	
	// Mettre ici les filtres ID de reception sur objet 0
	//....................................................
	// On accepte les IDs de 0x0F0 à 0x0FF
	Driver_CAN1.ObjectSetFilter(0, ARM_CAN_FILTER_ID_MASKABLE_ADD, ARM_CAN_STANDARD_ID(0x0F0), 0x7F0); 
	Driver_CAN1.ObjectConfigure(0, ARM_CAN_OBJ_RX);

	Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL);
	
}
 // tâche reception
void thread_ReceptionCAN(void *argument)
{
	ARM_CAN_MSG_INFO                rx_msg_info;
	uint8_t donnees_rx[8];
//	char heure[10];
//	char latitude[10];
//	char nord_sud[10];
//	char longitude[10];
//	char est_ouest[10];
//	uint32_t id;
	char ligne1[20];
  char ligne2[20];
	
//	osStatus_t status;

	InitCan1(); //initialise le CAN utilisée pour la r?ception
	
	while (1) {
		osThreadFlagsWait(1<<0, osFlagsWaitAll, osWaitForever);		// sommeil en attente fin emission
		// Code pour reception trame + affichage Id et Data sur LCD
		//.............
		
		
		 // Lecture du message sur l'objet 0
        Driver_CAN1.MessageRead(0, &rx_msg_info, donnees_rx, 8);

        // Tri par ID
        switch(rx_msg_info.id)
        {
//            case ARM_CAN_STANDARD_ID(0x200): // ID du Capteur de liquide
//                monAffiche.niveau_liquide = donnees_rx[0];
//                break;

            case ARM_CAN_STANDARD_ID(0x0F6): // ID GPS Temps
                strncpy(monAffiche.temps, (char*)donnees_rx, 6);
//                monAffiche.temps[6] = '\0';
                break;

            case ARM_CAN_STANDARD_ID(0x0F7): // ID GPS Latitude
                strncpy(monAffiche.latitude, (char*)donnees_rx, 8);
//                monAffiche.latitude[8] = '\0';
                break;

            case ARM_CAN_STANDARD_ID(0x0F8): // ID GPS Longitude
                strncpy(monAffiche.longitude, (char*)donnees_rx, 8);
//                monAffiche.longitude[8] = '\0';
                break;
        }
				
		// Préparation du texte
        sprintf(ligne1, " T:%s", monAffiche.temps);
        sprintf(ligne2, "L:%s Lo:%s", monAffiche.latitude, monAffiche.longitude);

        GLCD_ClearScreen();
        GLCD_DrawString(0,10, ligne1); // Affiche sur la ligne 0
        GLCD_DrawString(1, 100, ligne2); // Affiche sur la ligne 1
        
        osDelay(500); // Rafraîchissement 2 fois par seconde
		
	}		
}
//void thread_AffichageLCD(void *argument)
//{
//    char ligne1[20];
//    char ligne2[20];

//    while(1)
//    {
//        // Préparation du texte
//        sprintf(ligne1, "Eau: %d%%  T:%s", monAffiche.niveau_liquide, monAffiche.temps);
//        sprintf(ligne2, "L:%s Lo:%s", monAffiche.latitude, monAffiche.longitude);

//        GLCD_ClearScreen();
//        GLCD_DrawString(0,10, ligne1); // Affiche sur la ligne 0
//        GLCD_DrawString(1, 100, ligne2); // Affiche sur la ligne 1
//        
//        osDelay(500); // Rafraîchissement 2 fois par seconde
//    }
//}

int main (void)
{

	osKernelInitialize();                 // Initialize CMSIS-RTOS
	// initialize peripherals here
	
	// initialize peripherals here
	LPC_PINCON->PINMODE1 = LPC_PINCON->PINMODE1 | 0x0000aaaa;
	
	GLCD_Initialize();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
	GLCD_SetForegroundColor(GLCD_COLOR_YELLOW);
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_DrawString(0,0,"TP CAN IT2R 2026");
	
	//creation de tâches
	id_thread_ReceptionCAN = osThreadNew((osThreadFunc_t)thread_ReceptionCAN, NULL, NULL);    // tâche CAN1 reçoit
  osKernelStart();                      // Start thread execution
  for (;;) {}

}