#ifndef _adc_h
#define _adc_h
#include "stm32F10x.h"


extern u16 ADC_ConvertedValue[8];

void ConfigADC(void);
u16 readADC1(u8 channel);
void ADC1_2_IRQHandler(void);
void LookADC(void);
u8 ADC_array_check(void);
#endif