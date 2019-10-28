#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <iocon.h>


#define FUNC_START	   0
#define MODE_START	   3
#define HYS_START	     5
#define ADMODE_START	 7
#define I2CMODE_START	 8

#define FUNC(val)		 (val<<FUNC_START)
#define MODE(val)		 (val<<MODE_START)
#define HYS(val)		 (val<<HYS_START)
#define ADMODE(val)	 (val<<ADMODE_START)
#define I2CMODE(val) (val<<I2CMODE_START)

void ConfigIO(void)
{
		// Enable PCLK for IOCON Module
  Set_PCLK_IOCON(PCLK_ENABLE);

	LPC_IOCON->PIO0_1 = FUNC(0) |  // PIO0_1
	                    MODE(2) |  // PullUp Enabled
	                    HYS(1);    // Hysteresis Disabled 

	LPC_IOCON->PIO1_8 = FUNC(0) |  // PIO1_8
	                    MODE(2) |  // PullUp Enabled
	                    HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO0_2 = FUNC(0) |  // PIO0_2
	                    MODE(2) |  // PullUp Enabled
	                    HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO0_3 = FUNC(0) |  // PIO0_3
	                    MODE(2) |  // PullUp Enabled
	                    HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO0_4 = FUNC(1) |  // SCL (I2C)
                      I2CMODE(0);// I2C Standard Mode
	
	LPC_IOCON->PIO0_5 = FUNC(1) |  // SDA (I2C)
                      I2CMODE(0);// I2C Standard Mode

	LPC_IOCON->PIO0_7 = FUNC(0) |  // PIO0_7
	                    MODE(2) |  // PullUp Enabled
	                    HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO2_10 = FUNC(0) |  // PIO2_10
	                     MODE(2) |  // PullUp Enabled
	                     HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO0_9 = FUNC(1) |  // MOSI0 (SSP0)
	                    MODE(2) |  // PullUp Enabled
	                    HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO1_10 = FUNC(0) |  // PIO1_10
	                     MODE(2) |  // PullUp Enabled
	                     HYS(0)  |  // Hysteresis Disabled 
                       ADMODE(1); // Digital Enable

	LPC_IOCON->PIO2_11 = FUNC(1) |  // SCK0 (SSP0)
	                     MODE(2) |  // PullUp Enabled
	                     HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->R_PIO0_11 = FUNC(2) |  // AD0 (ADC)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(0); // Analog Enable

	LPC_IOCON->R_PIO1_0 =  FUNC(3) |  // CT32B1_CAP0 (GPT)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(1); // Digital Enable

	LPC_IOCON->R_PIO1_1 =  FUNC(3) |  // CT32B1_MAT0 (GPT)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(1); // Digital Enable

	LPC_IOCON->R_PIO1_2 =  FUNC(1) |  // PIO1_2 (GPIO)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(1); // Digital Enable

	LPC_IOCON->PIO1_4 =    FUNC(0) |  // PIO1_4 (GPIO)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(1); // Digital Enable

	LPC_IOCON->PIO1_11 =   FUNC(1) |  // AD7 (ADC)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0)  |  // Hysteresis Disabled 
                         ADMODE(0); // Analog Enable

	LPC_IOCON->PIO1_5  =   FUNC(2) |  // CT32B0_CAP0 (GPT)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO1_6  =   FUNC(1) |  // RXD (UART)  
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0);    // Hysteresis Disabled 

	LPC_IOCON->PIO1_7  =   FUNC(1) |  // TXD (UART)
	                       MODE(2) |  // PullUp Enabled
	                       HYS(0);    // Hysteresis Disabled 
}	
