#include "LPC17xx.h"
#include "Driver_USART.h"

extern ARM_DRIVER_USART Driver_USART1;

// Fonction pour envoyer une trame de commande au DFPlayer
void sendDFCommand(uint8_t cmd, uint8_t para1, uint8_t para2) {
    uint8_t packet[10];
    uint16_t checksum;

    packet[0] = 0x7E;          // Start byte [cite: 474]
    packet[1] = 0xFF;          // Version [cite: 474]
    packet[2] = 0x06;          // Data length [cite: 474]
    packet[3] = cmd;           // Command ID [cite: 474]
    packet[4] = 0x00;          // Feedback (0x00 = No, 0x01 = Yes) 
    packet[5] = para1;         // Parameter high byte 
    packet[6] = para2;         // Parameter low byte 
    
    // Calcul du Checksum : 0xFFFF - (VER + Len + CMD + Feedback + Para1 + Para2) + 1
    checksum = 0 - (packet[1] + packet[2] + packet[3] + packet[4] + packet[5] + packet[6]);
    
    packet[7] = (uint8_t)(checksum >> 8); // Checksum high byte [cite: 519]
    packet[8] = (uint8_t)(checksum & 0xFF); // Checksum low byte [cite: 519]
    packet[9] = 0xEF;          // End byte [cite: 474]

    Driver_USART1.Send(packet, 10);
    while (Driver_USART1.GetStatus().tx_busy);
}

void delay_ms(uint32_t ms) {
    // Boucle de délai simplifiée (à ajuster selon la fréquence de votre CPU).
    for (volatile uint32_t i = 0; i < ms * 12000; i++);
}

void Init_UART(void) {
    Driver_USART1.Initialize(NULL);
    Driver_USART1.PowerControl(ARM_POWER_FULL);
    Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS |
                          ARM_USART_DATA_BITS_8 |
                          ARM_USART_STOP_BITS_1 |
                          ARM_USART_PARITY_NONE |
                          ARM_USART_FLOW_CONTROL_NONE, 9600); // 9600 bps par défaut 
    Driver_USART1.Control(ARM_USART_CONTROL_TX, 1);
    Driver_USART1.Control(ARM_USART_CONTROL_RX, 1);
}

int main(void) {
		Initialise_GPIO ();
    Init_UART();
	
    delay_ms(1000); // Attendre la stabilisation du module au démarrage [cite: 484]

    // 1. Spécifier la source de lecture : Carte TF (0x09, param: 0x02) [cite: 529]
    sendDFCommand(0x09, 0x00, 0x02);
    delay_ms(200); // Délai nécessaire après sélection de la source [cite: 529]
		Allumer_1LED(1);
    // 2. Régler le volume à 15 (0x06, param: 0x0F) [cite: 525]
    sendDFCommand(0x06, 0x00, 0x1E);
    delay_ms(100);
		Allumer_1LED(2);
    // 3. Jouer le premier morceau (0x03, param: 0x0001) [cite: 519]
    sendDFCommand(0x08, 0x00, 0x04);
		Allumer_1LED(3);
    while (1) {
        // Le programme boucle ici pendant que le son joue
    }
}