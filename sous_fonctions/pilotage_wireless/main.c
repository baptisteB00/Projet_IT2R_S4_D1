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

#define SLAVE_I2C_ADDR 0x52 
extern ARM_DRIVER_I2C Driver_I2C0; 
//extern ARM_DRIVER_I2C Driver_I2C2;          
extern GLCD_FONT GLCD_Font_16x24;      

// Prototypes des fonctions 
void Init_I2C(void);
void write1byte(unsigned char composant, unsigned char registre, unsigned char valeur);

int main (void) {
	char chaineX[20], chaineY[20]; //  Mag 
  char chainex[20], chainey[20]; //  Acc
	
	const uint8_t zero = 0x00;
	uint8_t rd_Nunchuk [6];
	
	// Initialisations GLCD et I2C N°2
	Init_I2C();
	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);
	
	
	while (1) {
		// Ecriture I2C 
		write1byte(SLAVE_I2C_ADDR, 0xF0, 0x55);
		for (int i=0; i>1000;i++);
		write1byte(SLAVE_I2C_ADDR, 0xFB, 0x00);
		for (int i=0; i>1000;i++);
		//cmd Lecture_Nunchuck;
		Driver_I2C0.MasterTransmit(SLAVE_I2C_ADDR, &zero, 1, false); 
    while (Driver_I2C0.GetStatus().busy == 1); 
		for (int i=0; i>1000;i++);
		//Lecture_Nunchuck();
		Driver_I2C0.MasterReceive(SLAVE_I2C_ADDR, rd_Nunchuk , 6, true); 
    while (Driver_I2C0.GetStatus().busy == 1); 
		for (int i=0; i>1000;i++);
		// --- Formatage des chaînes ---
		sprintf(chaineX, "mag X=%06d", rd_Nunchuk[0]);
		sprintf(chaineY, "mag Y=%06d", rd_Nunchuk[1]);
		sprintf(chainex, "Acc x=%06d", rd_Nunchuk[2]);
		sprintf(chainey, "Acc y=%06d", rd_Nunchuk[3]);

		// --- Affichage LCD ---
		GLCD_DrawString(1, 1, (unsigned char*)chaineX);   // Ligne Mag X
		GLCD_DrawString(1, 50, (unsigned char*)chaineY);   // Ligne Mag Y
		GLCD_DrawString(1, 150,(unsigned char*)chainex);   // Ligne Acc x
		GLCD_DrawString(1, 200, (unsigned char*)chainey);   // Ligne Acc y

	}
}

/* --------------------------------------------
Fonctions Lecture / Ecriture I2C & UART 
----------------------------------------------*/

// Fonction d'initialisation I2C 
void Init_I2C(void) {
    Driver_I2C0.Initialize(NULL); 
    Driver_I2C0.PowerControl(ARM_POWER_FULL); 
    Driver_I2C0.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST); // 400 kHz
//		Driver_I2C0.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD); // 100 kHz
    Driver_I2C0.Control(ARM_I2C_BUS_CLEAR, 0); 
}

// Fonction d'écriture (MasterTransmit) 
void write1byte(unsigned char composant, unsigned char registre, unsigned char valeur) {
    unsigned char tab[2];
    tab[0] = registre; 
    tab[1] = valeur; 
    Driver_I2C0.MasterTransmit(composant, tab, 2, false); 
    while (Driver_I2C0.GetStatus().busy == 1); // attente fin 
}
