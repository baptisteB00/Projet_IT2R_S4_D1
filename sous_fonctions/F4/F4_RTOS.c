#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"
#include "Driver_SPI.h"                 // CMSIS Driver:SPI
#include "RTE_Components.h"
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source


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

// Déclarations Externes
extern ARM_DRIVER_USART Driver_USART1;
extern ARM_DRIVER_SPI Driver_SPI1;

// Variables partagées entre la fonction d'interruption interne au driver et le main
// volatile car badge_complet est modifié dans le Callback (=>nécessité de stockage dans la ram)
uint8_t buffer_rfid[14]; 
uint32_t tab[62];

// Prototypes
void My_USART_Callback(unsigned int event);
void Init_UART(void);
void Init_SPI(void);
void Identification(unsigned char badge_maitre[], uint8_t recu[]);
void allumer_led(int n);
void eteindre_led(int n);
void Init_LEDs(void);
void Clignotants1(void);
void PharesAvant(void);
void allumer1LED(uint8_t numLED,uint32_t COLOR);
void eteindre1LED(uint8_t numLED);

//Tâches
osThreadId_t tid_mySPI_Thread, ID_Allumer1, ID_TRFID, ID_PharesAvant,ID_Clignotants1;
osThreadAttr_t configTRFID = {.priority = osPriorityHigh}, configTSPI = {.priority = osPriorityNormal};

void tacheRFID(void *arg){
	unsigned char badge_maitre[12] = {0x33,0x43,0x30,0x30,0x34,0x44,0x39,0x35,0x44,0x32,0x33,0x36};
	Driver_USART1.Receive(buffer_rfid, 14);
	while (1) {
		allumer_led(led_orange);
		allumer_led(led_bleue);
		Driver_USART1.Receive(buffer_rfid, 14);
		osThreadFlagsWait((1<<0), osFlagsWaitAll, osWaitForever);
		// On traite le badge reçu
		Identification(badge_maitre, buffer_rfid);
	}
}
void PharesAvant(void){
  while (1) {
		allumer1LED(25,BLANC);
		allumer1LED(24,BLANC);
		allumer1LED(23,BLANC);

		allumer1LED(35,BLANC);
		allumer1LED(36,BLANC);
		allumer1LED(37,BLANC);

		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
  }
}

void Clignotants1(void){
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
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osDelay(500);
		
		eteindre1LED(15);
		eteindre1LED(45);
		
		Driver_SPI1.Send(tab,(NbLEDs+2)*4);
		osDelay(500);
		//osThreadFlagsSet((osThreadId_t)ID_PharesAvant,0x10);
  }
}

// Fonction de callback (évite l'écriture d'une fonction d'interruption en utilisant une configurée préalablement dans le driver UART)
void My_USART_Callback(unsigned int event) {
    if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
				osThreadFlagsSet((osThreadId_t)ID_TRFID, (1<<0));
    }
}

//Main
int main(void) {
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO
		GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
		GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
		GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
		GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
		GPIOD->BSRR = 0; //Eteindre toutes les LEDs sur la carte
		Init_LEDs();
    Init_UART();
		Init_SPI();
	
		osKernelInitialize();
	  ID_TRFID = osThreadNew(tacheRFID, NULL, NULL);
		ID_PharesAvant = osThreadNew ((osThreadId_t)PharesAvant,NULL,NULL);
		ID_Clignotants1 = osThreadNew((osThreadId_t)Clignotants1,NULL,NULL);
	
		osKernelStart();
}

// Initialisation
void Init_UART(void) {
    // Initialisation de l'UART via le Driver CMSIS
    Driver_USART1.Initialize(My_USART_Callback); // Liaison du Callback
    Driver_USART1.PowerControl(ARM_POWER_FULL);
    Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS |
                          ARM_USART_DATA_BITS_8       |
                          ARM_USART_STOP_BITS_1       |
                          ARM_USART_PARITY_NONE, 9600);
    Driver_USART1.Control(ARM_USART_CONTROL_RX, 1); // Activer la réception
		Driver_USART1.Control(ARM_USART_CONTROL_TX, 1); // Activer la transmission
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

//Badge
void Identification(unsigned char chaine[], uint8_t recu[]) {
    int i, b = 0;
    
    for(i=1; i<13; i++) {
        if (chaine[i-1] == recu[i]) b++;
    }

    if (b == 12){
			osThreadFlagsSet((osThreadId_t)ID_Clignotants1, (1<<0));
			Driver_USART1.Send("1",1); 
			eteindre_led(led_orange);
			eteindre_led(led_rouge);
			allumer_led(led_verte);
			osDelay(1000);
			eteindre_led(led_verte);
		}
		
    else{
			osThreadFlagsSet((osThreadId_t)ID_Clignotants1, (1<<1));
			Driver_USART1.Send("0",1);
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