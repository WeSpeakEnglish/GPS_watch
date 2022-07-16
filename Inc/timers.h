#ifndef _timers_h
#define _timers_h
#include "stm32f10x.h"

extern volatile u8 TIM2_flag;
void TIM4_init(void);
void IWDG_init(void);
void delay_ms(u16 millisec);
void TIM2_IRQHandler(void);
void TIM2_init(u16);
#endif


