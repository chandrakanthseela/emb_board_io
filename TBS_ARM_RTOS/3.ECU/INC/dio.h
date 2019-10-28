#ifndef __DIO_H__
#define __DIO_H__

typedef enum {
	KEY_CLOSE,
	KEY_OPEN
} dio_key_t;

typedef enum {
	LED_OFF,
	LED_ON
} dio_rgb_t;

typedef enum
{
	ROTARY_OFF,
	ROTARY_ON
}rotary_status_t;	

typedef enum
{
	CLOCKWISE,
	COUNTERCLOCKWISE
}rotary_dir_t;	

typedef struct
{
	rotary_status_t  status;
	rotary_dir_t     dir;
  int32_t          count;
}rotary_params_t;

void Init_UserKeys(void);
dio_key_t DIO_Get_Key1(void);
dio_key_t DIO_Get_Key2(void);
dio_key_t DIO_Get_Key3(void);

void Init_RGB(void);
void Set_RGB_Red(dio_rgb_t option);
void Set_RGB_Green(dio_rgb_t option);
void Set_RGB_Blue(dio_rgb_t option);

void Init_Rotary(void);
void Get_Rotary_Data(rotary_params_t *params);

#endif
