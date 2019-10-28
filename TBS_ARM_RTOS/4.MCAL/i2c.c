#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <i2c.h>


void Set_I2C_Master_Ack(i2c_master_ack_t option)
{
	switch(option)
	{
		case MASTER_ACK:	LPC_I2C->CONSET = (1<<2);
		                  break;

		case MASTER_NACK:	LPC_I2C->CONCLR = (1<<2);
		                  break;
	}	
}

uint8_t Get_I2C_Status_Code(void)
{
	return ((uint8_t)LPC_I2C->STAT);
}	

void Write_I2C_Byte(uint8_t data_byte)
{
	LPC_I2C->DAT = data_byte;
}	

uint8_t Read_I2C_Byte(void)
{
	return ((uint8_t)LPC_I2C->DAT);
}	

static void Set_I2C_Clock_100KHz(void)
{
	 // I2CPCLK = 48MHz
	LPC_I2C->SCLH = 240;
	LPC_I2C->SCLL = 240;
}	


void Set_I2C_Master_Command(i2c_master_cmd_t cmd)
{
	switch(cmd)
	{
		case ISSUE_START:		LPC_I2C->CONSET = (1<<5);
		                    break;  
	
		case CLEAR_START:		LPC_I2C->CONCLR = (1<<5);
		                    break;  

		case ISSUE_STOP:		LPC_I2C->CONSET = (1<<4);
		                    break;  
	}	
}	


void Set_I2C_Interface(i2c_en_t option)
{
	switch(option)
	{
		case ENABLE_I2C: 		LPC_I2C->CONSET = (1<<6);
												break;
	
		case DISABLE_I2C: 	LPC_I2C->CONCLR = (1<<6);
												break;
	}	
}	

void Wait_I2C_Phase_Complete(void)
{
	while ((LPC_I2C->CONSET & (1<<3)) == 0);
}	

uint8_t GetI2CStatus(void)
{
    return ((LPC_I2C->CONSET & (1 << 3)) ? 1 : 0);
}

void Clear_I2C_Status(void)
{
	LPC_I2C->CONCLR = (1<<3);
}	

static void Set_I2C_Base_Config(void)
{	
	/* Enable PCLK for I2C in SYSAHBCLKCTRL of SYSCON */
	Set_PCLK_I2C(PCLK_ENABLE);
	
	/* De-assert the reset for I2C in PRESETCTRL of SYSCON */
	LPC_SYSCON->PRESETCTRL |= (1<<1);
}

void Init_I2C(void)
{
	// I2C Base Configuration
	Set_I2C_Base_Config();
	
	// Enable I2C Interface
	Set_I2C_Interface(ENABLE_I2C);
	
	// Set I2C Clock to 100KHz
	Set_I2C_Clock_100KHz();
}	
