#include <stdint.h>
#include <lpc11xx.h>
#include <clocks.h>
#include <uart.h>


typedef enum
{
	UART_DATA_5BIT,
	UART_DATA_6BIT,
	UART_DATA_7BIT,
	UART_DATA_8BIT
}uart_data_size_t;	

typedef enum
{
	UART_PARITY_DISABLE,
	UART_PARITY_ODD,
	UART_PARITY_EVEN
}uart_parity_t;	

typedef enum
{
	UART_BAUD_LOCK,
	UART_BAUD_UNLOCK
}uart_baud_lock_t;	

void Set_UART_Baud_Lock(uart_baud_lock_t option)
{
	switch(option)
	{	
		case UART_BAUD_LOCK:			LPC_UART->LCR &= ~(1<<7);
															break;

		case UART_BAUD_UNLOCK:		LPC_UART->LCR |= (1<<7);
															break;	
	}
}	


void Set_UART_Data_Size(uart_data_size_t data_size)
{
#define UART_WLS_MASK   0x3
#define UART_WLS_START  0

	LPC_UART->LCR = (LPC_UART->LCR & ~(UART_WLS_MASK)) | (data_size);
}	

void Set_UART_Parity(uart_parity_t parity)
{
	switch(parity)
	{
		case UART_PARITY_DISABLE:		LPC_UART->LCR &= ~(1<<3);
			                          break; 

		case UART_PARITY_ODD:			  LPC_UART->LCR |= (1<<3);
			                          LPC_UART->LCR &= ~(1<<4);
																break; 
			                           
		case UART_PARITY_EVEN:			LPC_UART->LCR |= (1<<3);
			                          LPC_UART->LCR |= (1<<4);
																break; 
	}	
}	
void Update_UART_DLL(uint8_t dll_value)
{
	LPC_UART->DLL = dll_value;
}	

void Update_UART_DLM(uint8_t dlm_value)
{
	LPC_UART->DLM = dlm_value;
}	

void Update_UART_FDR(uint8_t fdr_value)
{
	LPC_UART->FDR = fdr_value;
}	

void Set_UART_Baud_9600(void)
{
	Set_UART_Baud_Lock(UART_BAUD_UNLOCK);
  
	Update_UART_DLL(0xfa);
	Update_UART_DLM(0);
	Update_UART_FDR(0x41);

	Set_UART_Baud_Lock(UART_BAUD_LOCK);

}	
void Set_UART_Baud_57600(void)
{
	Set_UART_Baud_Lock(UART_BAUD_UNLOCK);
  
	Update_UART_DLL(0x19);
	Update_UART_DLM(0);
	Update_UART_FDR(0xcd);

	Set_UART_Baud_Lock(UART_BAUD_LOCK);

}	

uint8_t Get_UART_TxBuf_Status(void)
{
	return ((LPC_UART->LSR & (1<<5))?1:0);
}	

uint8_t Get_UART_RxBuf_Status(void)
{
	return ((LPC_UART->LSR & (1<<0))?1:0);
}	

void Update_UART_TxBuf(uint8_t data)
{
	LPC_UART->THR = data;
}	

uint8_t Read_UART_RxBuf(void)
{
	return (LPC_UART->RBR);
}	

void Send_UART_Byte(uint8_t data_byte)
{
	// Wait if UART is Busy
	while(0 == Get_UART_TxBuf_Status());
		
	// Load the byte in THR
 Update_UART_TxBuf(data_byte);
}	

uint8_t Receive_UART_Byte(void)
{
	uint8_t receive_byte =0;
	
	if(1 == Get_UART_RxBuf_Status())
	{
		receive_byte = Read_UART_RxBuf();
	}	
	return receive_byte;
}	


void Set_UART_Core_Config(void)
{
	// Data Size set to 8-bit
	Set_UART_Data_Size(UART_DATA_8BIT);
	
	// Disable Parity
	Set_UART_Parity(UART_PARITY_DISABLE);
	
	// Set a baud of 57600
	Set_UART_Baud_57600();
}	

void Set_UART_Base_Config(void)
{
  // IOCON
	  // Refer ioconfig.h/ .c
	
	// PCLK Enable/ Disable
	Set_PCLK_UART(PCLK_ENABLE);
	
	// Set Global UART Clock divider
	Set_UART_Clock_Divider(1); // PCLK = 48MHz
}	

void Init_UART(void)
{
	Set_UART_Base_Config();
	Set_UART_Core_Config();
}
