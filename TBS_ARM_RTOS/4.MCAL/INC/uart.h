#ifndef __UART_H__
#define __UART_H__


/* UART Driver Global Functions */
void Init_UART(void);
void Send_UART_Byte(uint8_t data_byte);
uint8_t Receive_UART_Byte(void);


#endif
