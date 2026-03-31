#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"
#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "Driver_I2C.h"                 // ::CMSIS Driver:I2C
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "RTE_Components.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "stdio.h"
#include "adc_F4.h"

#define led_verte 12
#define led_orange 13
#define led_rouge 14
#define led_bleue 15

#define ATTENTE -1
#define AUTORISE 1
#define REFUSE 0

# define VERT 0x00FF00F0
# define ROUGE 0xFF0000F0
# define BLEU 0x0000FFF0
# define ORANGE
# define BLANC 0xFFFFFFFE
# define JAUNE 0xFF00FFF0

# define Eteint 0x000000E0
# define NbLEDs 60

#define Son_Clignotants 0x01
#define Son_Demarrage 0x02
#define Son_Radar 0x03
#define Son_Klaxon 0x04
#define Son_Deverouillage 0x05

#define CAPTAvD 0x70 //0xE0
#define CAPTAvG 0x71 //0xE2

// Déclarations Externes
extern ARM_DRIVER_USART Driver_USART2;
extern ARM_DRIVER_USART Driver_USART3;
extern ARM_DRIVER_SPI Driver_SPI1;
extern ARM_DRIVER_I2C Driver_I2C1;

// Variables partagées entre la fonction d'interruption interne au driver et le main
// volatile car badge_complet est modifié dans le Callback (=>nécessité de stockage dans la ram)
uint8_t buffer_rfid[14]; 
uint32_t tab[62];

ADC_HandleTypeDef ADC1_Hand;

// Prototypes
void My_USART_Callback(unsigned int event);
void Init_UART(void);
void Init_SPI(void);
void Identification(unsigned char badge_maitre[], uint8_t recu[]);
void allumer_led(int n);
void eteindre_led(int n);
void Init_LEDs(void);
void Clignotants(void);
void Phares(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);
void sendDFCommand(uint8_t cmd, uint8_t para1, uint8_t para2);
void Init_I2C(void);
void write1byte(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t read1byte(uint8_t addr, uint8_t reg);
uint16_t get_distance(uint8_t addr);

//Tâches
osThreadId_t tid_mySPI_Thread, ID_Allumer1, ID_RFID, ID_Phares, ID_Clignotants, ID_DFP, ID_Klaxon, ID_Sensorlight, ID_Radar_Droit, ID_Radar_Gauche;
osMutexId_t MUT_EnvoiSPI, MUT_DFP, MUT_I2C;
osSemaphoreId_t ADCSemaphore;

void tacheRFID(void *arg){
	unsigned char badge_maitre[12] = {0x33,0x43,0x30,0x30,0x34,0x44,0x39,0x35,0x44,0x32,0x33,0x36};
	Driver_USART2.Receive(buffer_rfid, 14);
	while (1) {
		allumer_led(led_orange);
		Driver_USART2.Receive(buffer_rfid, 14);
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		Identification(badge_maitre, buffer_rfid);		// On traite le badge reçu ici
	}
}
void Phares(void){
	uint32_t flag;
  while (1) {
		flag = osThreadFlagsWait(0x06, osFlagsWaitAny, osWaitForever);
		if (flag == (1<<1)){
			allumer1LED(25,BLANC);
			allumer1LED(24,BLANC);
			allumer1LED(23,BLANC);

			allumer1LED(35,BLANC);
			allumer1LED(36,BLANC);
			allumer1LED(37,BLANC);
		}
		else if (flag == (1<<2)){
			eteindre1LED(25);
			eteindre1LED(24);
			eteindre1LED(23);

			eteindre1LED(35);
			eteindre1LED(36);
			eteindre1LED(37);
		}
		osMutexAcquire(MUT_EnvoiSPI, osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(MUT_EnvoiSPI);
  }
}

void Clignotants(void){
	uint32_t flag;
  while (1) {
		flag = osThreadFlagsWait (((1<<0)|(1<<1)),osFlagsWaitAny,osWaitForever);
		if (flag == (1<<0)){
			allumer1LED(15,VERT);
			allumer1LED(45,VERT);
		}
		else if (flag == (1<<1)){
			allumer1LED(15,ROUGE);
			allumer1LED(45,ROUGE);
		}
		else if (flag == (1<<2)){
			allumer1LED(15,BLANC);
			allumer1LED(45,BLANC);
			osThreadFlagsSet(ID_DFP, (1<<2));
		}
		osMutexAcquire(MUT_EnvoiSPI, osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(MUT_EnvoiSPI);
		osDelay(500);
		
		eteindre1LED(15);
		eteindre1LED(45);
		
		osMutexAcquire(MUT_EnvoiSPI, osWaitForever);
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osMutexRelease(MUT_EnvoiSPI);
		osDelay(500);
  }
}

void DFP(void){
		uint32_t flag;
		// 1.Reset le module	(0x0C, param: 0x0000)
		sendDFCommand(0x0C, 0x00, 0x00);
    osDelay(200);
		// 2. Spécifier la source de lecture : Carte SD (0x09, param: 0x01) 
		sendDFCommand(0x09, 0x00, 0x15);
    osDelay(25); // Délai nécessaire après sélection de la source 
		// 3. Régler le volume à 15 (0x06, param: 0x0F) 
    sendDFCommand(0x06, 0x00, 0x15);
    osDelay(25);
		while(1){
			flag = osThreadFlagsWait(0xFFFF, osFlagsWaitAny, osWaitForever);
			if (flag == (1<<0)){
				sendDFCommand(0x03, 0x00, Son_Deverouillage);
			}
			else if(flag == (1<<1)){
				sendDFCommand(0x03, 0x00, Son_Klaxon);
			}
			else if(flag == (1<<2)){
				sendDFCommand(0x03, 0x00, Son_Clignotants);
			}
			else if(flag == (1<<3)){
				sendDFCommand(0x03, 0x00, Son_Radar);
			}
		}
}

void SensorLight(void){
	int valeur;
	while(1){
		HAL_ADC_Start(&ADC1_Hand);
		while(HAL_ADC_PollForConversion(&ADC1_Hand, 1000) != HAL_OK);
		valeur = HAL_ADC_GetValue(&ADC1_Hand);
    if (valeur < 4095) {
			osThreadFlagsSet(ID_Phares, (1<<1)); 
		}
		else{
			osThreadFlagsSet(ID_Phares, (1<<2));
		}
	}
}

void RadarDroit(void){
	uint16_t distD=0;
	while(1){
		//osMutexAcquire(MUT_I2C, osWaitForever);
		distD = get_distance(CAPTAvD);
		if (distD != 0){
			if ((distD < 25)){
				//osThreadFlagsSet(ID_DFP, (1<<3));
				allumer_led(led_rouge);
				osDelay(50*distD);
				eteindre_led(led_rouge);
			}
		}
		//osMutexRelease(MUT_I2C);
	}
}

void RadarGauche(void){
	uint16_t distG=0;
	while(1){
		//osMutexAcquire(MUT_I2C, osWaitForever);
		distG = get_distance(CAPTAvG);
		if (distG != 0){
			if ((distG < 25)){
				//osThreadFlagsSet(ID_DFP, (1<<3));
				allumer_led(led_verte);
				osDelay(50*distG);
				eteindre_led(led_verte);
			}
		}
		//osMutexRelease(MUT_I2C);
	}
}

// Fonction de callback (évite l'écriture d'une fonction d'interruption en utilisant une configurée préalablement dans le driver UART)
void My_USART_Callback(unsigned int event) {
    if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
				osThreadFlagsSet(ID_RFID, (1<<0));
    }
}

void EXTI0_IRQHandler(void) {
		osThreadFlagsSet(ID_DFP, (1<<1));
    EXTI->PR = EXTI_PR_PR0; // Acquittement de l'interruption matériellement
}

//Main
int main(void) {
		//Init LEDs
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO (LEDs)
		GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
		GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
		GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
		GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
		GPIOD->BSRR = 0; //Eteindre toutes les LEDs sur la carte
		
		//Init Bouton (en interruption)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable the clock of port D of the GPIO (Bouton)
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Activer horloge système config
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0; // Relier EXTI0 à PA0
    EXTI->IMR |= EXTI_IMR_MR0;    // Démasquer l'interruption 0
    EXTI->RTSR |= EXTI_RTSR_TR0;  // Front montant (Rising Edge)
    NVIC_EnableIRQ(EXTI0_IRQn);   // Activer dans le NVIC
	
		ADC_Initialize(&ADC1_Hand,1);
	
		Init_LEDs();
    Init_UART();
		Init_SPI();
		HAL_Init();
		Init_I2C();
	
		osKernelInitialize();
	  ID_RFID = osThreadNew(tacheRFID, NULL, NULL);
		ID_Phares = osThreadNew ((osThreadId_t)Phares, NULL, NULL);
		ID_Clignotants = osThreadNew((osThreadId_t)Clignotants, NULL, NULL);
		ID_DFP = osThreadNew((osThreadId_t)DFP, NULL, NULL);
		ID_Sensorlight = osThreadNew((osThreadId_t)SensorLight, NULL, NULL);
		ID_Radar_Gauche = osThreadNew((osThreadId_t)RadarGauche, NULL, NULL);
		ID_Radar_Droit = osThreadNew((osThreadId_t)RadarDroit, NULL, NULL);
		
		
		MUT_EnvoiSPI = osMutexNew(NULL);
		MUT_DFP = osMutexNew(NULL);
		MUT_I2C = osMutexNew(NULL);
		ADCSemaphore = osSemaphoreNew(1, 0, NULL);
	
		osKernelStart();
}

// Initialisation
void Init_UART(void) {
    // Initialisation de l'UART2 via le Driver CMSIS
    Driver_USART2.Initialize(My_USART_Callback); // Liaison du Callback
    Driver_USART2.PowerControl(ARM_POWER_FULL);
    Driver_USART2.Control(ARM_USART_MODE_ASYNCHRONOUS |
                          ARM_USART_DATA_BITS_8       |
                          ARM_USART_STOP_BITS_1       |
                          ARM_USART_PARITY_NONE, 9600);
    Driver_USART2.Control(ARM_USART_CONTROL_RX, 1); // Activer la réception
		Driver_USART2.Control(ARM_USART_CONTROL_TX, 1); // Activer la transmission
	
		// Initialisation de l'UART3 via le Driver CMSIS
    Driver_USART3.Initialize(My_USART_Callback); // Liaison du Callback
    Driver_USART3.PowerControl(ARM_POWER_FULL);
    Driver_USART3.Control(ARM_USART_MODE_ASYNCHRONOUS |
                         ARM_USART_DATA_BITS_8       |
                          ARM_USART_STOP_BITS_1       |
                          ARM_USART_PARITY_NONE, 9600);
    Driver_USART3.Control(ARM_USART_CONTROL_RX, 1); // Activer la réception
		Driver_USART3.Control(ARM_USART_CONTROL_TX, 1); // Activer la transmission
}

void Init_SPI(void){
	Driver_SPI1.Initialize(NULL);
	Driver_SPI1.PowerControl(ARM_POWER_FULL);
	Driver_SPI1.Control(ARM_SPI_MODE_MASTER | 
											//ARM_SPI_CPOLXX_CPHAXX |   // Choisir en fonction datasheet
											ARM_SPI_MSB_LSB | 
											ARM_SPI_SS_MASTER_UNUSED |
											ARM_SPI_DATA_BITS(8), 1000000);
	Driver_SPI1.Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
	NVIC_SetPriority(SPI1_IRQn,2);
}

void Init_I2C(void){
	Driver_I2C1.Initialize(NULL);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(	ARM_I2C_BUS_SPEED,				// 2nd argument = debit
							ARM_I2C_BUS_SPEED_STANDARD  );	// 100 kHz
//	Driver_I2C1.Control(	ARM_I2C_BUS_CLEAR,
//							0 );
}
//Badge
void Identification(unsigned char chaine[], uint8_t recu[]) {
    int i, b = 0;
    
    for(i=1; i<13; i++) {
        if (chaine[i-1] == recu[i]) b++;
    }

    if (b == 12){
			osThreadFlagsSet((osThreadId_t)ID_Clignotants, (1<<0));
			osThreadFlagsSet((osThreadId_t)ID_DFP, (1<<0));
			eteindre_led(led_orange);
			eteindre_led(led_rouge);
			allumer_led(led_verte);
			osDelay(1000);
			eteindre_led(led_verte);
		}
		
    else{
			osThreadFlagsSet((osThreadId_t)ID_Clignotants, (1<<1));
			eteindre_led(led_orange);
			eteindre_led(led_verte);
			allumer_led(led_rouge);
			osDelay(125);
			eteindre_led(led_rouge);
			osDelay(125);
			allumer_led(led_rouge);
			osDelay(125);
			eteindre_led(led_rouge);
			osDelay(125);
			allumer_led(led_rouge);
			osDelay(125);
			eteindre_led(led_rouge);
		}
}

// Envoi DFP
void sendDFCommand(uint8_t cmd, uint8_t para1, uint8_t para2) {
    char packet[10];
    short checksum;
		int i;
		osMutexAcquire(MUT_DFP, osWaitForever);
    packet[0] = 0x7E;          // Start byte 
    packet[1] = 0xFF;          // Version 
    packet[2] = 0x06;          // Data length 
    packet[3] = cmd;           // Command ID 
    packet[4] = 0x00;          // Feedback (0x00 = No, 0x01 = Yes) 
    packet[5] = para1;         // Parameter high byte 
    packet[6] = para2;         // Parameter low byte 
    
    // Calcul du Checksum : 0xFFFF - (VER + Len + CMD + Feedback + Para1 + Para2) + 1
    checksum = 0xffff - (packet[1] + packet[2] + packet[3] + packet[4] + packet[5] + packet[6])+1;
    
    packet[7] = (uint8_t)(checksum >> 8); // Checksum high byte 
    packet[8] = (uint8_t)(checksum & 0xFF); // Checksum low byte
    packet[9] = 0xEF;          // End byte 

	for (i=0;i<10;i++)
	{
    Driver_USART3.Send(&packet[i], 1); // Tx sur pin PC11
		osDelay(2);
	}
	osMutexRelease(MUT_DFP);
	osDelay(500);
}

//LEDs
void allumer_led(int n){
		GPIOD->BSRR |= (1<<n);
}
void eteindre_led(int n){
		GPIOD->BSRR |= (1<<(n+16));
}

void allumer1LED(uint8_t numLED, uint32_t COLOR){
	tab[numLED]=COLOR;
}

void eteindre1LED(uint8_t numLED){
	tab[numLED]=Eteint;
}

void Init_LEDs(void){
	int i;
	tab[0]=0;
	tab[61]=0xFFFFFFFF;
	for(i=0;i<60;i++){
	tab[i] = Eteint;
	}
}

void write1byte(unsigned char capt_addr, unsigned char reg, unsigned char val) {
    uint8_t tab[2];
		
		tab[0]= reg;
		tab[1]= val;
    Driver_I2C1.MasterTransmit(capt_addr, tab, 2, false); // Envoi START + ADDR_Slave+W + REG + DATA + STOP 
    while (Driver_I2C1.GetStatus().busy == 1); // Attente fin de transmission physique 
}

uint8_t read1byte(uint8_t capt_addr, uint8_t reg) {
    uint8_t valeur;
    // Envoi de la sous-adresse avec RESTART (true) 
    Driver_I2C1.MasterTransmit(capt_addr, &reg, 1, true); 
    while (Driver_I2C1.GetStatus().busy == 1);
	
    
    // Réception de l'octet 
    Driver_I2C1.MasterReceive(capt_addr, &valeur, 1, false);
    while (Driver_I2C1.GetStatus().busy == 1);
    
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