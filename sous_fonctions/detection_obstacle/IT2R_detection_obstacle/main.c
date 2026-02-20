#include "Driver_I2C.h"                 // ::CMSIS Driver:I2C
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f4xx.h"                  // Device header
//#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic

// Test git


#define CAPTAvD 0xE0 //0x70
#define CAPTAvG 0xE2 //0x71

extern ARM_DRIVER_I2C Driver_I2C1;
I2C_HandleTypeDef hi2c1; // Handle pour le bus I2C

//uint8_t DeviceAddr;
//uint16_t dist1;
//uint16_t dist2;
static void Error_Handler(void);
static void SystemClock_Config(void);
void MX_I2C1_Init(void);

void SystemClock_Config(void);
void SysTick_Handler(void);
void Init_I2C(void);
void write1byte(uint8_t addr, uint8_t reg, uint8_t val);
uint8_t read1byte(uint8_t addr, uint8_t reg);
uint16_t get_distance(uint8_t addr);

void SysTick_Handler(void) {
    HAL_IncTick();
}

//void SystemClock_Config(void) {
//    // Configuration standard pour 168MHz
//    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//    __HAL_RCC_PWR_CLK_ENABLE();
//    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//    RCC_OscInitStruct.PLL.PLLM = 8;
//    RCC_OscInitStruct.PLL.PLLN = 336;
//    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//    RCC_OscInitStruct.PLL.PLLQ = 7;
//    HAL_RCC_OscConfig(&RCC_OscInitStruct);
//    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
//}
//-----------------------------------------------
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

//-----------------------------------------------------

void Init_I2C(void){
	
	Driver_I2C1.Initialize(NULL);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(	ARM_I2C_BUS_SPEED,				// 2nd argument = debit
							ARM_I2C_BUS_SPEED_STANDARD  );	// 100 kHz
	Driver_I2C1.Control(	ARM_I2C_BUS_CLEAR,
							0 );
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
    // Envoyer l'adresse du registre avec REPEATED START (true) 
    Driver_I2C1.MasterTransmit(capt_addr, &reg, 1, true); 
    while (Driver_I2C1.GetStatus().busy == 1);
    
    // Recevoir la donnée 
    Driver_I2C1.MasterReceive(capt_addr, &valeur, 1, false);
    while (Driver_I2C1.GetStatus().busy == 1);
    
    return valeur; // On retourne l'octet récupéré
}


// --- Fonction spécifique au SRF10 (Mesure + Attente ) ---
uint16_t get_distance(uint8_t capt_addr) {
    uint8_t high, low;
//	uint32_t i;
    
    // 1. Lancer la mesure en cm (Commande 0x51 dans registre 0) 
    write1byte(capt_addr, 0x00, 0x51);

    // Attente : le capteur renvoie 0xFF tant qu'il mesure 
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
//	uint8_t tab[2];
//	uint8_t high, low;
	
//	tab[0]=0x00;
//	tab[1]=0x51;

	HAL_Init();
	SystemClock_Config();      // Config 168 MHz
  SystemCoreClockUpdate(); // On synchronise la variable de fréquence

	Init_I2C();
//	MX_I2C1_Init();

	while (1)
  {
		dist1 = get_distance(CAPTAvG>>1);
		dist2 = get_distance(CAPTAvD>>1);
			
//		write1byte(CAPTAvG>>1, tab[0], tab[1]);
//		HAL_Delay(70);
//		
//		high = read1byte(CAPTAvG>>1, 0x02);
//    low  = read1byte(CAPTAvG>>1, 0x03);
//		
//		dist1=(high << 8) | low;
		
 }

	return 0;
}

//void MX_I2C1_Init(void) {
//    hi2c1.Instance = I2C1; // / Utilise le bloc I2C n°1 du STM32F4 (lié aux broches PB6/PB7)
//    hi2c1.Init.ClockSpeed = 100000;         // Vitesse standard 100kHz
//    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2; // Définit le rapport cyclique du signal d'horloge. En mode standard (100kHz), ce paramètre est fixe (50/50)
//    hi2c1.Init.OwnAddress1 = 0;             // Le STM32 est maître, pas besoin d'adresse
//    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT; // // Le SRF10 utilise des adresses sur 7 bits
//    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE; // Désactive la possibilité pour le STM32 d'avoir 2 adresses
//    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE; // Désactive la réponse aux messages envoyés à "tout le monde".
//    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE; // Autorise le "Clock Stretching". // Cela permet au bus de s'adapter si un composant est un peu lent.
//    
//    HAL_I2C_Init(&hi2c1); // Cette fonction HAL configure le matériel
//}
