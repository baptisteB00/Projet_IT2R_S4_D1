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
#include "stdio.h"

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

osMessageQueueId_t ID_BAL_DECODE;
osMessageQueueId_t ID_BAL_EMET_CAN;

typedef struct
{
	uint8_t data[100];
} DataRecept;

typedef struct
{
	char *temps;				//  RMC / GGA
	char *latitude;			//  RMC / GGA
	char *nord_sud;			//  RMC / GGA
	char *est_ouest;		//  RMC / GGA
	char *longitude;		//  RMC / GGA
	char *alerte;				//  RMC
} DataCoordonnee;

uint8_t idx=0;

DataRecept Message;

void thread_ReceptUART(void *argument)
{
	(void)argument;	
	
	while(1)
	{
		// J lance réception du tout premier caractère
		Driver_USART3.Receive(&Message.data[0], 1);
		 // On attend le drapeau (Flag) mis par la callback lors du '\n'
    osThreadFlagsWait(0x0001, osFlagsWaitAll, osWaitForever);
		
		// On envoie la trame complète au thread de décodage
    osMessageQueuePut(ID_BAL_DECODE,&Message.data , NULL, osWaitForever);
		idx = 0;

		osDelay(100);
	}
}

void thread_Decode(void *argument)
{
	(void)argument;
	
	DataRecept MessageRecu;
	DataCoordonnee Coordonnee;
	int i=0;
	
	char val_GPRMC[10];
	char val_GPGGA[10];
	char val[6];
	char val2[6];
	const char *separateur = ",";

	int32_t  retour_val_GPRMC;
	int32_t  retour_val_GPGGA;
	
	int32_t  retour_val_GPRMCb;
	int32_t  retour_val_GPGGAb;
	
	char * strToken;
	
	
	while(1)
	{
		osMessageQueueGet(ID_BAL_DECODE, &MessageRecu, NULL, osWaitForever); // On attend recevoir la mailbox du thread Recept UART
		
		//sprintf(val, "%06s", MessageRecu.data);		// On prend les 6 premiers caractère (à partir du $)
		//sprintf(val2, "%06s", MessageRecu.data+1);		
		
		retour_val_GPRMC = strncmp(MessageRecu.data, "$GPRMC",6);	// strncmp renvoie 0 correspond à la chaîne de carcactère
		retour_val_GPGGA = strncmp(MessageRecu.data, "$GPGGA",6);
		
		retour_val_GPRMCb = strncmp(MessageRecu.data+1, "$GPRMC",6);	// strncmp renvoie 0 correspond à la chaîne de carcactère
		retour_val_GPGGAb = strncmp(MessageRecu.data+1, "$GPGGA",6);

		
		
		if (retour_val_GPRMC == NULL)		// En fonction de ce qu'on reçoit au début de la trame, notre code va dans une de ses conditions pour décoder la bonne trame
		{
			 strToken = strtok(MessageRecu.data, separateur);
			
			if (strToken != NULL)
				{
					Coordonnee.temps 		 = strtok (NULL, separateur); 
					Coordonnee.alerte 	 = strtok (NULL, separateur); 
					Coordonnee.latitude  = strtok (NULL, separateur);
				  Coordonnee.nord_sud  = strtok (NULL, separateur);
				  Coordonnee.longitude = strtok (NULL, separateur);
				  Coordonnee.est_ouest = strtok (NULL, separateur);
				}		
				while ( strToken != NULL ) {
        // On demande le token suivant.
        strToken = strtok ( NULL, separateur );
				}		
		}
		
		else if (retour_val_GPGGA == NULL) 	// Renvo
		{
			strToken = strtok(MessageRecu.data, separateur);
			 
			if (strToken != NULL)
				{
					Coordonnee.temps 		 = strtok (NULL, separateur); 
					Coordonnee.latitude  = strtok (NULL, separateur);
				  Coordonnee.nord_sud  = strtok (NULL, separateur);
				  Coordonnee.longitude = strtok (NULL, separateur);
				  Coordonnee.est_ouest = strtok (NULL, separateur);
				}	
			while ( strToken != NULL ) {
        // On demande le token suivant.
        strToken = strtok ( NULL, separateur );
				}				
		}
		
		else if (retour_val_GPRMCb == NULL)		// En fonction de ce qu'on reçoit au début de la trame, notre code va dans une de ses conditions pour décoder la bonne trame
		{
			strToken = strtok(MessageRecu.data, separateur);
			
			if (strToken != NULL)
				{
					Coordonnee.temps 		 = strtok (NULL, separateur); 
					Coordonnee.alerte 	 = strtok (NULL, separateur); 
					Coordonnee.latitude  = strtok (NULL, separateur);
				  Coordonnee.nord_sud  = strtok (NULL, separateur);
				  Coordonnee.longitude = strtok (NULL, separateur);
				  Coordonnee.est_ouest = strtok (NULL, separateur);
				}		
				while ( strToken != NULL ) {
        // On demande le token suivant.
        strToken = strtok ( NULL, separateur );
				}
		}
		
		else if (retour_val_GPGGAb == NULL) 	// Renvo
		{
			strToken = strtok(MessageRecu.data, separateur);
			 
			if (strToken != NULL)
				{
					Coordonnee.temps 		 = strtok (NULL, separateur); 
					Coordonnee.latitude  = strtok (NULL, separateur);
				  Coordonnee.nord_sud  = strtok (NULL, separateur);
				  Coordonnee.longitude = strtok (NULL, separateur);
				  Coordonnee.est_ouest = strtok (NULL, separateur);
				}			
				while ( strToken != NULL ) {
        // On demande le token suivant.
        strToken = strtok ( NULL, separateur );
				}
		}
		
		osMessageQueuePut(ID_BAL_EMET_CAN,&Coordonnee , NULL, osWaitForever);
	}
}

void thread_EmissionCAN(void *argument)
{
	(void)argument;
	
	DataCoordonnee Coordonnee;
	ARM_CAN_MSG_INFO tx_msg_info;
	char *ptr;
	uint8_t data_buff_temps[8];
	uint8_t data_buff_latitude[8];
	uint8_t data_buff_longitude[8];
	uint16_t i = 0;
	
	while(1)
	{
		osMessageQueueGet(ID_BAL_EMET_CAN, &Coordonnee, NULL, osWaitForever);		// Reception du BAL du thread decode
		
		tx_msg_info.id = ARM_CAN_STANDARD_ID(0x0F6);
		tx_msg_info.rtr = 0;
		
		data_buff_temps[0] = *Coordonnee.temps;
		data_buff_temps[1] = *(Coordonnee.temps+1);
		data_buff_temps[2] = *(Coordonnee.temps+2);
		data_buff_temps[3] = *(Coordonnee.temps+3);
		data_buff_temps[4] = *(Coordonnee.temps+4);
		data_buff_temps[5] = *(Coordonnee.temps+5);
		
		data_buff_latitude[0]= *Coordonnee.latitude;
		data_buff_latitude[1]= *(Coordonnee.latitude+1);
		data_buff_latitude[2]= *(Coordonnee.latitude+2);
		data_buff_latitude[3]= *(Coordonnee.latitude+3);
		
		data_buff_longitude[0]= *Coordonnee.longitude;
		data_buff_longitude[1]= *(Coordonnee.longitude+1);
		data_buff_longitude[2]= *(Coordonnee.longitude+2);
		data_buff_longitude[3]= *(Coordonnee.longitude+3);
		data_buff_longitude[4]= *(Coordonnee.longitude+4);
		
		
		Driver_CAN2.MessageSend(1, &tx_msg_info, data_buff_temps, 6); 
//		osDelay(10);
//		Driver_CAN2.MessageSend(1, &tx_msg_info, data_buff_latitude, 4);
////		osDelay(10);
//		Driver_CAN2.MessageSend(1, &tx_msg_info, data_buff_longitude, 5);
		
		osThreadFlagsWait(0x0002, osFlagsWaitAll, osWaitForever);
		osDelay(100);
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
	ID_BAL_EMET_CAN = osMessageQueueNew(10, sizeof(DataCoordonnee), NULL);
	
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
	
//	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE)
//	{
//		 // On vérifie si on vient de recevoir le caractère de fin de trame
//		if (Message.data[idx] == '\n') 
//		{
//			//Message.data[idx + 1] = '\0'; // Fin de chaîne 
////			idx=0;
//			
//			osThreadFlagsSet(ID_ReceptUART, 0x0001); // reveille la reception
//		}
//		else
//		{
//			if (idx < 100)
//			{
//				idx++;
//				Driver_USART3.Receive(&Message.data[idx], 1);
//			}
//		}
//	}
	
	
//	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE)
//	{
//	
//		if ( (Message.data[idx] != '\n') && (idx < 100) )
//		{
//			idx++;
//			Driver_USART3.Receive(&Message.data[idx], 1);
//		}
//		else 
//		{
//			osThreadFlagsSet(ID_ReceptUART, 0x0001); // reveille la reception
//		}
//		}
//	

	if (event & ARM_USART_EVENT_RECEIVE_COMPLETE)
	{
		if (idx == 0)
		{
			if(Message.data[idx] == '$') idx++;
			Driver_USART3.Receive(&Message.data[idx], 1);
		}
		else
		{
			if( (idx != 0) && (Message.data[idx] != '\n') )
			{		
				idx++;
				Driver_USART3.Receive(&Message.data[idx], 1);
			}
			else if ( (idx !=0) && (Message.data[idx] == '\n') ) osThreadFlagsSet(ID_ReceptUART, 0x0001); // reveille la reception
		}
		
		
		
		
	}
		
		
		
	
//	
//	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE)
//	{
//		if (Message.data[idx] == '$')
//		{
//			if (Message.data[idx] != '\n')
//			{
//				idx++;
//				Driver_USART3.Receive(&Message.data[idx], 1);
//			}
//			
//		}
//	else 
//	{
//		idx = 0;
//		osThreadFlagsSet(ID_ReceptUART, 0x0001); // reveille la reception
//	}
//		
		
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
														ARM_CAN_BIT_PROP_SEG(5U) 	 |
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