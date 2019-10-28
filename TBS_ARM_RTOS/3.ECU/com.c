#include <stdint.h>
#include <lpc11xx.h>
#include <common.h>
#include <clocks.h>
#include <uart.h>
#include <com.h>
#include <stdio.h>

void Send_COM_String(uint8_t *str)
{
	while(*str != NULL)
	{
			Send_COM_Data(*str);
		  str++;
	}	
}	

void Send_COM_Num(int32_t num)  // max 9999
{
	uint8_t ones, tens, cents, thousands;
	
	if(num < 0) {
		num *= -1;
		Send_COM_String("-");
	}

 	if(num < 10) // 1-digit number
	{
		Send_COM_Data(num + 0x30);
	}	
	else if((num >= 10) && (num < 100)) // 2-digit number
	{
		tens  = (num/10);
		ones  = (num%10);
		Send_COM_Data(tens + 0x30);
		Send_COM_Data(ones + 0x30);
	}	
	else if((num >= 100) && (num < 1000)) // 3-digit number
	{
		cents = (num/100);
		tens  = (num%100)/10;
		ones  = (num%100)%10;

		Send_COM_Data(cents + 0x30);
		Send_COM_Data(tens + 0x30);
		Send_COM_Data(ones + 0x30);
	}	
	else if((num >= 1000) && (num < 10000)) // 4-digit number
	{
		thousands = (num/1000);
		cents = ((num%1000)/100);
		tens  = (num%100)/10;
		ones  = (num%100)%10;

		Send_COM_Data(thousands + 0x30);
		Send_COM_Data(cents + 0x30);
		Send_COM_Data(tens + 0x30);
		Send_COM_Data(ones + 0x30);
	}	
}	

