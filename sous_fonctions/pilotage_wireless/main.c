/*------------------------------------
Projet IT2R 2026 S4
Auteurs : Alexandre Ho, Lucas VINCENTI
--------------------------------------
Programme acquisition Nunchuck - Sequentiel 
-------------------------------------*/

/* ------------- Bibliotheques -------------------*/
#include "Driver_I2C.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "stdio.h"

/* ------------ Composants et police LCD ----------*/
#define NUNCHUCK_ADDR 0x52

extern ARM_DRIVER_I2C Driver_I2C2;
extern GLCD_FONT GLCD_Font_16x24;

/* ------------ Prototypes des fonctions -----------*/
void Nunchuck_Init(void);
void Nunchuck_Read(uint8_t data[6]);

/* ------------ Programme Principale ----------------
Fonction : Traitement et Acquisition du Nunchuck
Affichage : Sérialisation puis Ecriture sur LCD
------------------------------------------------------*/
int main(void) {
	uint8_t data[6];
	char ligne1[32], ligne2[32], ligne3[32];

	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_16x24);

	Nunchuck_Init();
	
	while (1) {
		Nunchuck_Read(data);
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

/* --------------------------------------------
Fonctions Lecture / Ecriture I2C & UART 
----------------------------------------------*/

// Fonction d'initialisation I2C 
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

// Fonction d'initialisation I2C 
void Nunchuck_Read(uint8_t data[6]) {
    uint8_t cmd = 0x00;

    // 1. Demande de lecture
    Driver_I2C2.MasterTransmit(NUNCHUCK_ADDR, &cmd, 1, false);
    while (Driver_I2C2.GetStatus().busy);

    // 2. Delay
    for (volatile int i = 0; i < 200000; i++); 

    // 3. Lecture des 6 octets
    Driver_I2C2.MasterReceive(NUNCHUCK_ADDR, data, 6, false);
    while (Driver_I2C2.GetStatus().busy);
	}
