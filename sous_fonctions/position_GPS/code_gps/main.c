/* --------------------------------------------------------------------------
 * Projet BUT2 Semestre 4 : L'embarqué pour véhicule intelligent et communicant 
 * Auteurs : Groupe IT2R1
 * 
 * Objectif de ce code : Position GPS, envoie en CAN sur la carte de supervision (avec LCD) et pour l'interface net
 * 
 * Utilisation d'un PmodGPS -> Voir doc sur GitHub
 * Programmé sur carte STM32F4
 * -------------------------------------------------------------------------- */

#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART
#include "cmsis_os2.h"                  // CMSIS:RTOS2
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Driver_CAN.h"                 // CMSIS Driver:CAN
#include "EventRecorderConf.h"          // CMSIS-View:Event Recorder&&DAP
#include "EventRecorder.h"              // CMSIS-View:Event Recorder&&DAP
#include "string.h"


extern ARM_DRIVER_USART Driver_USART3; 
extern ARM_DRIVER_CAN Driver_CAN2;

void Init_UART_GPS(void);
void UART_Callback_GPS(uint32_t event);
void Init_CAN_Emission(void);
void myCAN2_callback(uint32_t obj_idx, uint32_t event);

/*-------------- Création des identifiants des tâches (ID) --------------*/

osThreadId_t ID_ReceptUART;
osThreadId_t ID_EmissionCAN;
osThreadId_t ID_Decode;

/*-------------- Créations des identifiants des boîte aux lettres (BAL) --------------*/

osMessageQueueId_t ID_BAL_UART_CAN;
osMessageQueueId_t ID_BAL_DECODE;

typedef struct
{
	uint8_t data[150];
} DataRecept;

uint8_t idx=0;


void thread_ReceptUART(void *argument)
{
	(void)argument;
	DataRecept Message;
	
	uint8_t *ptra, *ptrb;
	uint32_t caracta = '$';
	uint32_t caractb = '\n';
	
	uint8_t chaine [150];
	
	while(1)
	{
		idx = 0;
		Driver_USART3.Receive(&Message.data[idx], 1);		// Reception des data du GPS
		
//		ptra = strchr(Message.data, caracta);
//		
//		
//		if(ptra != NULL)
//		{
//			ptrb = strrchr(Message.data, caractb);
//			if (ptrb != NULL)
//			{
//				osThreadFlagsWait(0x0001, osFlagsWaitAll, osWaitForever);			// En attente, avec la callback
//		
//				osMessageQueuePut(ID_BAL_DECODE, &Message, NULL, osWaitForever);		// BAL pour le thread de decodage
//			}
////			chaine = strcpy (chaine, Message.data);
//		
//		}
		
		osDelay(100);
	}
}

void thread_Decode(void *argument)
{
	(void)argument;
	DataRecept Message;
	char data[100];
	char i=0;
	
	while(1)
	{
		osMessageQueueGet(ID_BAL_DECODE, &Message, NULL, osWaitForever); // On attend recevoir la mailbox du thread Recept UART
		
		
		
		if (strstr(Message.data, "$GPRMC")!= 0) // Message $GPRMC présent dans la chaîne de caractère
			{
		
		i++;
	
			}
		
	}
}

void thread_EmissionCAN(void *argument)
{
	(void)argument;
	
	
	DataRecept ReceptMessage;
	
	while(1)
	{
		osMessageQueueGet(ID_BAL_UART_CAN, &ReceptMessage, NULL, osWaitForever);		// Reception du BAL du thread ReceptUART
	}
	
	
}


/*-------------- Priorité des threads --------------*/

osThreadAttr_t configReceptUART  = { .priority = osPriorityHigh };
osThreadAttr_t configEmissionCAN = { .priority = osPriorityBelowNormal };
osThreadAttr_t configDecode      = { .priority = osPriorityNormal };

int main()
{
	
	SystemCoreClockUpdate();
	EventRecorderInitialize(EventRecordAll, 1);
	osKernelInitialize();     // Initialize CMSIS-RTOS
	
	Init_UART_GPS();					// Initialisation de l'UART3 pour le GPS
	Init_CAN_Emission();			// Initialisation du CAN2 pour l'émission
	
	ID_BAL_DECODE		= osMessageQueueNew(10, sizeof(DataRecept), NULL);
	ID_BAL_UART_CAN = osMessageQueueNew(10, sizeof(DataRecept), NULL);
	
	ID_ReceptUART  = osThreadNew( (osThreadFunc_t) thread_ReceptUART , NULL , &configReceptUART) ;
	ID_EmissionCAN = osThreadNew( (osThreadFunc_t) thread_EmissionCAN , NULL , &configEmissionCAN) ;
	ID_Decode			 = osThreadNew( (osThreadFunc_t) thread_Decode , NULL , &configDecode) ;
	
	osKernelStart();                      // Start thread execution
	return 0;
}

/* --------------------------------------------------------
 * Fonction : void Init_UART_GPS(void)
 *
 * Initialisation de l'UART3 pour le GPS (PD.9. (RX)/ PD.8 (TX))
 * 8 bits de donnée / pas parité / 1 stop / [4.8 kBd, 115.2 kBd]
 *-------------------------------------------------------*/

void Init_UART_GPS(void)
{
	Driver_USART3.Initialize(UART_Callback_GPS);
	Driver_USART3.PowerControl(ARM_POWER_FULL);
	Driver_USART3.Control( ARM_USART_MODE_ASYNCHRONOUS |
												 ARM_USART_DATA_BITS_8			 |
												 ARM_USART_STOP_BITS_1			 |
												 ARM_USART_PARITY_NONE			 |
												 ARM_USART_FLOW_CONTROL_NONE, 9600);
	Driver_USART3.Control(ARM_USART_CONTROL_RX, 1);			// réception
}

/* --------------------------------------------------------
 * Fonction : void UART_Callback_GPS(uint32_t event)
 *
 * Callback pour l'init de l'UART GPS
 *-------------------------------------------------------*/
	
void UART_Callback_GPS(uint32_t event)
{
	DataRecept caract;
	
	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE)
	{
		if (caract.data != '\n') 
		{
			idx++;
			Driver_USART3.Receive(&caract.data[idx], 1);
		}
		else
		{
			osThreadFlagsSet(ID_ReceptUART, 0x0001);
		}
		
	}
		
}

/* --------------------------------------------------------
 * Fonction : void Init_CAN(void)
 *
* Initialisation du CAN2 (PB.12 (RX) / PB.13 (TX))
 *-------------------------------------------------------*/

void Init_CAN_Emission(void)
{
	Driver_CAN2.Initialize(NULL, myCAN2_callback);
	Driver_CAN2.PowerControl(ARM_POWER_FULL);
	Driver_CAN2.SetMode(ARM_CAN_MODE_INITIALIZATION);
	Driver_CAN2.SetBitrate(ARM_CAN_BITRATE_NOMINAL, 125000,
														ARM_CAN_BIT_PROP_SEG(5U) |
														ARM_CAN_BIT_PHASE_SEG1(1U) |
														ARM_CAN_BIT_PHASE_SEG2(1U) |
														ARM_CAN_BIT_SJW(1U));
}

/* --------------------------------------------------------
 * Fonction : void UART_Callback_GPS(uint32_t event)
 *
 * Callback pour l'init du CAN d'émission
 *-------------------------------------------------------*/

void myCAN2_callback(uint32_t obj_idx, uint32_t event)
{
	if(event & ARM_CAN_EVENT_SEND_COMPLETE) osThreadFlagsSet(ID_EmissionCAN, 0x0002);
}