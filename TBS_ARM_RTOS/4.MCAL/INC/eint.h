#ifndef __EINT_H__
#define __EINT_H__


typedef enum
{
	LOW_LEVEL,
	HIGH_LEVEL,
	BOTH_EDGE,
	FALL_EDGE,
	RISE_EDGE
}eint_trigger_t;	

typedef enum
{
	EINT_DISABLE,
	EINT_ENABLE
}eint_mask_t;	


void Config_EINT0_Trigger(gpio_pin_t pin, eint_trigger_t trigger);
void Config_EINT1_Trigger(gpio_pin_t pin, eint_trigger_t trigger);
void Config_EINT2_Trigger(gpio_pin_t pin, eint_trigger_t trigger);
void Config_EINT3_Trigger(gpio_pin_t pin, eint_trigger_t trigger);

void Set_EINT0_Mask(gpio_pin_t pin, eint_mask_t eint_mask);
void Set_EINT1_Mask(gpio_pin_t pin, eint_mask_t eint_mask);
void Set_EINT2_Mask(gpio_pin_t pin, eint_mask_t eint_mask);
void Set_EINT3_Mask(gpio_pin_t pin, eint_mask_t eint_mask);

void Clr_EINT0(gpio_pin_t pin);
void Clr_EINT1(gpio_pin_t pin);
void Clr_EINT2(gpio_pin_t pin);
void Clr_EINT3(gpio_pin_t pin);
 

extern volatile uint32_t ctr_eint0;

#endif
