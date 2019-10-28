#include <stdint.h>
#include <lpc11xx.h>
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <app_tasks.h>
#include <task_def.h>

#define STACK_SIZE 64

#define TASK_PRIO 5

xTaskHandle Task_IP_Handle, Task_OP_Handle, Task_COM_Handle;
portBASE_TYPE Task_IP_sts, Task_OP_sts, Task_COM_sts;

void CreateSemaphores(void)
{

}	

void CreateQueues(void)
{
	
}


void CreateAppTasks(void)
{
	Task_IP_sts = xTaskCreate(Task_Input,
								(const signed char *)"Input",
								STACK_SIZE,
								0,
								TASK_PRIO,
								&Task_IP_Handle);
	Task_OP_sts = xTaskCreate(Task_Output,
								(const signed char *)"Output",
								STACK_SIZE,
								0,
								TASK_PRIO,
								&Task_OP_Handle);
	Task_COM_sts = xTaskCreate(Task_COM,
								(const signed char *)"COM",
								STACK_SIZE,
								0,
								TASK_PRIO,
								&Task_COM_Handle);
	vTaskSuspend(Task_OP_Handle);
}	
