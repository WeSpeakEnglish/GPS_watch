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
  RCC->CR   |=  RCC_CR_HSION;            //�������� ��������� HSI
  while((RCC->CR & RCC_CR_HSIRDY)==0) {} //�������� ���������� HSI
  RCC->CFGR &= ~RCC_CFGR_SW;             //������� ����� ������ ��������� ��������� �������
  RCC->CFGR |=  RCC_CFGR_SW_HSI;         //������� ���������� ��������� ������� HSI
  //��������� �������� ��� AHB
   RCC->CFGR &= ~RCC_CFGR_HPRE;           //������� ����� ������������ "AHB Prescaler"
   RCC->CFGR |=  RCC_CFGR_HPRE_DIV4;      //���������� "AHB Prescaler" ������ 8
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
