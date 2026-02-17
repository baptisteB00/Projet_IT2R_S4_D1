#include "LPC17xx.h"                    // Device header


/*................PIN....................
P0.23 => moteur de motricite
P2.25 => moteur de direction
.......................................*/


enum sens {AVANT = 1 , ARRIERE = -1 , STOP = 0};

void init_moteur_motricite(void);


int main(void){

init_moteur_motricite();
	
}

void init_moteur_motricite(void){

	LPC_SC->PCONP |= 0x00000040; // Enable PWM1
	LPC_PINCON->PINSEL7 |= (0x11<<20)|(0x11<<18); //met les Pin P3.25 et P3.26 sur PWM1.2 et PWM 1.3
	LPC_PWM1->PR = 0; // Prescaler
	LPC_PWM1->MR0 = 1250; // MR0+1=25000, comptage à 1kHz
	LPC_PWM1->MCR |= 0x00000002; // RAZ on MR0
	LPC_PWM1->LER |= 0x0000000F; // Autorise Modification PWM en cours de fonctionnement
	LPC_PWM1->PCR |= 0x00000E00; // Autorise les sorties PWM1/2/3
	LPC_PWM1->TCR |= 0x00000001; // Démarrage Timer

	LPC_PWM1->MR2 = 0;
	LPC_PWM1->MR3 = 50;
}



void direction_moteur(enum sens direction ){

	switch (direction){
	
		case AVANT :
				LPC_GPIO0->FIOPIN2 |=(1<<3);
				LPC_GPIO0->FIOPIN2 &=~(1<<0);
			break;
		
		case ARRIERE:
				LPC_GPIO0->FIOPIN2 &=~(1<<3);
				LPC_GPIO0->FIOPIN2 |=(1<<0);
			break;
		default:
		case STOP:
			LPC_GPIO0->FIOPIN2 &=~(1<<3);
			LPC_GPIO0->FIOPIN2 &=~(1<<0);
			break;
		}
	
}  

//valeur entre 0 et 100
void vitesse(uint8_t val_vitesse){

	if(val_vitesse<=100 && val_vitesse>=0){
	
	LPC_PWM1->MR2 = val_vitesse * 6; //*6 car valeur entre 0;100 => 0;600
		
	}

}

void direction_roue(int8_t angle){
	uint8_t valeur_PWM;
	
	if ( angle < 100 && angle > -100){
	
		valeur_PWM = (angle+ 100)/2.0;
		
		LPC_PWM1->MR2 = (char) valeur_PWM;
		
	}
}