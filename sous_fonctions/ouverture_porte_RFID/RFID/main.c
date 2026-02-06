#include "LPC17xx.h"
#include "Driver_USART.h"
#include "RTE_Components.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "stdio.h"

// Déclarations Externes
extern ARM_DRIVER_USART Driver_USART1;
extern GLCD_FONT GLCD_Font_16x24;

// Variables partagées entre la fonction d'interruption interne au driver et le main
// volatile est crucial -> badge_complet est modifié dans le Callback (=>nécessité de stockage dans la ram)
volatile bool badge_complet = false; 
uint8_t buffer_rfid[10]; 

// Prototypes
void My_USART_Callback(int event);
void Init_Systeme(void);
void Identification(unsigned char badge_maitre[], uint8_t recu[]);

// Fonction de callback (évite l'écriture d'une fonction d'interruption en utilisant une configurée pralablement dans le driver UART)
void My_USART_Callback(int event) {
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
                          ARM_USART_PARITY_NONE, 115200);
    Driver_USART1.Control(ARM_USART_CONTROL_RX, 1); // Activer la réception

    GLCD_Initialize();
    GLCD_ClearScreen();
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString(0, 0, "En attente badge...");
}

int main(void) {
    unsigned char badge_maitre[10] = {0,0,0,5,0,8,4,6,2,6};
    
    Init_Systeme();

    while (1) {
        if (badge_complet) {
            // On traite le badge reçu
            Identification(badge_maitre, buffer_rfid);
            
            badge_complet = false;
            
            Driver_USART1.Receive(buffer_rfid, 10);
        }
    }
}

void Identification(unsigned char tab[], uint8_t recu[]) {
    int i, j, b = 0;
    
    for(i=0; i<10; i++) {
        if (tab[i] == recu[i]) b++;
    }

    GLCD_ClearScreen();
    if (b == 10) {
        GLCD_DrawString(0, 50, "Badge reconnu !");
    } else {
        GLCD_DrawString(0, 50, "Acces refuse");
    }
    
    // Pause visuelle avant de revenir à l'état d'attente
    for(j=0; j<10000000; j++); 
    GLCD_ClearScreen();
    GLCD_DrawString(0, 0, "En attente badge...");
}
