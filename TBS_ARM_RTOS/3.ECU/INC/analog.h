#ifndef __ANALOG_H__
#define __ANALOG_H__


#define Init_Analog() 	Init_ADC()
void Measure_vPOT(uint16_t *mv);


void Init_DAC(void);	
void Set_DAC_Input(uint16_t count);
#define Get_DAC_Out()	  Get_AD7()

#endif
