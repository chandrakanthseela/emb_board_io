#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <gpio.h>
#include <ssp0.h>

typedef enum
{
	SPI_DISABLE,
	SPI_ENABLE
}spi_t;


typedef enum
{
	SPI_NOT_BUSY,
	SPI_BUSY
}spi_status_t;	

typedef enum
{
	SPI_MODE0,
	SPI_MODE1,
	SPI_MODE2,
	SPI_MODE3
}spi_mode_t;

typedef enum
{
	SPI_DATA_8BIT  = 0x7,
	SPI_DATA_16BIT = 0xF
}spi_data_size_t;


static void Set_SSP0_Base_Config(void)
{
// Enable PCLK for SPI0 in SYSAHBCLKCTRL
	Set_PCLK_SSP0(PCLK_ENABLE);
	
// Configure SPIO_CLKDIV   
	Set_SSP0_Clock_Divider(1); // 48MHz/1 = 48MHz
	
// Desassert SPI0 Reset
	LPC_SYSCON->PRESETCTRL |= (1<<0);
}	

static void Set_SSP0(spi_t option)
{
	switch(option)
	{
		case SPI_DISABLE:  LPC_SSP0->CR1 &= ~(1<<1); 
		                   break;
	
		case SPI_ENABLE:   LPC_SSP0->CR1 |= (1<<1);
		                   break;
	}	
}	


static spi_status_t Get_SSP0_Status(void)
{
	return ((LPC_SSP0->SR & (1<<4))?SPI_BUSY:SPI_NOT_BUSY);
}	

static uint16_t Get_SSP0_Data(void)
{
   return (LPC_SSP0->DR);
}	

static void Set_SSP0_Data(uint16_t spi_data)
{
   LPC_SSP0->DR = spi_data;
}	


static void Set_SSP0_Clock_1MHz(void)
{
	LPC_SSP0->CPSR = 48;  // SPI_CLOCK = SPI_CLKDIV/CPSR = 48MHz/48 = 1MHz
}	


void Set_SSP0_Mode(spi_mode_t spi_mode)
{
	switch(spi_mode)
	{
		case SPI_MODE0:   LPC_SSP0->CR0 &= ~(1<<6); // CPOL = 0
										  LPC_SSP0->CR0 &= ~(1<<7); // CPHA = 0
		                  break; 

		case SPI_MODE1:   LPC_SSP0->CR0 &= ~(1<<6); // CPOL = 0
										  LPC_SSP0->CR0 |=  (1<<7); // CPHA = 1
		                  break; 

		case SPI_MODE2:   LPC_SSP0->CR0 |=  (1<<6); // CPOL = 1
										  LPC_SSP0->CR0 &= ~(1<<7); // CPHA = 0
		                  break; 

		case SPI_MODE3:   LPC_SSP0->CR0 |=  (1<<6); // CPOL = 1
										  LPC_SSP0->CR0 |=  (1<<7); // CPHA = 1
		                  break; 
	}	
}


#define FOURBIT_MASK (0xF)
void Set_SSP0_Data_Size(spi_data_size_t spi_data_size)
{
	LPC_SSP0->CR0 = (LPC_SSP0->CR0 & ~(FOURBIT_MASK<<0)) | (spi_data_size<<0);
}	

void Init_SSP0(void)
{
	Set_SSP0_Base_Config();
	
	// Set SPI Data Size to 16-bit
	Set_SSP0_Data_Size(SPI_DATA_16BIT);
	
	// Set SPI mode to MODE0
	Set_SSP0_Mode(SPI_MODE0);
	

	// Set SPI clock to 1MHz
	Set_SSP0_Clock_1MHz();
	
	// Enable SPI 
  Set_SSP0(SPI_ENABLE);
}	

uint16_t Set_SSP0_Transfer(uint16_t master_data)
{
	uint16_t slave_data =0;
	
	// Write Master data in DR
	Set_SSP0_Data(master_data);
	
	// Wait for the Transfer complete
	while(Get_SSP0_Status()==SPI_BUSY);
	
	// Read the data received from slave in DR
	slave_data = Get_SSP0_Data();
	
	// return slave data
  return slave_data;	
}
