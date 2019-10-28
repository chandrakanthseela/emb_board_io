#ifndef __CT32B1_H__
#define __CT32B1_H__


/* Free Running Counter */
void Set_CT32B1_Count(uint32_t count);
uint32_t Get_CT32B1_Count(void);


/* Match Value Setup */
void Set_CT32B1_MAT0_Count(uint32_t count);
void Set_CT32B1_MAT3_Count(uint32_t count);

/* Capture Count */
uint32_t Get_CT32B1_Capture_Count(void);

/* All GPT Feature Functionalities */
void Init_CT32B1_Event_Counter(void);
void Init_CT32B1_Simple_Timer(void);
void Init_CT32B1_Timer_Capture(void);
void Init_CT32B1_Pulse_Gen(void); // Single Match Square Wave
void Init_CT32B1_PWM(void); // DoubLe Match PWM Wave


#endif
