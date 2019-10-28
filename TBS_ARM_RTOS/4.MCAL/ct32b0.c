#include <stdint.h>
#include <lpc11xx.h>
#include <iocon.h>
#include <ct32b0.h>


void Config_CT32B0_CTM(gpt_ctm_t ctm)
{
	LPC_TMR32B0->CTCR = ctm;
}	

void Config_CT32B0_Counters(gpt_ce_t ce)
{
	switch(ce)
	{
		case COUNTERS_DISABLE:		LPC_TMR32B0->TCR &= ~(1<<0);
		                          break;
		
		case COUNTERS_ENABLE:			LPC_TMR32B0->TCR |= (1<<0);
		                          break;
	}	
}	

void Config_CT32B0_Reset(gpt_crst_t crst)
{
	switch(crst)
	{
		case DEASSERT_RESET :		LPC_TMR32B0->TCR &= ~(1<<1);
		                        break;
		
		case ASSERT_RESET:			LPC_TMR32B0->TCR |= (1<<1);
		                        break;
	}	
}	

void Set_CT32B0_Count(uint32_t count)
{
	LPC_TMR32B0->TC = count;
}	

void Set_CT32B0_Prescale_Count(uint32_t count)
{
	LPC_TMR32B0->PR = count;
}	

void Set_CT32B0_MAT0_Count(uint32_t count)
{
	LPC_TMR32B0->MR0 = count;
}	

void Set_CT32B0_MAT3_Count(uint32_t count)
{
	LPC_TMR32B0->MR3 = count;
}	

uint32_t Get_CT32B0_Count(void)
{
	return (LPC_TMR32B0->TC);
}	

uint32_t Get_CT32B0_Capture_Count(void)
{
	return (LPC_TMR32B0->CR0);
}	

void Set_CT32B0_CAP_Option(gpt_cap_option_t option)
{
	switch(option)
	{
		case CAP_ON_RISE:			LPC_TMR32B0->CCR |= (1<<0);
													LPC_TMR32B0->CCR &= ~(1<<1);
													LPC_TMR32B0->CCR &= ~(1<<2);
													break;
	
		case CAP_ON_FALL:			LPC_TMR32B0->CCR &= ~(1<<0);
													LPC_TMR32B0->CCR |= (1<<1);
													LPC_TMR32B0->CCR &= ~(1<<2);
													break;

		case CAP_INTERRUPT :	LPC_TMR32B0->CCR &= ~(1<<0);
													LPC_TMR32B0->CCR &= ~(1<<1);
													LPC_TMR32B0->CCR |= (1<<2);
													break;
	}	
}	


void Init_CT32B0_Event_Counter(void)
{	
 Config_CT32B0_CTM(COUNTER_MODE_RISE_EDGE);
 Config_CT32B0_Counters(COUNTERS_ENABLE);
 Config_CT32B0_Reset(DEASSERT_RESET);
 Set_CT32B0_Count(0);
}

void Init_CT32B0_Simple_Timer(void)
{
 Config_CT32B0_CTM(TIMER_MODE);
 Set_CT32B0_Count(0);
 Set_CT32B0_Prescale_Count(47); // 1 MHz
 Config_CT32B0_Counters(COUNTERS_ENABLE);
 Config_CT32B0_Reset(DEASSERT_RESET);
}	

void Init_CT32B0_Timer_Capture(void)
{
   // PIO1_5 to be configured for CT32B0_CAP pin function
   // Refer ioconfig.c/.h
	
	 // Set the appropriate Capture Option
	 Set_CT32B0_CAP_Option(CAP_ON_FALL);
	
	 // Set Simple Timer Operation
  Init_CT32B0_Simple_Timer();
}	

void Config_CT32B0_MAT0_Internal_Option(gpt_int_mat_option_t option)
{
	switch(option)
	{
		case INTERRUPT_ON_MATCH:		LPC_TMR32B0->MCR |= (1<<0);
																LPC_TMR32B0->MCR &= ~(1<<1);
																LPC_TMR32B0->MCR &= ~(1<<2);
		                            break;

		case COUNTER_RESET:					LPC_TMR32B0->MCR &= ~(1<<0);
																LPC_TMR32B0->MCR |= (1<<1);
																LPC_TMR32B0->MCR &= ~(1<<2);
                                break;
		
		case COUNTER_STOP:					LPC_TMR32B0->MCR &= ~(1<<0);
																LPC_TMR32B0->MCR &= ~(1<<1);
																LPC_TMR32B0->MCR |= (1<<2);
		                            break;
	}	
}	

void Config_CT32B0_MAT3_Internal_Option(gpt_int_mat_option_t option)
{
	switch(option)
	{
		case INTERRUPT_ON_MATCH:		LPC_TMR32B0->MCR |= (1<<9);
																LPC_TMR32B0->MCR &= ~(1<<10);
																LPC_TMR32B0->MCR &= ~(1<<11);
		                            break;

		case COUNTER_RESET:					LPC_TMR32B0->MCR &= ~(1<<9);
																LPC_TMR32B0->MCR |= (1<<10);
																LPC_TMR32B0->MCR &= ~(1<<11);
                                break;
		
		case COUNTER_STOP:					LPC_TMR32B0->MCR &= ~(1<<9);
																LPC_TMR32B0->MCR &= ~(1<<10);
																LPC_TMR32B0->MCR |= (1<<11);
		                            break;
	}	
}	


#define GPT_EMC0_START	4
#define MASK_2BIT	      0x3

void Config_CT32B0_MAT0_External_Option(gpt_ext_mat_option_t option)
{
	LPC_TMR32B0->EMR = (LPC_TMR32B0->EMR & ~(MASK_2BIT<<GPT_EMC0_START)) |
	                    (option<<GPT_EMC0_START);
}

void Init_CT32B0_Pulse_Gen(void)
{
	// IOCON
	// Refer ioconfig.c
	
	// Simple Timer
	Init_CT32B0_Simple_Timer();
	
	// Set Internal Match Option
	Config_CT32B0_MAT0_Internal_Option(COUNTER_RESET);
	
	// Set External Match Option
	Config_CT32B0_MAT0_External_Option(TOGGLE_OUTPUT);
}	

void Init_CT32B0_PWM(void)
{
	// IOCON
	// Refer ioconfig.c
	
	// Set Internal Match Option for MAT3
	Config_CT32B0_MAT3_Internal_Option(COUNTER_RESET);
	
	// Set the PWM Cycle (T)
	Set_CT32B0_MAT3_Count(1000);
	
	// Set the PWM On/Off Time (Ton)
	Set_CT32B0_MAT0_Count(500); // Sqaure Wave

	// Enable PWM for MR0
	LPC_TMR32B0->PWMC |= (1<<0);

	// Simple Timer
	Init_CT32B0_Simple_Timer();
}	
