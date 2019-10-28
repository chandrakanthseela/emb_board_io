/* MCAL Includes */
#include <stdint.h>
#include <lpc11xx.h>

/* ECU Includes */


/* RTOS Includes */
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>


/* Application Includes */
#include <app_tasks.h>
#include <iocon.h>
#include <dio.h>
#include <adc.h>
#include <analog.h>
#include <pwm.h>
#include <ct32b1.h>
#include <clocks.h>
#include <uart.h>
#include <com.h>
#include <i2c.h>
#include <lm75.h>
void InitPeripherals(void)
{
	Init_UserKeys();
	Init_Rotary();
	Init_RGB();
	Set_PCLK_CT32B1(PCLK_ENABLE);
	Init_Analog();
	Init_DAC();
	Init_PWM();
	Init_COM();
	Init_Temp_Sensor();
}	


int main(void)
 {
 	ConfigIO();  // IOCON setup for TeamBits ECU
	InitPeripherals();
	CreateSemaphores();
	CreateQueues();
	CreateAppTasks();       
	vTaskStartScheduler(); // Start the Kernel
	 
}
