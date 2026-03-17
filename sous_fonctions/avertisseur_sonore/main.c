#include "LPC17xx.h"
#include "Driver_USART.h"
//#include "GLCD_Config.h"                // Board Support:Graphic LCD
//#include "GLCD_Fonts.h"                 // Board Support:Graphic LCD
#include "stdio.h"                    // Device header
#include "RTE_Components.h"
#include "cmsis_os2.h"


extern ARM_DRIVER_USART Driver_USART1;
extern int32_t GLCD_Initialize (void);

osThreadId_t ID_sendDFCommand;
osThreadId_t ID_trame_uart;

osThreadAttr_t configT1 = {.priority = osPriorityNormal} ;
osThreadAttr_t configT2 = {.priority = osPriorityNormal} ;
osThreadAttr_t configT3 = {.priority = osPriorityNormal} ;
osMutexId_t mut_son;


// Fonction pour envoyer une trame de commande au DFPlayer
void sendDFCommand(uint8_t cmd, uint8_t para1, uint8_t para2) {
    char packet[10];
    short checksum;
		int i;
		osMutexAcquire(mut_son, osWaitForever);
    packet[0] = 0x7E;          // Start byte 
    packet[1] = 0xFF;          // Version 
    packet[2] = 0x06;          // Data length 
    packet[3] = cmd;           // Command ID 
    packet[4] = 0x00;          // Feedback (0x00 = No, 0x01 = Yes) 
    packet[5] = para1;         // Parameter high byte 
    packet[6] = para2;         // Parameter low byte 
    
    // Calcul du Checksum : 0xFFFF - (VER + Len + CMD + Feedback + Para1 + Para2) + 1
    checksum = 0xffff - (packet[1] + packet[2] + packet[3] + packet[4] + packet[5] + packet[6])+1;
    
    packet[7] = (uint8_t)(checksum >> 8); // Checksum high byte 
    packet[8] = (uint8_t)(checksum & 0xFF); // Checksum low byte
    packet[9] = 0xEF;          // End byte 

	for (i=0;i<10;i++)
	{
    Driver_USART1.Send(&packet[i], 1);
    while (Driver_USART1.GetStatus().tx_busy);
		osDelay(2);
	}
	osMutexRelease(mut_son);
	osDelay(500);
}


static void Init_UART(void) {
    Driver_USART1.Initialize(NULL);
    Driver_USART1.PowerControl(ARM_POWER_FULL);
    Driver_USART1.Control(ARM_USART_MODE_ASYNCHRONOUS |
                          ARM_USART_DATA_BITS_8 |
                          ARM_USART_STOP_BITS_1 |
                          ARM_USART_PARITY_NONE |
                          ARM_USART_FLOW_CONTROL_NONE, 9600);  
    Driver_USART1.Control(ARM_USART_CONTROL_TX, 1);
    Driver_USART1.Control(ARM_USART_CONTROL_RX, 1);
}

void trame_uart(void)
{
	osMutexAcquire(mut_son, osWaitForever);
	char tab[1];
	Driver_USART1.Receive(tab,1);
			while(Driver_USART1.GetRxCount()<1);
			if (tab[0]==0x30)
			{
				sendDFCommand(0x03, 0x00, 0x03);
				osDelay(100);
				sendDFCommand(0x0D, 0x00, 0x00);
			}
			if (tab[0]==0x31)
			{
				sendDFCommand(0x03, 0x00, 0x04);
				osDelay(100);
				sendDFCommand(0x0D, 0x00, 0x00);
			}
	
	osMutexRelease(mut_son);
}


int main(void) {
		
    Init_UART();
		
	
		SystemCoreClockUpdate;
		osKernelInitialize();
		ID_sendDFCommand = osThreadNew((osThreadFunc_t)sendDFCommand, NULL, &configT1);
    
		
		mut_son= osMutexNew(NULL);
		
		osKernelStart;
		
		
	 // 1.Reset le module	(0x0C, param: 0x0000)
		sendDFCommand(0x0C, 0x00, 0x00);
    osDelay(1000);

   // 2. Spécifier la source de lecture : Carte SD (0x09, param: 0x01) 
		sendDFCommand(0x09, 0x00, 0x01);
    osDelay(200); // Délai nécessaire après sélection de la source 
		
    
	// 3. Régler le volume à 15 (0x06, param: 0x0F) 
    sendDFCommand(0x06, 0x00, 0x02);
    osDelay(100);
		

    
	// 4. Jouer le premier morceau (0x03, param: 0x0001) 
    sendDFCommand(0x03, 0x00, 0x01);
		osDelay(100);
		sendDFCommand(0x0D, 0x00, 0x00);
	
    while (1) {
			trame_uart();      
    }
}