#include <stdint.h>
#include <lpc11xx.h>
#include <common.h>
#include <clocks.h>

#define PCLK_IOCON_MASK	   (1<<16)
#define PCLK_GPIO_MASK	   (1<<6)
#define PCLK_CT16B0_MASK	 (1<<7)
#define PCLK_CT16B1_MASK	 (1<<8)
#define PCLK_CT32B0_MASK	 (1<<9)
#define PCLK_CT32B1_MASK	 (1<<10)
#define PCLK_ADC_MASK	     (1<<13)
#define PCLK_UART_MASK	   (1<<12)
#define PCLK_I2C_MASK	     (1<<5)
#define PCLK_SSP0_MASK	   (1<<11)
#define PCLK_SSP1_MASK	   (1<<18)
#define PCLK_CAN_MASK	     (1<<17)
#define PCLK_WDT_MASK	     (1<<15)

void Set_PCLK_ADC(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_ADC_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_ADC_MASK;
	}
}	


void Set_PCLK_GPIO(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_GPIO_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_GPIO_MASK;
	}
}	


void Set_PCLK_UART(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_UART_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_UART_MASK;
	}
}	

void Set_UART_Clock_Divider(uint8_t div_val)
{
	LPC_SYSCON->UARTCLKDIV = div_val;
}

void Set_PCLK_I2C(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_I2C_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_I2C_MASK;
	}
}	

void Set_PCLK_SSP0(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_SSP0_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_SSP0_MASK;
	}
}	

void Set_SSP0_Clock_Divider(uint8_t div_val)
{
	LPC_SYSCON->SSP0CLKDIV = div_val; 

}

void Set_PCLK_IOCON(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_IOCON_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_IOCON_MASK;
	}
}	

void Set_PCLK_CT32B0(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_CT32B0_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_CT32B0_MASK;
	}
}	

void Set_PCLK_CT32B1(pclk_option_t option)
{
	if(PCLK_DISABLE == option)
	{
		LPC_SYSCON->SYSAHBCLKCTRL &= ~PCLK_CT32B1_MASK;
	}
	else
	{
		LPC_SYSCON->SYSAHBCLKCTRL |= PCLK_CT32B1_MASK;
	}
}	
