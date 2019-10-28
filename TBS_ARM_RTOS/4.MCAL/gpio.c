#include <stdint.h>
#include <lpc11xx.h>
#include <gpio.h>


void Set_GPIO_Direction(gpio_port_t port, gpio_pin_t pin, gpio_dir_t dir)
{
	uint32_t pin_mask = (1<<pin);
	
	switch(port)
	{
		case PIO0:	if(INPUT == dir)
								{
									LPC_GPIO0->DIR &= ~pin_mask;
								}	
								else
								{
									LPC_GPIO0->DIR |= pin_mask;
								}	
								break;

		case PIO1:	if(INPUT == dir)
								{
									LPC_GPIO1->DIR &= ~pin_mask;
								}	
								else
								{
									LPC_GPIO1->DIR |= pin_mask;
								}	
								break;

		case PIO2:	if(INPUT == dir)
								{
									LPC_GPIO2->DIR &= ~pin_mask;
								}	
								else
								{
									LPC_GPIO2->DIR |= pin_mask;
								}	
								break;

		case PIO3:	if(INPUT == dir)
								{
									LPC_GPIO3->DIR &= ~pin_mask;
								}	
								else
								{
									LPC_GPIO3->DIR |= pin_mask;
								}	
								break;
	}	
}	

gpio_state_t Get_GPIO_Status(gpio_port_t port, gpio_pin_t pin)
{
	uint32_t pin_mask = (1<<pin);
	gpio_state_t pin_state = HIGH;
	
	switch(port)
	{
		case PIO0:	pin_state = (LPC_GPIO0->DATA & pin_mask)?HIGH:LOW;
		            break;
		case PIO1:	pin_state = (LPC_GPIO1->DATA & pin_mask)?HIGH:LOW;
		            break;
		case PIO2:	pin_state = (LPC_GPIO2->DATA & pin_mask)?HIGH:LOW;
		            break;
		case PIO3:	pin_state = (LPC_GPIO3->DATA & pin_mask)?HIGH:LOW;
		            break;
	}	
	return pin_state; 
}

void Set_GPIO_State(gpio_port_t port, gpio_pin_t pin, gpio_state_t state)
{
	uint32_t pin_mask = (1<<pin);
	
	switch(port)
	{
		case PIO0:	if(LOW == state)
								{
									LPC_GPIO0->DATA &= ~pin_mask;
								}	
								else if(HIGH == state)
								{
									LPC_GPIO0->DATA |= pin_mask;
								}
								else
								{
									LPC_GPIO0->DATA ^= pin_mask;
								}	
								break;
		case PIO1:	if(LOW == state)
								{
									LPC_GPIO1->DATA &= ~pin_mask;
								}	
								else if(HIGH == state)
								{
									LPC_GPIO1->DATA |= pin_mask;
								}
								else
								{
									LPC_GPIO1->DATA ^= pin_mask;
								}	
								break;
		case PIO2:	if(LOW == state)
								{
									LPC_GPIO2->DATA &= ~pin_mask;
								}	
								else if(HIGH == state)
								{
									LPC_GPIO2->DATA |= pin_mask;
								}
								else
								{
									LPC_GPIO2->DATA ^= pin_mask;
								}	
								break;
		case PIO3:	if(LOW == state)
								{
									LPC_GPIO3->DATA &= ~pin_mask;
								}	
								else if(HIGH == state)
								{
									LPC_GPIO3->DATA |= pin_mask;
								}
								else
								{
									LPC_GPIO3->DATA ^= pin_mask;
								}	
								break;
	}
}	
