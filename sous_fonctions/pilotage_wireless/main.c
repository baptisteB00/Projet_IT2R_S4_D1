/*------------------------------------
Projet IT2R 2026 S4
Auteurs : Alexandre Ho, Lucas VINCENTI
--------------------------------------
Programme acquisition Nunchuck
-------------------------------------*/

#include "Driver_I2C.h"    			// Pour ecriture/lecture Nunchuck
#include "Board_GLCD.h"    			// Pour ecriture sur ecran LCD
#include "GLCD_Config.h"   
#include "stdio.h"  
#include "Driver_USART.h"       // Pour envoi Bluetooth 

#define SLAVE_I2C_ADDR 0x1D 

extern ARM_DRIVER_I2C Driver_I2C2;          
extern GLCD_FONT GLCD_Font_16x24;      

// Prototypes des fonctions 
void Init_I2C(void);
void write1byte(unsigned char composant, unsigned char registre, unsigned char valeur);
unsigned char read1byte(unsigned char composant, unsigned char registre);

int main (void) {
	
    // Initialisations GLCD et I2C N°2
    Init_I2C();
    GLCD_Initialize();
    GLCD_ClearScreen();
    GLCD_SetFont(&GLCD_Font_16x24);
	
    while (1) {
			// --- Affichage Lecture I2C ---
			
			//Lecture_Nunchuck();
			
			// --- Traitement données
			
			// --- Affichage LCD ---
      GLCD_DrawString(-10, 100, " Travaux en cours...");   // Ligne Mag X
    }
}

/* --------------------------------------------
Fonctions Lecture / Ecriture I2C & UART 
----------------------------------------------*/

// Fonction d'initialisation I2C 
void Init_I2C(void) {
    Driver_I2C2.Initialize(NULL); 
    Driver_I2C2.PowerControl(ARM_POWER_FULL); 
    Driver_I2C2.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD); // 100 kHz
    Driver_I2C2.Control(ARM_I2C_BUS_CLEAR, 0); 
}

// Fonction d'écriture (MasterTransmit) 
void write1byte(unsigned char composant, unsigned char registre, unsigned char valeur) {
    unsigned char tab[2];
    tab[0] = registre; 
    tab[1] = valeur; 
    Driver_I2C2.MasterTransmit(composant, tab, 2, false); 
    while (Driver_I2C2.GetStatus().busy == 1); // attente fin 
}

unsigned char read1byte(unsigned char composant, unsigned char registre) {
    unsigned char valeur;
    Driver_I2C2.MasterTransmit(composant, &registre, 1, true); 
    while (Driver_I2C2.GetStatus().busy == 1);
    Driver_I2C2.MasterReceive(composant, &valeur, 1, false); 
    while (Driver_I2C2.GetStatus().busy == 1); 
    return valeur; 
}
