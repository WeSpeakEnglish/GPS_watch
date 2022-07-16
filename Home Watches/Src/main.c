#include "stm32F10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_adc.h"
#include "uart.h"
#include "delays.h"
#include "timers.h"
#include "ioconfig.h"
#include "adc.h"
#include "RTC.h"
//GPIO_TypeDef * PORT_Temp;





int main(void)
{
  int i;
  RCC->CR   |=  RCC_CR_HSION;            //Включить генератор HSI
  while((RCC->CR & RCC_CR_HSIRDY)==0) {} //Ожидание готовности HSI
  RCC->CFGR &= ~RCC_CFGR_SW;             //Очистка битов выбора источника тактового сигнала
  RCC->CFGR |=  RCC_CFGR_SW_HSI;         //Выбрать источником тактового сигнала HSI
  //Настроить делитель для AHB
   RCC->CFGR &= ~RCC_CFGR_HPRE;           //Очистка битов предделителя "AHB Prescaler"
   RCC->CFGR |=  RCC_CFGR_HPRE_DIV4;      //Установить "AHB Prescaler" равным 8
// RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;




 // PortCConf();
  PortBConf();
  PortAConf();
  ConfigADC();
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  TIM2_init();
  for(i=0; i< 10000; i++){;}
  RTC_Config();

     while(1){

     }

}
