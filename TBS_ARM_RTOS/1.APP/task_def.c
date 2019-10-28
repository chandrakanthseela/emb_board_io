#include <stdint.h>
#include <lpc11xx.h>
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <task_def.h>
#include <dio.h>
#include <adc.h>
#include <analog.h>
#include <pwm.h>
#include <ct32b1.h>
#include <clocks.h>
#include <uart.h>
#include <com.h>
#include <lm75.h>

static void clear_screen(void)
{
	/* http://ascii-table.com/ansi-escape-sequences-vt-100.php -> for escape codes*/
	Send_UART_Byte(27);
	Send_COM_String("[2J"); /*for clear sccreen*/
	Send_UART_Byte(27);
	Send_COM_String("[f"); // return cursor to start
}
static void clear_Input(void)
{
	/* http://ascii-table.com/ansi-escape-sequences-vt-100.php -> for escape codes*/
	Send_UART_Byte(27);
	Send_COM_String("[f"); // return cursor to start

	Send_UART_Byte(27);
	Send_COM_String("[15B"); // MOVE CURSOR TO END OF IP

	Send_UART_Byte(27);
	Send_COM_String("[1J"); /*for clear screen FROM CURSOR UP*/
}

extern xTaskHandle Task_OP_Handle;

uint8_t key1, key2, key3, prevValk1, prevValk2, prevValk3, volt, milliVolt, prvMv;
rotary_params_t rot;
rotary_status_t prvSts;
rotary_dir_t prvDir;
int32_t prvCount;

uint16_t milliVolt_count;
uint32_t tem, prevTem;

output_choice_t main_choice;
rgb_choice_t color;

uint16_t dac_pwm_ip;
uint16_t dac_out;
uint8_t dac_volt, dac_mv;

void Task_Input(void *args)
{

	while (1)
	{
		key1 = DIO_Get_Key1();
		key2 = DIO_Get_Key2();
		key3 = DIO_Get_Key3();
		Get_Rotary_Data(&rot);
		Measure_vPOT(&milliVolt_count);
		volt = milliVolt_count / 1000;
		milliVolt = (milliVolt_count % 1000) / 100;
		tem = ReadLM75();
	}
}

static void Input_Status_Log()
{
	Send_UART_Byte(27);
	Send_COM_String("[f");

	Send_COM_String("\r------------------------------------\n");
	Send_COM_String("\r            Input Monitor           \n");
	Send_COM_String("\r------------------------------------\n");
	Send_COM_String("\r Key 1 = ");
	key1 ? Send_COM_String("OPEN \n") : Send_COM_String("CLOSE \n");

	Send_COM_String("\r Key 2 = ");
	key2 ? Send_COM_String("OPEN \n") : Send_COM_String("CLOSE \n");

	Send_COM_String("\r Key 3 = ");
	key3 ? Send_COM_String("OPEN \n") : Send_COM_String("CLOSE \n");
	Send_COM_String("\n");

	Send_COM_String("\r Rotary Count = ");
	Send_COM_Num(rot.count);
	Send_COM_String("\n");

	Send_COM_String("\r Rotary Dir = ");
	rot.dir ? Send_COM_String("COUNTER CLOCKWISE\n") : Send_COM_String("CLOCKWISE\n");

	Send_COM_String("\r Rotary Status = ");
	rot.status ? Send_COM_String("ON \n") : Send_COM_String("OFF \n");
	Send_COM_String("\n");

	Send_COM_String("\r POT Voltage = ");
	Send_COM_Num(volt);
	Send_COM_String(".");
	Send_COM_Num(milliVolt);
	Send_COM_String("V\n");
	Send_COM_String("\n");

	Send_COM_String("\r DAC Voltage = ");
	Send_COM_Num(dac_volt);
	Send_COM_String(".");
	Send_COM_Num(dac_mv);
	Send_COM_String("V\n");
	Send_COM_String("\n");

	Send_COM_String("\r Temperature = ");
	Send_COM_Num(tem);
	Send_COM_String(" °C\n");

	Send_UART_Byte(27);
	Send_COM_String("[f");
	Send_UART_Byte(27);
	Send_COM_String("[16B");
	
	Send_COM_String("\n\r--------------OUTPUT-----------------\n");
	Send_COM_String("\r Select the output based on number \n");
	Send_COM_String("\r 0 - RGB, 1 - PWM, 2 - DAC \n\r");
}

void Task_COM(void *args)
{
	uint8_t data, ind = 0, num_ind = 0, arr[4] = {0};
	int8_t ctr;

	while (1)
	{
		if ( key1 != prevValk1 
			|| key2 != prevValk2 
			|| key3 != prevValk3 
			|| rot.count != prvCount 
			|| rot.status != prvSts 
			|| rot.dir != prvDir
			|| milliVolt != prvMv 
			//|| tem != prevTem
			)
		{
			clear_Input();
			Input_Status_Log();
			prevValk1 = key1;
			prevValk2 = key2;
			prevValk3 = key3;
			prvCount = rot.count;
			prvSts = rot.status;
			prvMv = milliVolt;
			prevTem = tem;
			prvDir = rot.dir;

			if(main_choice == RGB && ind == 1) {
			Send_UART_Byte(27);
			Send_COM_String("[f"); // return cursor to start

			Send_UART_Byte(27);
			Send_COM_String("[22B"); // MOVE CURSOR TO END OF screen
		} else if(main_choice == PWM && num_ind < 2) {
			Send_UART_Byte(27);
			Send_COM_String("[f"); // return cursor to start

			Send_UART_Byte(27);
			Send_COM_String("[21B"); // MOVE CURSOR TO END OF screen
		} else if(main_choice == DAC && num_ind < 3) {
			Send_UART_Byte(27);
			Send_COM_String("[f"); // return cursor to start

			Send_UART_Byte(27);
			Send_COM_String("[21B"); // MOVE CURSOR TO END OF screen
		}
		}

		data = Receive_COM_Data();
		if (data != 0 && (data - 0x30) < 3)
		{
			ind++;
			if (ind == 1)
			{
				main_choice = ((output_choice_t)(data - 0x30));
				switch (main_choice)
				{
				case RGB:	Send_COM_String("\r Select a color \n");
							Send_COM_String("\r 0 - OFF, 1 - RED, 2 - BLUE, 3 - GREEN, 4 - WHITE \n\r");
							break;
				case PWM:	Send_COM_String("\r Enter Duty ratio in 3 digit format \n\r");
							break;
				case DAC:	Send_COM_String("\r Enter DAC input count in 4 digit format \n\r");
							break;
				
				}
			}
			else if (ind > 1)
			{
				switch (main_choice)
				{
				case RGB:	color = ((rgb_choice_t)(data - 0x30));
							ind = 0;
							vTaskResume(Task_OP_Handle);
							clear_screen();
							Input_Status_Log();
							break;
				case PWM:	arr[num_ind++] = data - 0x30;
							if(num_ind > 2)
							{
								num_ind = 0;
								dac_pwm_ip = 0;
								for(ctr = 0; ctr <= 2; ctr++)
								{
									dac_pwm_ip = dac_pwm_ip*10 + arr[ctr];
									arr[ctr] = 0;
								}
								ind = 0;
								vTaskResume(Task_OP_Handle);
								clear_screen();
								Input_Status_Log();
							}
							break;
				case DAC:	arr[num_ind++] = data - 0x30;
							if(num_ind > 3)
							{
								num_ind = 0;
								dac_pwm_ip = 0;
								for(ctr = 0; ctr <= 3; ctr++)
								{
									dac_pwm_ip = dac_pwm_ip*10 + arr[ctr];
									arr[ctr] = 0;
								}
								ind = 0;
								vTaskResume(Task_OP_Handle);
								clear_screen();
								Input_Status_Log();
							}
							break;

				}
			}
		}

		
	}
}

void Task_Output(void *args)
{
	while (1)
	{
		switch (main_choice)
		{
		case RGB:	switch (color)
					{
						case OFF:	Set_RGB_Red(LED_OFF);
									Set_RGB_Green(LED_OFF);
									Set_RGB_Blue(LED_OFF);
									break;
						case RED:	Set_RGB_Red(LED_ON);
									Set_RGB_Green(LED_OFF);
									Set_RGB_Blue(LED_OFF);
									break;
						case BLUE:	Set_RGB_Red(LED_OFF);
									Set_RGB_Green(LED_OFF);
									Set_RGB_Blue(LED_ON);
									break;
						case GREEN:	Set_RGB_Red(LED_OFF);
									Set_RGB_Green(LED_ON);
									Set_RGB_Blue(LED_OFF);
									break;
						case WHITE:	Set_RGB_Red(LED_ON);
									Set_RGB_Green(LED_ON);
									Set_RGB_Blue(LED_ON);
									break;
					}
					vTaskSuspend(Task_OP_Handle);
					break;
		
		case PWM:	Set_PWM_Duty(dac_pwm_ip);
					vTaskSuspend(Task_OP_Handle);
					break;

		case DAC:	Set_DAC_Input(dac_pwm_ip);
					dac_out = (Get_DAC_Out() * 322)/100;
					dac_volt = dac_out/1000;
					dac_mv = (dac_out % 1000)/100;
					vTaskSuspend(Task_OP_Handle);
					break;
		}
	}
}
