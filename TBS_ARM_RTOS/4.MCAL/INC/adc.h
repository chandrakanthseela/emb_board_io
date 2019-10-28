#ifndef __ADC_H__
#define __ADC_H__



typedef enum
{
	AD_NONE    =  0,
	AD0_SELECT = (1<<0),
	AD1_SELECT = (1<<1),
	AD2_SELECT = (1<<2),
	AD3_SELECT = (1<<3),
	AD4_SELECT = (1<<4),
	AD5_SELECT = (1<<5),
	AD6_SELECT = (1<<6),
	AD7_SELECT = (1<<7)
}adc_select_t;	


void Init_ADC(void);
uint16_t Get_AD0(void);
uint16_t Get_AD7(void);


#endif
