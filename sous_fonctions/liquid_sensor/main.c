#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "adc_F4.h"
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source

ADC_HandleTypeDef ADC8_Hand;
extern ARM_DRIVER_CAN Driver_CAN2;

/*------ ID des tâches ------*/

osThreadId_t ID_ReceptData;
osThreadId_t ID_Traitement;

/*------ ID des BAL ------*/

osMessageQueueId_t ID_BAL_DATA_RECEPT;
osMessageQueueId_t ID_BAL_EMISSION_CAN;

/*------ Variable global ------*/

typedef struct 
{
	uint32_t valeur_capteur;
	float liquid_level;
}	SensorLiquid;

/*------ Prototypes fonctions ------*/

float ConvertToCm(uint32_t mesure);

/*------ Tâches ------*/

void Thread_ReceptData(void * argument)
{
	(void)argument; 
	
	SensorLiquid donnee_capteur;

	while(1)
	{
		HAL_ADC_Start(&ADC8_Hand); 			// Début de la conversion ADC
		
		 if (HAL_ADC_PollForConversion(&ADC8_Hand, 10) == HAL_OK)
        {
            // Lire la valeur brute du capteur
            donnee_capteur.valeur_capteur = HAL_ADC_GetValue(&ADC8_Hand);
            
            // Envoyer à la file de messages pour traitement
            osMessageQueuePut(ID_BAL_DATA_RECEPT, &donnee_capteur, 0, osWaitForever);
        }

//		HAL_ADC_ConvCpltCallback(&ADC8_Hand); // Callback fonctionnelle ???
				
		HAL_ADC_Stop(&ADC8_Hand);
		
		osDelay(100);
	}
}

void Thread_Traitement(void * argument)
{
	(void) argument;
	
	SensorLiquid donnee_a_traiter;
	osStatus_t statut;


	while(1)
	{
		statut = osMessageQueueGet(ID_BAL_DATA_RECEPT, &donnee_a_traiter, NULL, osWaitForever);	// Reception BAL du thread ReceptData
		
		 if (statut == osOK)
        {
            // Conversion de la valeur brute en centimètres
            donnee_a_traiter.liquid_level = ConvertToCm(donnee_a_traiter.valeur_capteur);
            
            // Ici, je peux ajouter la logique du projet
            // Exemple : Envoyer vers le bus CAN si le niveau change
            osMessageQueuePut(ID_BAL_EMISSION_CAN, &donnee_a_traiter, 0, 0);
        }

		
//		donnee_a_traiter.liquid_level = ConvertToCm(donnee_a_traiter.valeur_capteur);
		
		osDelay(100);
	}
}

osThreadAttr_t config_ReceptData = { .priority = osPriorityHigh };
osThreadAttr_t config_Traitement = { .priority = osPriorityNormal };

int main (void)
{
	SystemCoreClockUpdate();
	HAL_Init(); // Important pour initialiser les timers de délai
	osKernelInitialize();
	
	
	ADC_Initialize(&ADC8_Hand, 8);
		
	ID_BAL_DATA_RECEPT  = osMessageQueueNew(10, sizeof(SensorLiquid), NULL);
	ID_BAL_EMISSION_CAN = osMessageQueueNew(10, sizeof(SensorLiquid), NULL);
	
	ID_ReceptData = osThreadNew ((osThreadFunc_t) Thread_ReceptData , NULL , &config_ReceptData) ;
	ID_Traitement = osThreadNew ((osThreadFunc_t) Thread_Traitement , NULL , &config_Traitement) ;
	
//	while (1)
//	{
//		HAL_ADC_Start(&ADC8_Hand); 
//		
//		// Lecture de la valeur brute (0 à 4095)
//    valeur_sensor = HAL_ADC_GetValue(&ADC8_Hand);
//		valeur = ConvertToCm(valeur_sensor);
//		i++;
//	
//	
//	}
	osKernelStart();
	
	return 0;
}

float ConvertToCm(uint32_t mesure) {
	
		const uint32_t ADC_MIN = 9;  // Valeur lue quand le capteur est sec
    const uint32_t ADC_MAX = 4095; // Valeur lue quand le capteur est à 4.8cm
	
		if (mesure <= ADC_MIN) return 0.0f;
    else if (mesure >= ADC_MAX) return 4.8f;

		 // Calcul de la pente 
    // Niveau = (Mesure - Min) * (ProfondeurMax / (Max - Min))
    else return (float)(mesure - ADC_MIN) * (4.8f / (float)(ADC_MAX - ADC_MIN));
}

//    float voltage = (mesure * 3.3f) / 4096.0f;

//    if (voltage <= 0.05f) return 0.0f; // Seuil bas (Air)
//    
//    // Segment 1 : 0 à 0.5 cm (0V à 1.3V)
//    if (voltage <= 1.30f) {
//        return (voltage / 1.30f) * 0.5f;
//    }
//    // Segment 2 : 0.5 à 1.0 cm (1.3V à 1.53V)
//    if (voltage <= 1.53f) {
//        return 0.5f + ((voltage - 1.30f) * 0.5f) / (1.53f - 1.30f);
//    }
//    // Segment 3 : 1.0 à 4.8 cm (1.53V à 1.88V)
//    if (voltage <= 1.88f) {
//        return 1.0f + ((voltage - 1.53f) * 3.8f) / (1.88f - 1.53f);
//    }

//    return 4.8f; // Maximum physique du capteur
//}


