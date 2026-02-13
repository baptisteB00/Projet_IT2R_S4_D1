#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Device:STM32Cube HAL:Common
#include "Driver_USART.h"
#include "RTE_Components.h"

// Déclarations Externes
extern ARM_DRIVER_USART Driver_USART1;

// Variables partagées entre la fonction d'interruption interne au driver et le main
// volatile car badge_complet est modifié dans le Callback (=>nécessité de stockage dans la ram)
volatile bool badge_complet = false; 
uint8_t buffer_rfid[14]; 

// Prototypes
void My_USART_Callback(unsigned int event);
void Init_Systeme(void);
int Identification(unsigned char badge_maitre[], uint8_t recu[]);

// Fonction de callback (évite l'écriture d'une fonction d'interruption en utilisant une configurée pralablement dans le driver UART)
void My_USART_Callback(unsigned int event) {
    if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
        badge_complet = true; // Préviens qu'une trame prête à être lue
    }
}

// Initialisation
void Init_Systeme(void) {
    // Initialisation de l'UART via le Driver CMSIS
    Driver_USART1.Initialize(My_USART_Callback); // Liaison du Callback
    Driver_USART1.PowerControl(ARM_POWER_FULL);
    Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS |
                          ARM_USART_DATA_BITS_8       |
                          ARM_USART_STOP_BITS_1       |
                          ARM_USART_PARITY_NONE, 9600);
    Driver_USART1.Control(ARM_USART_CONTROL_RX, 1); // Activer la réception
}

int main(void) {
    unsigned char badge_maitre[12] = {0x33,0x43,0x30,0x30,0x34,0x44,0x39,0x35,0x44,0x32,0x33,0x36};
    int ouverture = 0, i;
		
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO
		GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
		GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
		GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
		GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
		
    Init_Systeme();
		
		Driver_USART1.Receive(buffer_rfid, 14);

    while (1) {
			 GPIOD->BSRR = 1<<13; // Set the BSRR bit X to 1 to turn respective LED on
       if (badge_complet) {
           // On traite le badge reçu
           ouverture = Identification(badge_maitre, buffer_rfid);
				 
					if (ouverture == 1){
						GPIOD->BSRR = 1<<12; // Set the BSRR bit X to 1 to turn respective LED on
						GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						GPIOD->BSRR = 1<<(13+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						for(i=0;i<3000000;i++);
						GPIOD->BSRR = 1<<(12+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
					}
					
					else if (ouverture == 0){
						GPIOD->BSRR = 1<<14; // Set the BSRR bit X to 1 to turn respective LED on
						GPIOD->BSRR = 1<<(12+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						GPIOD->BSRR = 1<<(13+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						for(i=0;i<500000;i++);
						GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						for(i=0;i<500000;i++);
						GPIOD->BSRR = 1<<14; // Set the BSRR bit X to 1 to turn respective LED on
						for(i=0;i<500000;i++);
						GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						for(i=0;i<500000;i++);
						GPIOD->BSRR = 1<<14; // Set the BSRR bit X to 1 to turn respective LED on
						for(i=0;i<500000;i++);
						GPIOD->BSRR = 1<<(14+16); // Set the BSRR bit X + 16 to 1 to turn respective LED off
						for(i=0;i<500000;i++);
					}
            
           badge_complet = false;
            
           Driver_USART1.Receive(buffer_rfid, 14);
       }
   }
}

int Identification(unsigned char tab[], uint8_t recu[]) {
    int i, b = 0;
    
    for(i=1; i<13; i++) {
        if (tab[i-1] == recu[i]) b++;
    }

    if (b == 12) {
        return 1;
    } else {
        return 0;
    }
}

