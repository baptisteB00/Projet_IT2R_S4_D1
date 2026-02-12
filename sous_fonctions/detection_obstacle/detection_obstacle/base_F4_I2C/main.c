/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "Driver_I2C.h"                 // CMSIS Driver:I2C
#include "cmsis_os2.h"
 
 extern ARM_DRIVER_I2C Driver_I2C1;
 
 uint32_t HAL_GetTick (void) {
  static uint32_t ticks = 0U;
         uint32_t i;

  if (osKernelGetState () == osKernelRunning) {
    return ((uint32_t)osKernelGetTickCount ());
  }

  /* If Kernel is not running wait approximately 1 ms then increment 
     and return auxiliary tick counter value */
  for (i = (SystemCoreClock >> 14U); i > 0U; i--) {
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
  }
  return ++uwTick;
}
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN static void app_main (void *argument) {
  (void)argument;
	char tab[2] = {0x00,0x51};
  // ...
	Driver_I2C1.Initialize(NULL);
	Driver_I2C1.PowerControl(ARM_POWER_FULL);
	Driver_I2C1.Control(ARM_I2C_BUS_SPEED,ARM_I2C_BUS_SPEED_STANDARD);
	Driver_I2C1.Control(ARM_I2C_BUS_CLEAR,0);
  for (;;) {
		Driver_I2C1.MasterTransmit(0xE0, tab, 2, false);
		while (Driver_I2C1.GetStatus().busy == 1); // Attente fin de transmission physique 
		
		osDelay(1000);
	
	}
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
