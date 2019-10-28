#ifndef __CT32B0_H__
#define __CT32B0_H__

typedef enum
{
	TIMER_MODE,
	COUNTER_MODE_RISE_EDGE,
	COUNTER_MODE_FALL_EDGE,
	COUNTER_MODE_BOTH_EDGE
}gpt_ctm_t;	

typedef enum
{
	COUNTERS_DISABLE,
	COUNTERS_ENABLE
}gpt_ce_t;	

typedef enum
{
	DEASSERT_RESET,
	ASSERT_RESET
}gpt_crst_t;	

typedef enum
{
	CAP_ON_RISE,
	CAP_ON_FALL,
	CAP_INTERRUPT
}gpt_cap_option_t;	

typedef enum
{
	INTERRUPT_ON_MATCH,
	COUNTER_RESET,
	COUNTER_STOP
}gpt_int_mat_option_t;	

typedef enum
{
	NO_OUTPUT,
	LOW_OUTPUT,
	HIGH_OUTPUT,
	TOGGLE_OUTPUT
}gpt_ext_mat_option_t;	


void Config_CT32B0_CTM(gpt_ctm_t ctm);
void Config_CT32B0_Counters(gpt_ce_t ce);
void Config_CT32B0_Reset(gpt_crst_t crst);

void Set_CT32B0_Count(uint32_t count);
uint32_t Get_CT32B0_Count(void);
void Set_CT32B0_MAT0_Count(uint32_t count);

uint32_t Get_CT32B0_Capture_Count(void);
void Set_CT32B0_CAP_Option(gpt_cap_option_t option);

void Config_CT32B0_MAT0_Internal_Option(gpt_int_mat_option_t option);
void Config_CT32B0_MAT0_External_Option(gpt_ext_mat_option_t option);

void Init_CT32B0_Event_Counter(void);
void Init_CT32B0_Simple_Timer(void);
void Init_CT32B0_Timer_Capture(void);
void Init_CT32B0_Pulse_Gen(void);
void Init_CT32B0_PWM(void);


#endif
