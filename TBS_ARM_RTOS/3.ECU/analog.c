#include <stdint.h>
#include <lpc11xx.h>
#include <common.h>
#include <clocks.h>
#include <gpio.h>
#include <adc.h>
#include <ssp0.h>
#include <analog.h>

#define Select_MCP4911_Chip()	   Set_GPIO_State(PIO0,PIN2,LOW)
#define Deselect_MCP4911_Chip()	 Set_GPIO_State(PIO0,PIN2,HIGH)
#define Update_DAC_Register(val) Set_SSP0_Transfer(val)

void Init_DAC(void)
{
	Set_GPIO_Direction(PIO0,PIN2,OUTPUT);
	Init_SSP0();
}	

void Measure_vPOT(uint16_t *mv)
{
	uint16_t a2d_raw = Get_AD0();
	
	*mv = (a2d_raw * 322)/100;
}	

void Set_DAC_Input(uint16_t count)
{
	uint16_t dac_word = (1<<13) | (1<<12) | (count<<2);
	
	Select_MCP4911_Chip();
	Update_DAC_Register(dac_word);
	Deselect_MCP4911_Chip();
}	

