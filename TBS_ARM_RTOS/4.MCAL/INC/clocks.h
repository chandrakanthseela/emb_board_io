#ifndef __CLOCKS_H__
#define __CLOCKS_H__


typedef enum
{
	PCLK_DISABLE,
	PCLK_ENABLE
}pclk_option_t;	


void Set_PCLK_IOCON(pclk_option_t option);
void Set_PCLK_GPIO(pclk_option_t option);
void Set_PCLK_CT16B0(pclk_option_t option);
void Set_PCLK_CT16B1(pclk_option_t option);
void Set_PCLK_CT32B0(pclk_option_t option);
void Set_PCLK_CT32B1(pclk_option_t option);
void Set_PCLK_ADC(pclk_option_t option);
void Set_PCLK_UART(pclk_option_t option);
void Set_PCLK_I2C(pclk_option_t option);
void Set_PCLK_SSP0(pclk_option_t option);
void Set_PCLK_SSP1(pclk_option_t option);
void Set_PCLK_CAN(pclk_option_t option);
void Set_PCLK_WDT(pclk_option_t option);

void Set_UART_Clock_Divider(uint8_t div_val);
void Set_SSP0_Clock_Divider(uint8_t div_val);


#endif

