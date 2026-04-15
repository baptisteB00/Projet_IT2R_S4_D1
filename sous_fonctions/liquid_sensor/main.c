#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "adc_F4.h"
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Driver_CAN.h" // Driver spécifique CMSIS-Driver

ADC_HandleTypeDef ADC8_Hand;
extern ARM_DRIVER_CAN Driver_CAN2;

/*------ ID des tâches ------*/

osThreadId_t ID_ReceptData;
osThreadId_t ID_Traitement;
osThreadId_t ID_Emission_CAN;

/*------ ID des BAL ------*/

osMessageQueueId_t ID_BAL_DATA_RECEPT;
osMessageQueueId_t ID_BAL_EMISSION_CAN;

/*------ Variable global ------*/

typedef struct 
{
	uint32_t valeur_capteur;
	uint8_t valeur_pourcentage;
	float liquid_level;
}	SensorLiquid;

/*------ Prototypes fonctions ------*/

float ConvertToCm(uint32_t mesure);
void Init_CAN(void);
void myCAN2_callback(uint32_t obj_idx, uint32_t event);

/*------ Tâches ------*/

void Thread_ReceptData(void * argument)
{
	(void)argument; 
	
	SensorLiquid donnee_capteur;

	while(1)
	{
		HAL_ADC_Start(&ADC8_Hand); 			// Début de la conversion ADC
		
		while(HAL_ADC_PollForConversion(&ADC8_Hand, 1000) != HAL_OK);
		
    // Lire la valeur brute du capteur
    donnee_capteur.valeur_capteur = HAL_ADC_GetValue(&ADC8_Hand);
            
    // Envoyer à la file de messages pour traitement
    osMessageQueuePut(ID_BAL_DATA_RECEPT, &donnee_capteur, 0, osWaitForever);
        

//		HAL_ADC_ConvCpltCallback(&ADC8_Hand); // Callback fonctionnelle ???
				
		//HAL_ADC_Stop(&ADC8_Hand);
		osDelay(100);
	}
}

void Thread_Traitement(void * argument)
{
	(void) argument;
	
	SensorLiquid donnee_a_traiter;
//	uint8_t val;
	
	while(1)
	{
		osMessageQueueGet(ID_BAL_DATA_RECEPT, &donnee_a_traiter, NULL, osWaitForever);	// Reception BAL du thread ReceptData
	
     // Conversion de la valeur brute en centimètres
		donnee_a_traiter.liquid_level = ConvertToCm(donnee_a_traiter.valeur_capteur);
		donnee_a_traiter.valeur_pourcentage = (donnee_a_traiter.valeur_capteur * 100) /4095 ;
    osMessageQueuePut(ID_BAL_EMISSION_CAN, &donnee_a_traiter, 0, osWaitForever);
        
		osDelay(100);
	}
}

void Thread_Emission_CAN(void *argument)
{
	SensorLiquid DataSensor; 	
	
	// Structure pour les infos de la trame (ID, type, etc.)
	ARM_CAN_MSG_INFO tx_msg_info;
	
  uint8_t buffer_donnees[1]; // On envoie 1 seul octet pour le niveau
	
	while(1)
	{
		 osMessageQueueGet(ID_BAL_EMISSION_CAN, &DataSensor, NULL, osWaitForever);	
		 // Ici, je peux ajouter la logique du projet
		 tx_msg_info.id = ARM_CAN_STANDARD_ID(0x033); // Identifiant dU capteur
     tx_msg_info.rtr = 0;                         // Trame de données
     tx_msg_info.dlc = 1;     // 1 octet suffit pour 0-100%

            // Exemple : Envoyer vers le bus CAN si le niveau change
					
					// On envoie le niveau en pourcentage (0 à 100)
     buffer_donnees[0] = (uint8_t)(DataSensor.valeur_pourcentage );
		 Driver_CAN2.MessageSend(2U, &tx_msg_info, buffer_donnees, 1);
		
		 osThreadFlagsWait(0x0002, osFlagsWaitAll, osWaitForever);
	}
}

osThreadAttr_t config_ReceptData = { .priority = osPriorityHigh };
osThreadAttr_t config_Traitement = { .priority = osPriorityNormal };
osThreadAttr_t config_Emet_CAN = { .priority = osPriorityBelowNormal };

int main (void)
{
	SystemCoreClockUpdate();
	HAL_Init(); // Important pour initialiser les timers de délai
	osKernelInitialize();
	
	
	ADC_Initialize(&ADC8_Hand, 8);
	Init_CAN();
		
	ID_BAL_DATA_RECEPT  = osMessageQueueNew(10, sizeof(SensorLiquid), NULL);
	ID_BAL_EMISSION_CAN = osMessageQueueNew(10, sizeof(SensorLiquid), NULL);
	
	ID_ReceptData = osThreadNew ((osThreadFunc_t) Thread_ReceptData , NULL , &config_ReceptData) ;
	ID_Traitement = osThreadNew ((osThreadFunc_t) Thread_Traitement , NULL , &config_Traitement) ;
	ID_Emission_CAN = osThreadNew ((osThreadFunc_t) Thread_Emission_CAN , NULL , &config_Emet_CAN) ;
	
	osKernelStart();
	
	return 0;
}

float ConvertToCm(uint32_t mesure) {
	
//		const uint32_t ADC_MIN = 77;  // Valeur lue quand le capteur est sec
//    const uint32_t ADC_MAX = 3839; // Valeur lue quand le capteur est à 4.8cm
	
//		if (mesure <= ADC_MIN) return 0.0f;
//    else if (mesure >= ADC_MAX) return 4.8f;

		 // Calcul de la pente 
    // Niveau = (Mesure - Min) * (ProfondeurMax / (Max - Min))
//    return (float)((mesure  * 4.8) / 4095);
//}

   //float voltage = (mesure * 3.3) / 4095;
	
	if (mesure <= 397) return 0.0; // Seuil bas (Air)
    
    // Segment 1 : 0 à 0.5 cm (0V à 1.3V)
    else if ( (mesure > 397) && (mesure <= 2928) ) {
        return (mesure) / 2928;
    }
    // Segment 2 : 0.5 à 1.0 cm (1.3V à 1.53V)
    else if ( (mesure > 2928) && (mesure <= 3486) ) {
        return (mesure * 2) / 3486;
    }
    // Segment 3 : 1.0 à 4.8 cm (1.53V à 1.88V)
    else if ( (mesure > 3486) && (mesure <= 3598) ) {
        return (mesure * 3) / 3598; 
    }
		else if ( (mesure > 3598) && (mesure <= 3722) ) {
				return (mesure *4) / 3722;
		}
		else 
		{
			return (mesure *4.8) / 4095;
		}

//    if (voltage <= 0.05) return 0.0; // Seuil bas (Air)
//    
//    // Segment 1 : 0 à 0.5 cm (0V à 1.3V)
//    else if (voltage <= 1.30) {
//        return (voltage / 1.30) * 0.5;
//    }
//    // Segment 2 : 0.5 à 1.0 cm (1.3V à 1.53V)
//    else if (voltage <= 1.53) {
//        return 0.5+ ((voltage - 1.30) * 0.5) / (1.53 - 1.30);
//    }
//    // Segment 3 : 1.0 à 4.8 cm (1.53V à 1.88V)
//    else if (voltage <= 1.88) {
//        return 1.0 + ((voltage - 1.53) * 3.8) / (1.88 - 1.53);
    

//    return 4.8f; // Maximum physique du capteur
}

void Init_CAN(void)
{
	Driver_CAN2.Initialize(NULL, myCAN2_callback);
	Driver_CAN2.PowerControl(ARM_POWER_FULL);
	Driver_CAN2.SetMode(ARM_CAN_MODE_INITIALIZATION);
	Driver_CAN2.SetBitrate(ARM_CAN_BITRATE_NOMINAL, 125000,
														ARM_CAN_BIT_PROP_SEG(5U) 	 |
														ARM_CAN_BIT_PHASE_SEG1(1U) |
														ARM_CAN_BIT_PHASE_SEG2(1U) |
														ARM_CAN_BIT_SJW(1U));
	
	Driver_CAN2.ObjectConfigure(2U,ARM_CAN_OBJ_TX); // Objet 2 pour émission
	Driver_CAN2.SetMode(ARM_CAN_MODE_NORMAL); // fin initialisation
}

void myCAN2_callback(uint32_t obj_idx, uint32_t event)
{
	if(event & ARM_CAN_EVENT_SEND_COMPLETE) osThreadFlagsSet(ID_Emission_CAN, 0x0002);
}

