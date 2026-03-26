/* --------------------------------------------------------------------------
 * Projet BUT2 Semestre 4 : L'embarqué pour véhicule intelligent et communicant 
 * Auteurs : Groupe IT2R1
 * 
 * Objectif de ce code : Position GPS
 * 
 * Utilisation d'un PmodGPS -> Voir doc sur GitHub
 * Programmé sur carte STM32F4
 * -------------------------------------------------------------------------- */

#include "stm32f4xx.h"                  // Device header
#include "Driver_USART.h"               // CMSIS Driver:USART
#include "cmsis_os2.h"                  // CMSIS:RTOS2
#include "os_tick.h"                    // CMSIS:OS Tick
#include "rtx_os.h"                     // CMSIS:RTOS2:Keil RTX5&&Source

extern ARM_DRIVER_USART Driver_USART3; 

void Init_UART_GPS(void);
void UART_Callback_GPS(uint32_t event);

/*-------------- Création des identifiants des tâches (ID) --------------*/

osThreadId_t ID_ReceptUART;

typedef struct
{
	uint8_t data[100];
} DataRecept;


void thread_ReceptUART(void *argument)
{
	(void)argument;
	DataRecept Message;
	
	while(1)
	{
		Driver_USART3.Receive(Message.data, 100);
		osThreadFlagsWait(0x0001, osFlagsWaitAll, osWaitForever);
		osDelay(100);
	}
}


/*-------------- Priorité des threads --------------*/

osThreadAttr_t configReceptUART = { .priority = osPriorityHigh };

int main()
{
	SystemCoreClockUpdate();
	osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	Init_UART_GPS();

	ID_ReceptUART = osThreadNew( (osThreadFunc_t) thread_ReceptUART , NULL , &configReceptUART) ;
	
	osKernelStart();                      // Start thread execution
	return 0;
}

/* --------------------------------------------------------
 * Fonction : void Init_UART_GPS(void)
 *
 * Initialisation de l'UART3 pour le GPS (PD.9. (RX)/ PD.8 (TX))
 * 8 bits de donnée / pas parité / 1 stop / [4.8 kBd, 115.2 kBd]
 *-------------------------------------------------------*/

void Init_UART_GPS(void)
{
	Driver_USART3.Initialize(UART_Callback_GPS);
	Driver_USART3.PowerControl(ARM_POWER_FULL);
	Driver_USART3.Control( ARM_USART_MODE_ASYNCHRONOUS |
												 ARM_USART_DATA_BITS_8			 |
												 ARM_USART_STOP_BITS_1			 |
												 ARM_USART_PARITY_NONE			 |
												 ARM_USART_FLOW_CONTROL_NONE, 115200);
	Driver_USART3.Control(ARM_USART_CONTROL_RX, 1);			// réception
}

/* --------------------------------------------------------
 * Fonction : void UART_Callback_GPS(uint32_t event)
 *
 * Callback pour l'init de l'UART GPS
 *-------------------------------------------------------*/
	
void UART_Callback_GPS(uint32_t event)
{
	if(event & ARM_USART_EVENT_RECEIVE_COMPLETE) osThreadFlagsSet(ID_ReceptUART, 0x0001);
}