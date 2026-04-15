#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART
#include "cmsis_os2.h"                  // CMSIS:RTOS2
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Driver_CAN.h"                 // CMSIS Driver:CAN
#include "Driver_I2C.h"                 // CMSIS Driver:I2C
#include "adc_F4.h"

#include "string.h"
#include "stdio.h"

#define led_verte 12
#define led_orange 13
#define led_rouge 14
#define led_bleue 15

//ID CAN
#define ID_CAN_Radars_Avants 0x010
#define ID_CAN_Radars_Arrieres 0x011
#define ID_CAN_Lidar 0x012
#define ID_CAN_Panneau 0x013
#define ID_CAN_Nunchuk 0x020
#define ID_CAN_Vitesse 0x021
#define ID_CAN_LEDs 0x030
#define ID_CAN_Porte 0x031
#define ID_CAN_DFP 0x032
#define ID_CAN_Light_Sensor 0x033
#define ID_CAN_Liquid_Sensor 0x034
#define ID_CAN_GPS_Heure 0x035
#define ID_CAN_GPS_Lattitude 0x036
#define ID_CAN_GPS_Longitude 0x037

//RTOS
#define FlagTimeout 0x80000000

//Adresses Radars (I2C)
#define CAPTAvD 0xEA
#define CAPTAvG 0xEC

extern ARM_DRIVER_USART Driver_USART3; 
extern ARM_DRIVER_CAN Driver_CAN2;
extern ARM_DRIVER_I2C Driver_I2C1;

void Init_UART_GPS(void);
void UART_Callback_GPS(uint32_t event);
void Init_CAN_Emission(void);
void myCAN2_callback(uint32_t obj_idx, uint32_t event);
void Init_I2C(void);
void I2C_Callback(uint32_t event);
void write1byte(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t read1byte(uint8_t addr, uint8_t reg);
uint16_t get_distance(uint8_t addr);
void allumer_led(int n);
void eteindre_led(int n);
void RadarDroit(void);
void RadarGauche(void);
float ConvertToCm(uint32_t mesure);

bool verrouillage = 1;

ADC_HandleTypeDef ADC8_Hand;

/*-------------- Création des identifiants des tâches (ID) --------------*/

osThreadId_t ID_ReceptUART, ID_EmissionCAN, ID_Decode,ID_Radar_Gauche, ID_Radar_Droit, ID_Traitement, ID_ReceptData;

/*-------------- Créations des identifiants des boîte aux lettres (BAL) --------------*/

osMessageQueueId_t ID_BAL_DECODE, ID_BAL_EMET_CAN, MB_Radars, ID_BAL_DATA_RECEPT, ID_BAL_EMISSION_CAN;

typedef struct {
	uint8_t data[100];
} DataRecept;

typedef struct {                             
  uint16_t Buf[16];
  uint8_t Idx;
} MSGQUEUE_OBJ_t;

typedef struct {
	uint32_t valeur_capteur;
	uint8_t valeur_pourcentage;
	float liquid_level;
}	SensorLiquid;

typedef struct {
	char *temps;				//  RMC / GGA
	char *latitude;			//  RMC / GGA
	char *nord_sud;			//  RMC / GGA
	char *est_ouest;		//  RMC / GGA
	char *longitude;		//  RMC / GGA
	char *alerte;				//  RMC
} DataCoordonnee;


uint8_t idx=0;
DataRecept Message;

void Thread_ReceptData(void * argument) {
	SensorLiquid donnee_capteur;
	uint32_t flag;
	while(1) {
		osThreadFlagsWait((1<<0), osFlagsWaitAny, osWaitForever);
		HAL_ADC_Start(&ADC8_Hand); 			// Début de la conversion ADC
		
		while(HAL_ADC_PollForConversion(&ADC8_Hand, 1000) != HAL_OK);
		
    // Lire la valeur brute du capteur
    donnee_capteur.valeur_capteur = HAL_ADC_GetValue(&ADC8_Hand);
            
    // Envoyer à la file de messages pour traitement
    osMessageQueuePut(ID_BAL_DATA_RECEPT, &donnee_capteur, 0, osWaitForever);
		osThreadFlagsSet((osThreadId_t)ID_Traitement, (1<<0));
	}
}

void Thread_Traitement(void * argument) {
	SensorLiquid donnee_a_traiter;
	uint32_t flag;
	while(1) {
		osThreadFlagsWait((1<<0), osFlagsWaitAny, osWaitForever);
		osMessageQueueGet(ID_BAL_DATA_RECEPT, &donnee_a_traiter, NULL, osWaitForever);	// Reception BAL du thread ReceptData
     // Conversion de la valeur brute en centimètres
		donnee_a_traiter.liquid_level = ConvertToCm(donnee_a_traiter.valeur_capteur);
		donnee_a_traiter.valeur_pourcentage = (donnee_a_traiter.valeur_capteur * 100) /4095 ;
    osMessageQueuePut(ID_BAL_EMISSION_CAN, &donnee_a_traiter, 0, osWaitForever);
		osThreadFlagsSet((osThreadId_t)ID_EmissionCAN, (1<<4));
	}
}

void thread_ReceptUART(void *argument) {
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

void thread_Decode(void *argument) {
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
			osMessageQueuePut(ID_BAL_EMET_CAN,&Coordonnee , NULL, osWaitForever);
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
				i--;
			osMessageQueuePut(ID_BAL_EMET_CAN,&Coordonnee , NULL, osWaitForever);
		}
		i++;
	}
}

void thread_EmissionCAN(void *argument) {
	DataCoordonnee Coordonnee;
	SensorLiquid DataSensor; 	
	ARM_CAN_MSG_INFO tx_msg_info;
	uint32_t flag;

	while(1) {
		osMessageQueueGet(ID_BAL_EMET_CAN, &Coordonnee, NULL, osWaitForever);		// Reception du BAL du thread decode
		flag = osThreadFlagsWait((1<<0), osFlagsWaitAny, osWaitForever);
		if ((flag & (1<<1)) == (1<<1)){
			 // --- Envoi du temps ---
			tx_msg_info.id = ARM_CAN_STANDARD_ID(ID_CAN_GPS_Heure);
			tx_msg_info.rtr = 0; // Trame de données
			Driver_CAN2.MessageSend(2U, &tx_msg_info, (uint8_t*)Coordonnee.temps, 6);
			// Attente que le contrôleur CAN ait fini l'envoi
			osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		}
		if ((flag & (1<<2)) == (1<<2)){
			 // --- Envoi de la latitude ---
			tx_msg_info.id = ARM_CAN_STANDARD_ID(ID_CAN_GPS_Lattitude);
			Driver_CAN2.MessageSend(2U, &tx_msg_info, (uint8_t*)Coordonnee.latitude, 8);
			// Attente que le contrôleur CAN ait fini l'envoi
			osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		}
		if ((flag & (1<<3)) == (1<<3)){
			 // --- Envoi de la longitude ---
			tx_msg_info.id = ARM_CAN_STANDARD_ID(ID_CAN_GPS_Longitude);
			Driver_CAN2.MessageSend(2U, &tx_msg_info, (uint8_t*)Coordonnee.longitude, 8);
			// Attente que le contrôleur CAN ait fini l'envoi
			osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);		
		}
		if ((flag & (1<<4)) == (1<<4)){
			 // --- Envoi Liquid Sensor (%) ---
			osMessageQueueGet(ID_BAL_EMISSION_CAN, &DataSensor, NULL, osWaitForever);	
			tx_msg_info.id = ARM_CAN_STANDARD_ID(ID_CAN_Liquid_Sensor);
			tx_msg_info.rtr = 0;                         // Trame de données
			tx_msg_info.dlc = 1;     // 1 octet suffit pour 0-100%
			Driver_CAN2.MessageSend(2U, &tx_msg_info, (uint8_t*)DataSensor.valeur_pourcentage, 1);
			// Attente que le contrôleur CAN ait fini l'envoi
			osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);		
		}
	}
}

/*-------------- Priorité des threads --------------*/

osThreadAttr_t configReceptUART  = { .priority = osPriorityHigh };
osThreadAttr_t configEmissionCAN = { .priority = osPriorityBelowNormal };
osThreadAttr_t configDecode      = { .priority = osPriorityNormal };
osThreadAttr_t config_ReceptData = { .priority = osPriorityHigh };
osThreadAttr_t config_Traitement = { .priority = osPriorityNormal };


void RadarDroit(void){
	uint16_t distD = 0;
	while(1){
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		distD = get_distance(CAPTAvD);
		if (distD != 0){
			if ((distD < 25)){
				allumer_led(led_bleue);
				osDelay(distD*distD);
				eteindre_led(led_bleue);
			}
		}
	}
}

void RadarGauche(void){
	uint16_t distG=0;
	while(1){
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		distG = get_distance(CAPTAvG);
		if (distG != 0){
			if ((distG < 25)){
				allumer_led(led_orange);
				osDelay(distG*distG);
				eteindre_led(led_orange);
			}
		}
	}
}

int main() {
	//Init LEDs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO (LEDs)
	GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
	GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
	GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
	GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
	GPIOD->BSRR = 0; //Eteindre toutes les LEDs sur la carte
	
	SystemCoreClockUpdate();
	osKernelInitialize();     // Initialize CMSIS-RTOS
	
	Init_UART_GPS();					// Initialisation de l'UART3 pour le GPS
	Init_CAN_Emission();			// Initialisation du CAN2 pour l'émission
	
	ID_BAL_DECODE		= osMessageQueueNew(10, sizeof(DataRecept), NULL);
	ID_BAL_EMET_CAN = osMessageQueueNew(10, sizeof(DataCoordonnee), NULL);
	ID_BAL_EMISSION_CAN = osMessageQueueNew(10, sizeof(SensorLiquid), NULL);	
	ID_ReceptUART  = osThreadNew( (osThreadFunc_t) thread_ReceptUART , NULL , &configReceptUART) ;
	ID_EmissionCAN = osThreadNew( (osThreadFunc_t) thread_EmissionCAN , NULL , &configEmissionCAN) ;
	ID_Decode			 = osThreadNew( (osThreadFunc_t) thread_Decode , NULL , &configDecode) ;
	
	ID_Radar_Gauche = osThreadNew((osThreadId_t)RadarGauche, NULL, NULL);
	ID_Radar_Droit = osThreadNew((osThreadId_t)RadarDroit, NULL, NULL);
	ID_ReceptData = osThreadNew ((osThreadFunc_t) Thread_ReceptData , NULL , &config_ReceptData) ;
	ID_Traitement = osThreadNew ((osThreadFunc_t) Thread_Traitement , NULL , &config_Traitement) ;
	
	osKernelStart();                      // Start thread execution
	return 0;
}

void Init_UART_GPS(void) {
	Driver_USART3.Initialize(UART_Callback_GPS);
	Driver_USART3.PowerControl(ARM_POWER_FULL);
	Driver_USART3.Control( ARM_USART_MODE_ASYNCHRONOUS |
												 ARM_USART_DATA_BITS_8			 |
												 ARM_USART_STOP_BITS_1			 |
												 ARM_USART_PARITY_NONE			 |
												 ARM_USART_FLOW_CONTROL_NONE, 9600);
	Driver_USART3.Control(ARM_USART_CONTROL_RX, 1);			// réception
}
	
void UART_Callback_GPS(uint32_t event) {
	
	if (event & ARM_USART_EVENT_RECEIVE_COMPLETE){
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
}

void Init_CAN_Emission(void) {
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

void myCAN2_callback(uint32_t obj_idx, uint32_t event) {
	ARM_CAN_MSG_INFO msg_info;
	uint8_t data_buf[8];
	if(event & ARM_CAN_EVENT_SEND_COMPLETE) osThreadFlagsSet(ID_EmissionCAN, (1<<0));
	if(event & ARM_CAN_EVENT_RECEIVE){
		Driver_CAN2.MessageRead(obj_idx, &msg_info, data_buf, 8);
		if(msg_info.rtr == 1){
			if(msg_info.id == ID_CAN_GPS_Heure) osThreadFlagsSet (ID_EmissionCAN, (1<<1));
			if(msg_info.id == ID_CAN_GPS_Lattitude) osThreadFlagsSet (ID_EmissionCAN, (1<<2));
			if(msg_info.id == ID_CAN_GPS_Longitude) osThreadFlagsSet (ID_EmissionCAN, (1<<3));
			if(msg_info.id == ID_CAN_Liquid_Sensor) osThreadFlagsSet (ID_ReceptData, (1<<0));
		}
	}
}

void Init_I2C_Radars(void) {
	Driver_I2C1.Initialize(I2C_Callback);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(	ARM_I2C_BUS_SPEED,				// 2nd argument = debit
							ARM_I2C_BUS_SPEED_STANDARD  );	// 100 kHz
//	Driver_I2C1.Control(	ARM_I2C_BUS_CLEAR,
//							0 );
}

void I2C_Callback(uint32_t event){
	if (event & ARM_I2C_EVENT_TRANSFER_DONE){
		
	}
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

void write1byte(unsigned char capt_addr, unsigned char reg, unsigned char val) {
    uint8_t tab[2];
		
		tab[0]= reg;
		tab[1]= val;
    Driver_I2C1.MasterTransmit(capt_addr, tab, 2, false); // Envoi START + ADDR_Slave+W + REG + DATA + STOP 
    //while (Driver_I2C1.GetStatus().busy == 1); // Attente fin de transmission physique 
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
}

uint8_t read1byte(uint8_t capt_addr, uint8_t reg) {
    uint8_t valeur;
    // Envoi de la sous-adresse avec RESTART (true) 
    Driver_I2C1.MasterTransmit(capt_addr, &reg, 1, true); 
    osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
	
    
    // Réception de l'octet 
    Driver_I2C1.MasterReceive(capt_addr, &valeur, 1, false);
    osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
    
    return valeur; 
}

// --- Fonction spécifique au SRF10 (Mesure + Attente ) ---
uint16_t get_distance(uint8_t capt_addr) {
    uint8_t high, low;
    
    // 1. Lancer la mesure en cm (Commande 0x51 dans registre 0) 
    write1byte(capt_addr, 0x00, 0x51);

    /* *ATTENTE DE CONVERSION : 
     * Le capteur ne répond pas pendant qu'il mesure (environ 65ms). 
     */ 
		osDelay(65);

    // 3. Lire les registres de distance 2 et 3 
    high = read1byte(capt_addr, 0x02);
    low  = read1byte(capt_addr, 0x03);
    
    return (uint16_t)((high << 8) | low); // Reconstruction 16-bits 
}

//LEDs
void allumer_led(int n){
		GPIOD->BSRR |= (1<<n);
}
void eteindre_led(int n){
		GPIOD->BSRR |= (1<<(n+16));
}