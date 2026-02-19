#include "Driver_I2C.h"                 // ::CMSIS Driver:I2C
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f4xx.h"                  // Device header
//#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic

// Test git


#define CAPTAvD 0x70 //0xE0
#define CAPTAvG 0x71 //0xE2

extern ARM_DRIVER_I2C Driver_I2C1;

//uint8_t DeviceAddr;
//uint16_t dist1;
//uint16_t dist2;

void Init_I2C(void);
void write1byte(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t read1byte(uint8_t addr, uint8_t reg);
uint16_t get_distance(uint8_t addr);

void Init_I2C(void){
	Driver_I2C1.Initialize(NULL);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(	ARM_I2C_BUS_SPEED,				// 2nd argument = debit
							ARM_I2C_BUS_SPEED_STANDARD  );	// 100 kHz
//	Driver_I2C1.Control(	ARM_I2C_BUS_CLEAR,
//							0 );
}

void write1byte(uint8_t capt_addr, uint8_t reg, uint8_t val) {
    uint8_t tab[2]; // 
		
		tab[0]= reg;
		tab[1]= val;
    Driver_I2C1.MasterTransmit(capt_addr, tab, 2, false); // Envoi START + ADDR_Slave+W + REG + DATA + STOP 
    while (Driver_I2C1.GetStatus().busy == 1); // Attente fin de transmission physique 
}

uint8_t read1byte(uint8_t capt_addr, uint8_t reg) {
    uint8_t valeur;
    // 1. Envoyer l'adresse du registre avec REPEATED START (true) 
    Driver_I2C1.MasterTransmit(capt_addr, &reg, 1, true); 
    while (Driver_I2C1.GetStatus().busy == 1);
    
    // 2. Recevoir la donnée 
    Driver_I2C1.MasterReceive(capt_addr, &valeur, 1, false);
    while (Driver_I2C1.GetStatus().busy == 1);
    
    return valeur; // On retourne l'octet récupéré
}


// --- Fonction spécifique au SRF10 (Mesure + Attente ) ---
uint16_t get_distance(uint8_t capt_addr) {
    uint8_t high, low;
    
    // 1. Lancer la mesure en cm (Commande 0x51 dans registre 0) 
    write1byte(capt_addr, 0x00, 0x51);

    // 2. Attente : le capteur renvoie 0xFF tant qu'il mesure 
//    while (read1byte(capt_addr, 0) == 0xFF); 
		HAL_Delay(70);

    // 3. Lire les registres de distance 2 et 3 
    high = read1byte(capt_addr, 0x02);
    low  = read1byte(capt_addr, 0x03);
    
    return (uint16_t)((high << 8) | low); // Reconstruction 16-bits 
}


int main(void)
{
	uint16_t dist1=0;
	uint16_t dist2=0;

	HAL_Init();
	Init_I2C();

	while (1)
  {
		dist1 = get_distance(CAPTAvG);
		dist2 = get_distance(CAPTAvD);
 }

	return 0;
}