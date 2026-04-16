#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source
#include "Driver_CAN.h"

//LEDs STM32
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

//DFP
#define Son_Clignotants 0x01
#define Son_Demarrage 0x02
#define Son_Radar 0x03
#define Son_Klaxon 0x04
#define Son_Deverouillage 0x05

extern ARM_DRIVER_CAN Driver_CAN2;

void Init_CAN(void);
void Envoi_CAN(uint32_t ID, uint8_t data[], uint8_t rtr, uint8_t dlc);
void allumer_led(int n);
void eteindre_led(int n);
void Radars(void);

osThreadId_t ID_CANT, ID_TRadars;
osMessageQueueId_t MB_Radars;

typedef struct {                             
  uint16_t Buf[16];
  uint8_t Idx;
} MSGQUEUE_OBJ_t;
void Init_GPIO(void){
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
}

void CANT(void){
	uint8_t data[8];
	while(1){
		data[0] = (1<<0);
		data[1] = Son_Demarrage;
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		Envoi_CAN(ID_CAN_DFP, data, 0, 2);
	}
}

void Radars(void){
	uint16_t distD, distG;
	osMessageQueueGet(MB_Radars, &distG, NULL, osWaitForever);
	osMessageQueueGet(MB_Radars, &distD, NULL, osWaitForever);
	if (distG != 0){
		if ((distG < 25)){
			//osThreadFlagsSet(ID_DFP, (1<<3));
			allumer_led(led_orange);
			osDelay(distG*distG);
			eteindre_led(led_orange);
		}
	}
	if (distD != 0){
		if ((distD < 25)){
			//osThreadFlagsSet(ID_DFP, (1<<3));
			allumer_led(led_orange);
			osDelay(distG*distG);
			eteindre_led(led_orange);
		}
	}
}

void My_CAN_Callback (uint32_t obj_idx, uint32_t event) {
	MSGQUEUE_OBJ_t msg;
	ARM_CAN_MSG_INFO	msg_info;
	uint8_t data_buf[8];
	if (event & ARM_CAN_EVENT_RECEIVE) {
		Driver_CAN2.MessageRead(obj_idx, &msg_info, data_buf, 0);
		Driver_CAN2.MessageRead(0, &msg_info, data_buf, 4);
		if ((msg_info.id == ID_CAN_Radars_Avants)&&(msg_info.dlc == 4)){
			msg.Idx = 0;
			msg.Buf[0] = (uint16_t)((data_buf[0]<<8)|data_buf[1]);
			osMessageQueuePut(MB_Radars, &msg, NULL, osWaitForever);
			msg.Idx = 1;
			msg.Buf[0] = (uint16_t)((data_buf[0]<<8)|data_buf[1]);
			osMessageQueuePut(MB_Radars, &msg, NULL, osWaitForever);
		}
	}
}

void EXTI0_IRQHandler(void) {
	EXTI->PR = EXTI_PR_PR0; // Acquittement de l'interruption matériellement
	osThreadFlagsSet((osThreadId_t)ID_CANT, (1<<0));
}

int main(void) {
	//Init LEDs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO (LEDs)
	GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
	GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
	GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
	GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
	GPIOD->BSRR = 0; //Eteindre toutes les LEDs sur la carte
	
	Init_GPIO();
	Init_CAN();
	
	osKernelInitialize();

	ID_CANT = osThreadNew((osThreadId_t)CANT, NULL, NULL);
	ID_TRadars = osThreadNew((osThreadId_t)Radars, NULL, NULL);

	MB_Radars = osMessageQueueNew(16, sizeof(MSGQUEUE_OBJ_t), NULL);

	osKernelStart();
}

void Init_CAN (void) {
	Driver_CAN2.Initialize(NULL,NULL);
	Driver_CAN2.PowerControl(ARM_POWER_FULL);
	Driver_CAN2.SetMode(ARM_CAN_MODE_INITIALIZATION);
	Driver_CAN2.SetBitrate(
		  	ARM_CAN_BITRATE_NOMINAL, // débit fixe
			125000, // 125 kbits/s (LS)
			ARM_CAN_BIT_PROP_SEG(5U) | // prop. seg = 5 TQ
			ARM_CAN_BIT_PHASE_SEG1(1U) | // phase seg1 = 1 TQ
			ARM_CAN_BIT_PHASE_SEG2(1U) | // phase seg2 = 1 TQ
			ARM_CAN_BIT_SJW(1U) // Resync. Seg = 1 TQ
	);
	Driver_CAN2.ObjectSetFilter(0U, ARM_CAN_FILTER_ID_MASKABLE_ADD, ARM_CAN_STANDARD_ID(0x000), 0x7C0); // Masque autorisant les ID souhaitées
	Driver_CAN2.ObjectConfigure(2U, ARM_CAN_OBJ_TX); // TX en emmission
	Driver_CAN2.ObjectConfigure(0U, ARM_CAN_OBJ_RX); // RX en reception
	Driver_CAN2.SetMode(ARM_CAN_MODE_NORMAL);
	osDelay(10);
}

void Envoi_CAN(uint32_t ID, uint8_t data[], uint8_t rtr, uint8_t dlc){
	ARM_CAN_MSG_INFO msg_info;
	msg_info.id = ID;
	msg_info.dlc = dlc;
	msg_info.rtr = rtr;
	Driver_CAN2.MessageSend(2U, &msg_info, data, dlc);
	Driver_CAN2.MessageSend(0U, &msg_info, data, dlc);
}

void allumer_led(int n){
		GPIOD->BSRR |= (1<<n);
}

void eteindre_led(int n){
		GPIOD->BSRR |= (1<<(n+16));
}
