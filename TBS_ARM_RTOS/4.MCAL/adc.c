#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <adc.h>


typedef enum
{
	ADC_MODE_INDIVIDUAL,
	ADC_MODE_GROUP
}adc_mode_t;	

typedef enum
{
	ADC_STOP,
	ADC_START
}adc_start_stop_t;	


static void Set_ADC_Base_Config(void)
{
	// IOCON Setup
	   // refer ioconfig.c
	
	// Global Clock Enable
	Set_PCLK_ADC(PCLK_ENABLE);

	// Disable ADC Global Power down
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);
}	

static void Set_ADC_Operation_Mode(adc_mode_t adc_mode)
{
	switch(adc_mode)
	{
		case ADC_MODE_INDIVIDUAL:		LPC_ADC->CR &= ~(1<<16);
		                            break;       
		case ADC_MODE_GROUP:			  LPC_ADC->CR |= (1<<16);
		                            break;       
	}	
}	

static void Select_ADC_Input_Channel(adc_select_t adc_select)
{
	#define ADC_SEL_MASK  0xff
	#define ADC_SEL_START 0
	
	LPC_ADC->CR = (LPC_ADC->CR & ~(ADC_SEL_MASK<<ADC_SEL_START)) |
	              (adc_select<<ADC_SEL_START);  
}	

static void Update_ADC_CLKDIV(uint8_t clkdiv)
{
	#define ADC_CLKDIV_MASK  0xff
	#define ADC_CLKDIV_START 8
	
	LPC_ADC->CR = (LPC_ADC->CR & ~(ADC_CLKDIV_MASK<<ADC_CLKDIV_START)) |
	              (clkdiv<<ADC_CLKDIV_START);  
	
}

static void Set_ADC_Start_Stop(adc_start_stop_t adc_start_stop)
{
	switch(adc_start_stop)
	{
		case ADC_STOP:		LPC_ADC->CR &= ~(1<<24);
		                  break;   
	
		case ADC_START:		LPC_ADC->CR |= (1<<24);
		                  break;   
	}	
}	

#define ADC_DONE_BIT_MASK  (1u<<31)
uint8_t Get_AD0_Status(void)
{
	return ((LPC_ADC->DR[0] & (ADC_DONE_BIT_MASK))?1:0);
}	

uint8_t Get_AD7_Status(void)
{
	return ((LPC_ADC->DR[7] & (ADC_DONE_BIT_MASK))?1:0);
}	

#define MASK_10BIT 0x3ff
uint16_t Read_AD0_Count(void)
{
	return ((LPC_ADC->DR[0] >> 6) & (MASK_10BIT));
}	

uint16_t Read_AD7_Count(void)
{
	return ((LPC_ADC->DR[7] >> 6) & (MASK_10BIT));
}	

static void Set_ADC_Core_Config(void)
{
	Set_ADC_Operation_Mode(ADC_MODE_INDIVIDUAL);
	Select_ADC_Input_Channel(AD_NONE);
	Set_ADC_Start_Stop(ADC_STOP);
	Update_ADC_CLKDIV(47); // 1MHz clock
}

uint16_t Get_AD0(void)
{
	uint16_t a2d_out =0;
	
	// Select the desired channel
	Select_ADC_Input_Channel(AD0_SELECT);
	
	// Start the ADC
	Set_ADC_Start_Stop(ADC_START);
	
	// Wait for the Conversion Complete
  while(0 == Get_AD0_Status());
	
  // Read the 10-bit Count
  a2d_out = Read_AD0_Count();
	
  // Stop the ADC
	Set_ADC_Start_Stop(ADC_STOP);

  // Return the count value	
	return a2d_out;
}	

uint16_t Get_AD7(void)
{
	uint16_t a2d_out =0;
	
	// Select the desired channel
	Select_ADC_Input_Channel(AD7_SELECT);
	
	// Start the ADC
	Set_ADC_Start_Stop(ADC_START);
	
	// Wait for the Conversion Complete
  while(0 == Get_AD7_Status());
	
  // Read the 10-bit Count
  a2d_out = Read_AD7_Count();
	
  // Stop the ADC
	Set_ADC_Start_Stop(ADC_STOP);

  // Return the count value	
	return a2d_out;
}	


void Init_ADC(void)
{
	Set_ADC_Base_Config();
	Set_ADC_Core_Config();
}	
