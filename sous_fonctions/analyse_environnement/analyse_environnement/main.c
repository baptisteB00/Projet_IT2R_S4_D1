#include "LPC17xx.h"                    // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART

int main()
{
	LPC_GPIO2->FIODIR0 |= 0x20; // Configuration de la broche P2.5 en sortie pour le moteur du Lidar
	
	while(1)
	{
		//LPC_GPIO2->FIOPIN0 &= 0xD0;	// Eteint Moteur Lidar 
		LPC_GPIO2->FIOPIN0 |= 0x20;	// Allume Moteur Lidar 
	}
	
	return 0; 
}
