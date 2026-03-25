#include "LPC17xx.h"                    // Device header
#include "Board_ADC.h"                  // Board Support:A/D Converter


/*................PIN....................
P0.23 => moteur de la voiture
P2.25 => servo moteur de direction
.......................................*/

volatile uint32_t VAL_PWM_SERVO = 37500;

enum sens {AVANT, ARRIERE, STOP_HAUT,STOP_BAS,DESACTIVE};
enum return_vit{vitOK,vitERROR};

void init_moteur_motricite(void);
void init_servo_moteur();

enum return_vit control_vitesse(uint8_t val_vitesse);
void direction_roue(int16_t angle);
void control_hacheur(enum sens direction );

int main(void){
	
	while(1){
	LPC_GPIO0->FIOPIN |= (1<<17);
	LPC_GPIO0->FIOPIN &= ~(1<<17);
	}
  /*init_moteur_motricite();
	
	init_servo_moteur();

	ADC_Initialize();
	
	LPC_PWM1->MR2 =500;
	
	direction_roue(90);
	//control_hacheur(AVANT);
	LPC_GPIO0->FIODIR |= (1<<17); 
	LPC_GPIO0->FIOPIN = ~(1<<17);
	while (1){
		ADC_StartConversion();
		while(ADC_ConversionDone()!=0);
		float valeur = ADC_GetValue();
		valeur/=4096.0f;
		direction_roue((valeur * 180.0f)-90);
		control_vitesse(valeur*100);
		
	}*/
}

void init_servo_moteur()
{
		LPC_GPIO3->FIODIR3|=(1<<2); // active la sortie utiliser par l'interuption du timer
		// Validation des 4 TIMERS   
		LPC_SC->PCONP = LPC_SC->PCONP | 0x00C00006;   
	
		LPC_TIM0->PR = 0;  // le registre PR prend la valeur du prescaler
		LPC_TIM0->MR0 = 499999;    // debut le timer a 50hz
		LPC_TIM0->MCR=LPC_TIM0->MCR | 0x00000003; // active le reset on mr0 et les interuptions
	
		LPC_TIM0->TCR = 1;  // active le timer
		
		NVIC_SetPriority(TIMER0_IRQn,0);//active l'interuption sur MR0
		NVIC_EnableIRQ(TIMER0_IRQn);// met la priorite maximal sur l'interruption de MR0
}

//interruption gerant la PWM du servo moteur
void TIMER0_IRQHandler(void){
	volatile static char stat = 0 ; // variable servant a savoir si l'ont est a l'etat haut ou bas
	LPC_TIM0->IR = 1; // baissse le flag

	if (stat == 1 ){
	 LPC_TIM0->MR0 = 500000 - VAL_PWM_SERVO;// temps a l'etat bas
	}
	else
	{
		LPC_TIM0->MR0 = VAL_PWM_SERVO; //temps a l'etat haut
	}
	
	stat ^=1;// change de l'etat haut vers bas ou vis versa
	LPC_GPIO3->FIOPIN3 ^= (1<<2); // change la valeur de P3.26 pour realiser la PWM
	
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

// valeur possible AVANT, ARRIERE, STOP_HIGH, STOP_LOW
/* pinout
EN A : P0.19
EN B : P0.18 

IN A : P0.16
IN B : P0.17
*/

void control_hacheur(enum sens direction ){

	switch (direction){
	
		case AVANT :
				LPC_GPIO0->FIOPIN		|= ((1<<19)|(1<<18)); //active les 4 quadrants
		
				LPC_GPIO0->FIOPIN |=(1<<16);	// IN A : HAUT
				LPC_GPIO0->FIOPIN &=~(1<<17);	// IN B : BAS
			break;
		
		case ARRIERE:
				LPC_GPIO0->FIOPIN2 |= (1<<3)|(1<<2); //active les 4 quadrants
		
				LPC_GPIO0->FIOPIN2 &=~(1<<0);	// IN A : BAS
				LPC_GPIO0->FIOPIN2 |=(1<<1);	// IN B : HAUT
			break;
		
		default:
		case STOP_BAS:
				LPC_GPIO0->FIOPIN2 &=~((1<<1)|(1<<0)); //IN A et IN B BAS
				
			break;
	
		case STOP_HAUT:
				LPC_GPIO0->FIOPIN2 |=((1<<1)|(1<<0)); //IN A et IN B HAUT
			break;
		
		case DESACTIVE:
			LPC_GPIO0->FIOPIN2 &= ~((1<<3)|(1<<2)); //desactive les 4 quadrants
			break;
		}
}  


//valeur entre 0 et 100
enum return_vit control_vitesse(uint8_t val_vitesse){
	
	if(val_vitesse<=100 && val_vitesse>=0){
	
	LPC_PWM1->MR2 = (uint16_t)(val_vitesse * 2499.0)/100.0; //*24.99 car MR0 entre 0 et 2499
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
		VAL_PWM_SERVO = ((angle) * 25000/180)+25000; // value between 25 000 (1ms) and 50 000 (2ms)
	}
}

