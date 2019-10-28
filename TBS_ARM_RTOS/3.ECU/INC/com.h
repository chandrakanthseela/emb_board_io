#ifndef __COM_H__
#define __COM_H__

#define Init_COM()		  				Init_UART()
#define Send_COM_Data(data)		  Send_UART_Byte(data)
#define Receive_COM_Data()	Receive_UART_Byte()

void Send_COM_String(uint8_t *str);
void Send_COM_Num(int32_t num);


#endif
