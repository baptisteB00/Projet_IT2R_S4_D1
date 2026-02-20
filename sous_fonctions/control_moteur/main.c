#include "LPC17xx.h"                    // Device header


/*................PIN....................
P0.23 => moteur de motricite
P2.25 => moteur de direction
.......................................*/

uint32_t VAL_PWM_SERVO = 50000;

enum sens {AVANT = 1 , ARRIERE = -1 , STOP = 0};
enum return_vit{vitOK,vitERROR};

void init_moteur_motricite(void);
void init_servo_moteur();

enum return_vit control_vitesse(uint8_t val_vitesse);
void direction_roue(int16_t angle);


int main(void){
	int i=0;
  init_moteur_motricite();
	
	init_servo_moteur();

	LPC_PWM1->MR2 =500;
	
	direction_roue(90);
	while (1){
		if(LPC_GPIO0->FIOPIN2){
		direction_roue(i);
		}
		i++;
		if(i>90)i=-90;
	}
}

void init_servo_moteur()
{
		LPC_GPIO3->FIODIR3|=(1<<2);
		// Validation des 4 TIMERS   
		LPC_SC->PCONP = LPC_SC->PCONP | 0x00C00006;   
	
		LPC_TIM0->PR = 0;  // le registre PR prend la valeur du prescaler
		LPC_TIM0->MR0 = 499999;    // le registre MR0 prend la valeur maximum du compteur
		LPC_TIM0->MCR=LPC_TIM0->MCR | 0x00000003; // active le reset on mr0 et les interuptions
	
		LPC_TIM0->TCR = 1;  
		
		NVIC_SetPriority(TIMER0_IRQn,0);
		NVIC_EnableIRQ(TIMER0_IRQn);
}


void TIMER0_IRQHandler(void){
	volatile static char stat = 0 ; 
	LPC_TIM0->IR = 1; // baissse le flag

	if (stat == 1 ){
	 LPC_TIM0->MR0 = 500000 - VAL_PWM_SERVO;
	}
	else
	{
		LPC_TIM0->MR0 = VAL_PWM_SERVO; 
	}
	
	stat ^=1;
	LPC_GPIO3->FIOPIN3 ^= (1<<2);
	
}


void init_moteur_motricite(void)
{
LPC_SC->PCONP |= 0x00000040; // Enable PWM1
LPC_PINCON->PINSEL7 |= (3<<18); // Broches P3.25
LPC_PWM1->PR = 0; // Prescaler
LPC_PWM1->MR0 = 2499; // MR0+1=25000, comptage à 10kHz
LPC_PWM1->MCR |= 0x00000002; // RAZ on MR0
LPC_PWM1->LER |= 0x0000000F; // Autorise Modification PWM en cours de fonctionnement
LPC_PWM1->PCR |= 0x00000E00; // Autorise les sorties PWM1/2/3
LPC_PWM1->TCR |= 0x00000001; // Démarrage Timer
LPC_PWM1->MR2=0; // desactive la vitesse au debut 

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
enum return_vit control_vitesse(uint8_t val_vitesse){
	
	if(val_vitesse<=100 && val_vitesse>=0){
	
	LPC_PWM1->MR2 = (uint16_t)(val_vitesse * 24.99); //*6 car valeur entre 0;100 => 0;600
		return vitOK;
	}else {
		LPC_PWM1->MR2 =0;
		return vitERROR;
	}

}

//angle : valeur en degrees
void direction_roue(int16_t angle){

	if ( angle <= 90 && angle >= -90){
	
		angle += 90; // value between 0 and 180 
		VAL_PWM_SERVO = ((angle) * 25000.0/180.0)+25000.0; // value between 25 000 (1ms) and 50 000 (2ms)
	}
}

