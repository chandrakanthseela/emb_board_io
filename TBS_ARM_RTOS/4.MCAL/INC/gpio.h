#ifndef __GPIO_H__
#define __GPIO_H__

typedef enum
{
	PIO0,
	PIO1,
	PIO2,
	PIO3
}gpio_port_t;	

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11
}gpio_pin_t;	


typedef enum
{
	INPUT,
	OUTPUT
}gpio_dir_t;	


typedef enum
{
	LOW,
	HIGH,
	TOGGLE
}gpio_state_t;	


void Set_GPIO_Direction(gpio_port_t port, gpio_pin_t pin, gpio_dir_t dir);
gpio_state_t Get_GPIO_Status(gpio_port_t port, gpio_pin_t pin);
void Set_GPIO_State(gpio_port_t port, gpio_pin_t pin, gpio_state_t state);

#endif
