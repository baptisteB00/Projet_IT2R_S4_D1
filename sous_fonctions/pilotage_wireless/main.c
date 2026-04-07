/*------------------------------------
Projet IT2R 2026 S4
Auteurs : Alexandre Ho, Lucas VINCENTI
--------------------------------------
Programme acquisition Nunchuck - Multitache
-------------------------------------*/

/* ------------- Bibliotheques -------------------*/
#include "Driver_I2C.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "stdio.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "Driver_USART.h"       // Pour les fonctions UART 

/* ------------ Composants et police LCD ----------*/
#define NUNCHUCK_ADDR 0x52

extern ARM_DRIVER_I2C Driver_I2C2;
extern GLCD_FONT GLCD_Font_16x24;
extern ARM_DRIVER_USART Driver_USART1;

uint8_t data[6];
uint8_t data_transmit;

/* ------------ Prototypes des fonctions -----------*/
void Nunchuck_Init(void);
void USART_Init(void);

/* ------------ Parametres Threads -----------*/
osThreadId_t ID_Thread_Nunchuck; // Définition de l'identifiant de la tâche 
osThreadId_t ID_Thread_Bluetooth; // Définition de l'identifiant de la tâche 
//osThreadId_t ID_Thread_LCD; // Définition de l'identifiant de la tâche 

osMutexId_t mut_Nunchuck;
void Thread_Nunchuck(void const * argument); // Prototype de la fonction de la tâche 
void Thread_Bluetooth(void const * argument); // Prototype de la fonction de la tâche 
//void Thread_LCD(void const * argument); // Prototype de la fonction de la tâche 

osThreadAttr_t configT1 = {.priority = osPriorityNormal} ;
osThreadAttr_t configT2 = {.priority = osPriorityNormal} ;
//osThreadAttr_t configT3 = {.priority = osPriorityNormal} ;


/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN static void app_main (void *argument) {
  (void)argument;
  // ...
  for (;;) {}
}
 
int main (void) {
  // System Initialization
  SystemCoreClockUpdate();

	GLCD_Initialize();// Initialisation du LCD
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	Nunchuck_Init();// Initalisation et demarrage du Nunchuck
	USART_Init();
  osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	ID_Thread_Nunchuck = osThreadNew((osThreadFunc_t)Thread_Nunchuck, NULL, &configT1);
  ID_Thread_Bluetooth = osThreadNew((osThreadFunc_t)Thread_Bluetooth, NULL, &configT2);
	//ID_Thread_LCD = osThreadNew((osThreadFunc_t)Thread_LCD, NULL, &configT3);
	
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}

/* --------------------------------------------
Thread Nunchuck / Thread Bluetooth
----------------------------------------------*/

//Thread Nunchuck
void Thread_Nunchuck (void const* argument){
	(void)argument;
	char ligne1[32], ligne2[32], ligne3[32];
	while (1){
		osMutexAcquire(mut_Nunchuck,osWaitForever);
		uint8_t cmd = 0x00;
		
    // 1. Demande de lecture
    Driver_I2C2.MasterTransmit(NUNCHUCK_ADDR, &cmd, 1, false);
    while (Driver_I2C2.GetStatus().busy);
    // 2. Delay
    osDelay(5);
		
    // 3. Lecture des 6 octets
    Driver_I2C2.MasterReceive(NUNCHUCK_ADDR, data, 6, false);
    while (Driver_I2C2.GetStatus().busy);
		
		// --- Serialisation ---
		sprintf(ligne1, "ValJoy: X%02X Y%02X", data[0], data[1]);
		sprintf(ligne2, "ValBP: Z%01X C%01X", data[5]&0x01, (data[5]&0x02)>>1);
		
		// --- Affichage LCD ---
		GLCD_DrawString(1, 1,  (unsigned char*)ligne1);
		GLCD_DrawString(1, 40, (unsigned char*)ligne2);

		osMutexRelease(mut_Nunchuck);
	}
}

//Thread Nunchuck
void Thread_Bluetooth (void const* argument){
	(void)argument;
	char data_transmit[3]; // [ Direction --> -128° to 127° , vitesse --> -128 to 127], reversible avec valeur negative

		while (1){
		data_transmit[2] = data[5] & 0x03; // Lecture BP
			

		if ((data[0] == 0x85)& (data[1]== 0x7C )) { // Neutre
			data_transmit[0] = 0x00;
			data_transmit[1] = 0x00;
		}
		// Vitesse
		if(data[1] > 0x80){data_transmit[1] = 0x7F;}//Avance
		else if(data[1] < 0x6F){data_transmit[1] = 0x80;}//Recule
		//Direction
		if (((data[0] > 0x62)&(data[0] < 0x95))){data_transmit[0] = 0x00 ;} //devant
		else if (data[0] < 0x62){data_transmit[0] = 0x80;}// Droite
		else if (data[0] > 0x95){data_transmit[0] = 0x7F;}// Gauche
		
		Driver_USART1.Send(data_transmit,3);	
		while(Driver_USART1.GetTxCount() < 2);		
		osDelay(100);
	}
}

//Thread Afficheur
/*void Thread_LCD (void const* argument)
{
  (void) argument;
	while (1)
	{
		// --- Serialisation ---
		sprintf(ligne1, "ValJoy: X%02X Y%02X", data[0], data[1]);
		sprintf(ligne2, "ValBP: Z%01X C%01X", data[5]&0x01, (data[5]&0x02)>>1);
		sprintf(ligne3, "ValACC: X%02X Y%02X Z%02X", data[2], data[3], data[4]);
		
		// --- Affichage LCD ---
		GLCD_DrawString(1, 1,  (unsigned char*)ligne1);
		GLCD_DrawString(1, 40, (unsigned char*)ligne2);
		GLCD_DrawString(1, 80, (unsigned char*)ligne3);
	}
}
*/


/* --------------------------------------------
Fonctions d'initialisation Nunchuck + Bluetooth
----------------------------------------------*/
void Nunchuck_Init(void) {
    uint8_t init1[] = {0xF0, 0x55};
    uint8_t init2[] = {0xFB, 0x00};

    Driver_I2C2.Initialize(NULL);
    Driver_I2C2.PowerControl(ARM_POWER_FULL);
    Driver_I2C2.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);

    // 1. Init nunchuck
    Driver_I2C2.MasterTransmit(NUNCHUCK_ADDR, init1, 2, false);
    while (Driver_I2C2.GetStatus().busy);
    for (volatile int i = 0; i < 5000; i++); // Petit délai

    // 2.Désactive le chiffrement (ne change rien, activer ou non)
    Driver_I2C2.MasterTransmit(NUNCHUCK_ADDR, init2, 2, false);
    while (Driver_I2C2.GetStatus().busy);
    for (volatile int i = 0; i < 5000; i++); 
}

void USART_Init(void){
		Driver_USART1.Initialize(NULL);
	Driver_USART1.PowerControl(ARM_POWER_FULL);
	Driver_USART1.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		|
							ARM_USART_FLOW_CONTROL_NONE,
							115200);
	Driver_USART1.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART1.Control(ARM_USART_CONTROL_RX,1);

}	