#ifndef __TASK_DEF_H__
#define __TASK_DEF_H__


typedef enum {
	STOP,
	START
}run_t;

typedef enum 
{
	RGB,
	PWM,
	DAC
}output_choice_t;

typedef enum
{
	OFF,
	RED,
	BLUE,
	GREEN,
	WHITE
}rgb_choice_t;

void Task_Input( void *args );
void Task_Output ( void *args );
void Task_COM ( void *args );

#endif
