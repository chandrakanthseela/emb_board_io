#include <stdint.h>
#include <lpc11xx.h>
#include <gpio.h>
#include <eint.h>


void Config_EINT0_Trigger(gpio_pin_t pin,eint_trigger_t trigger)
{
	uint32_t bit_mask = (1<<pin);
	switch(trigger)
	{ 
		case HIGH_LEVEL: LPC_GPIO0->IS  |= (bit_mask); 
										 LPC_GPIO0->IBE &= ~(bit_mask);	
                     LPC_GPIO0->IEV &= ~(bit_mask);										
										 break;
										
		case LOW_LEVEL: LPC_GPIO0->IS  |= (bit_mask); 
                     LPC_GPIO0->IBE &= ~(bit_mask);	
                     LPC_GPIO0->IEV |= (bit_mask);										
		                 break;
		
		case BOTH_EDGE:  LPC_GPIO0->IS  &= ~(bit_mask); 
                     LPC_GPIO0->IBE |= (bit_mask);	
                     break;
		
		case RISE_EDGE:  LPC_GPIO0->IS  &= ~(bit_mask); 
                     LPC_GPIO0->IBE &= ~(bit_mask);	
                     LPC_GPIO0->IEV &= ~(bit_mask);										
                     break;
		
		case FALL_EDGE:  LPC_GPIO0->IS  &= ~(bit_mask); 
                     LPC_GPIO0->IBE &= ~(bit_mask);	
                     LPC_GPIO0->IEV |= (bit_mask);										
                     break;
	}	
}

void Config_EINT1_Trigger(gpio_pin_t pin,eint_trigger_t trigger)
{
	uint32_t bit_mask = (1<<pin);
	switch(trigger)
	{ 
		case HIGH_LEVEL: LPC_GPIO1->IS  |= (bit_mask); 
										 LPC_GPIO1->IBE &= ~(bit_mask);	
                     LPC_GPIO1->IEV &= ~(bit_mask);										
										 break;
										
		case LOW_LEVEL:  LPC_GPIO1->IS  |= (bit_mask); 
                     LPC_GPIO1->IBE &= ~(bit_mask);	
                     LPC_GPIO1->IEV |= (bit_mask);										
		                 break;
		
		case BOTH_EDGE:  LPC_GPIO1->IS  &= ~(bit_mask); 
                     LPC_GPIO1->IBE |= (bit_mask);	
                     break;
		
		case RISE_EDGE:  LPC_GPIO1->IS  &= ~(bit_mask); 
                     LPC_GPIO1->IBE &= ~(bit_mask);	
                     LPC_GPIO1->IEV &= ~(bit_mask);										
                     break;
		
		case FALL_EDGE:  LPC_GPIO1->IS  &= ~(bit_mask); 
                     LPC_GPIO1->IBE &= ~(bit_mask);	
                     LPC_GPIO1->IEV |= (bit_mask);										
                     break;
	}	
}

void Config_EINT2_Trigger(gpio_pin_t pin,eint_trigger_t trigger)
{
	uint32_t bit_mask = (1<<pin);
	switch(trigger)
	{ 
		case HIGH_LEVEL: LPC_GPIO2->IS  |= (bit_mask); 
										 LPC_GPIO2->IBE &= ~(bit_mask);	
                     LPC_GPIO2->IEV &= ~(bit_mask);										
										 break;
										
		case LOW_LEVEL:  LPC_GPIO2->IS  |= (bit_mask); 
                     LPC_GPIO2->IBE &= ~(bit_mask);	
                     LPC_GPIO2->IEV |= (bit_mask);										
		                 break;
		
		case BOTH_EDGE:  LPC_GPIO2->IS  &= ~(bit_mask); 
                     LPC_GPIO2->IBE |= (bit_mask);	
                     break;
		
		case RISE_EDGE:  LPC_GPIO2->IS  &= ~(bit_mask); 
                     LPC_GPIO2->IBE &= ~(bit_mask);	
                     LPC_GPIO2->IEV &= ~(bit_mask);										
                     break;
		
		case FALL_EDGE:  LPC_GPIO2->IS  &= ~(bit_mask); 
                     LPC_GPIO2->IBE &= ~(bit_mask);	
                     LPC_GPIO2->IEV |= (bit_mask);										
                     break;
	}	
}

void Config_EINT3_Trigger(gpio_pin_t pin,eint_trigger_t trigger)
{
	uint32_t bit_mask = (1<<pin);
	switch(trigger)
	{ 
		case HIGH_LEVEL: LPC_GPIO3->IS  |= (bit_mask); 
										 LPC_GPIO3->IBE &= ~(bit_mask);	
                     LPC_GPIO3->IEV &= ~(bit_mask);										
										 break;
										
		case LOW_LEVEL:  LPC_GPIO3->IS  |= (bit_mask); 
                     LPC_GPIO3->IBE &= ~(bit_mask);	
                     LPC_GPIO3->IEV |= (bit_mask);										
		                 break;
		
		case BOTH_EDGE:  LPC_GPIO3->IS  &= ~(bit_mask); 
                     LPC_GPIO3->IBE |= (bit_mask);	
                     break;
		
		case RISE_EDGE:  LPC_GPIO3->IS  &= ~(bit_mask); 
                     LPC_GPIO3->IBE &= ~(bit_mask);	
                     LPC_GPIO3->IEV &= ~(bit_mask);										
                     break;
		
		case FALL_EDGE:  LPC_GPIO3->IS  &= ~(bit_mask); 
                     LPC_GPIO3->IBE &= ~(bit_mask);	
                     LPC_GPIO3->IEV |= (bit_mask);										
                     break;
	}	
}

void Set_EINT0_Mask(gpio_pin_t pin,eint_mask_t eint_mask)
{
	uint32_t bit_mask = (1<<pin);
	
	switch(eint_mask)
	{
		case EINT_DISABLE: LPC_GPIO0->IE  &= ~(bit_mask); 
											 break;
		case EINT_ENABLE:  LPC_GPIO0->IE  |= (bit_mask); 
											 break;
	}
}	

void Set_EINT1_Mask(gpio_pin_t pin,eint_mask_t eint_mask)
{
	uint32_t bit_mask = (1<<pin);
	
	switch(eint_mask)
	{
		case EINT_DISABLE: LPC_GPIO1->IE  &= ~(bit_mask); 
											 break;
		case EINT_ENABLE:  LPC_GPIO1->IE  |= (bit_mask); 
											 break;
	}
}	

void Set_EINT2_Mask(gpio_pin_t pin,eint_mask_t eint_mask)
{
	uint32_t bit_mask = (1<<pin);
	
	switch(eint_mask)
	{
		case EINT_DISABLE: LPC_GPIO2->IE  &= ~(bit_mask); 
											 break;
		case EINT_ENABLE:  LPC_GPIO2->IE  |= (bit_mask); 
											 break;
	}
}	

void Set_EINT3_Mask(gpio_pin_t pin,eint_mask_t eint_mask)
{
	uint32_t bit_mask = (1<<pin);
	
	switch(eint_mask)
	{
		case EINT_DISABLE: LPC_GPIO3->IE  &= ~(bit_mask); 
											 break;
		case EINT_ENABLE:  LPC_GPIO3->IE  |= (bit_mask); 
											 break; 
	}
}	

void Clr_EINT0(gpio_pin_t pin)
{
	uint32_t bit_mask = (1<<pin);
	
	LPC_GPIO0->IC = bit_mask;
}	

void Clr_EINT1(gpio_pin_t pin)
{
	uint32_t bit_mask = (1<<pin);
	
	LPC_GPIO1->IC = bit_mask;
}	


void Clr_EINT2(gpio_pin_t pin)
{
	uint32_t bit_mask = (1<<pin);
	
	LPC_GPIO2->IC = bit_mask;
}	

void Clr_EINT3(gpio_pin_t pin)
{
	uint32_t bit_mask = (1<<pin);
	
	LPC_GPIO3->IC = bit_mask;
}	



void PIOINT0_IRQHandler(void)
{

	
	
}	

void PIOINT1_IRQHandler(void)
{
	
}	

void PIOINT2_IRQHandler(void)
{
	
}	


void PIOINT3_IRQHandler(void)
{
	
}	


	
