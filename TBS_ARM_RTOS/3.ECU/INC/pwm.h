#ifndef __PWM_H__
#define __PWM_H__


#define PWM_CYCLE_COUNT 1000 

#define Init_PWM() Init_CT32B1_PWM()

void Set_PWM_Duty(uint8_t duty);


#endif
