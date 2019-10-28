#include <stdint.h>
#include <clocks.h>
#include <gpio.h>
#include <dio.h>

dio_rgb_t red_led_sts, blue_led_sts, green_led_sts;
void Init_UserKeys(void) 
{
	Set_PCLK_GPIO(PCLK_ENABLE);
	Set_GPIO_Direction(PIO0, PIN1, INPUT);
	Set_GPIO_Direction(PIO0, PIN3, INPUT);
	Set_GPIO_Direction(PIO1, PIN4, INPUT);
}

void Init_RGB(void) 
{
	Set_PCLK_GPIO(PCLK_ENABLE);
	Set_GPIO_Direction(PIO1, PIN2, OUTPUT);
	Set_GPIO_Direction(PIO1, PIN10, OUTPUT);
	Set_GPIO_Direction(PIO2, PIN10, OUTPUT);

	Set_RGB_Red(LED_OFF);
	Set_RGB_Green(LED_OFF);
	Set_RGB_Blue(LED_OFF);
}

void Init_Rotary(void)
{
	Set_PCLK_GPIO(PCLK_ENABLE);
	Set_GPIO_Direction(PIO1, PIN5, INPUT); //Encoder_A
	Set_GPIO_Direction(PIO1, PIN8, INPUT); //Encoder_B
	Set_GPIO_Direction(PIO0, PIN7, INPUT); //Encoder_SW
}

dio_key_t DIO_Get_Key1(void)
{
	dio_key_t sts = Get_GPIO_Status(PIO0,PIN1)? KEY_OPEN : KEY_CLOSE;
	return sts;
}

dio_key_t DIO_Get_Key2(void)
{
	dio_key_t sts = Get_GPIO_Status(PIO0,PIN3)? KEY_OPEN : KEY_CLOSE;
	return sts;
}

dio_key_t DIO_Get_Key3(void)
{
	dio_key_t sts = Get_GPIO_Status(PIO1,PIN4)? KEY_OPEN : KEY_CLOSE;
	return sts;
}

void Set_RGB_Red(dio_rgb_t option)
{
	if(option == LED_ON) {
		Set_GPIO_State(PIO2, PIN10, LOW);
		red_led_sts = LED_ON;
	} else {
		Set_GPIO_State(PIO2, PIN10, HIGH);
		red_led_sts = LED_OFF;
	}
}

void Set_RGB_Green(dio_rgb_t option)
{
	if(option == LED_ON) {
		Set_GPIO_State(PIO1, PIN2, LOW);
		green_led_sts = LED_ON;
	} else {
		Set_GPIO_State(PIO1, PIN2, HIGH);
		green_led_sts = LED_OFF;
	}
}

void Set_RGB_Blue(dio_rgb_t option)
{
	if(option == LED_ON) {
		Set_GPIO_State(PIO1, PIN10, LOW);
		blue_led_sts = LED_ON;
	} else {
		Set_GPIO_State(PIO1, PIN10, HIGH);
		blue_led_sts = LED_OFF;
	}
}

static rotary_status_t Get_Rotary_Status(void)
{
	static rotary_status_t rotary_status = ROTARY_OFF;
	
	if(Get_GPIO_Status(PIO0,PIN7) == LOW)
	{
			while(Get_GPIO_Status(PIO0,PIN7) == LOW){}; // Wait for Release
		
		  if(rotary_status == ROTARY_OFF)
      {
				 rotary_status = ROTARY_ON;
			}				
      else
			{
				 rotary_status = ROTARY_OFF;
			}	
	}	
	return rotary_status;
}	

void Get_Rotary_Data(rotary_params_t *params)
{
	static gpio_state_t prev_statusA = HIGH;
	gpio_state_t current_statusA, current_statusB;
  static int32_t rotary_ctr =0;
  static rotary_dir_t rotary_dir = CLOCKWISE;
	
	current_statusA = Get_GPIO_Status(PIO1,PIN5);
	
	if(current_statusA != prev_statusA)
	{
		current_statusB = Get_GPIO_Status(PIO1,PIN8);
		
		if(current_statusA == current_statusB)
		{
			rotary_dir = COUNTERCLOCKWISE;
			rotary_ctr--;
		}	
		else
		{
			rotary_dir = CLOCKWISE;
			rotary_ctr++;
		}	
		prev_statusA = current_statusA;
	}	
  
	params->count  = rotary_ctr;
	params->dir    = rotary_dir;
	params->status = Get_Rotary_Status();
}
