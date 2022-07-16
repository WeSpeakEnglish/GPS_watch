#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_adc.h"
#include "uart.h"
#include "delays.h"
#include "digits.h"
#include "timers.h"
#include "ioconfig.h"
#include "RTC.h"
#include "GPS.h"
#include "user_interface.h"
#include "stm32f10x_rtc.h"

int main(void)
{

  //RCC->CR   |=  RCC_CR_HSEON;            //�������� ��������� HSE
//  while((RCC->CR & RCC_CR_HSERDY)==0) {} //�������� ���������� HSE
//  delay_ms(1);

 // RCC->CFGR &= ~RCC_CFGR_HPRE;           //������� ����� ������������ "AHB Prescaler"
 // delay_ms(1);
 // RCC->CFGR &= ~RCC_CFGR_SW;             //������� ����� ������ ��������� ��������� �������
 // RCC->CFGR |=  RCC_CFGR_SW_HSE;         //������� ���������� ��������� ������� HSE
 //delay_ms(1);
//RCC_DeInit(); //    ����� �������� ��������� ����������
//RCC_HSICmd(DISABLE); // ���������� ����������� RC HSI 8��� ����������
//RCC_HSEConfig(RCC_HSE_ON); //   ��������� �������� ��������� ����������
//RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE); //  �� ��������� ���� ������ ������������ � �������� ����������
  Time.Z = 3;
  PortCConf();
  PortBConf();
  PortAConf();
delay_ms(1000);
 AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_DISABLE;// JTAG OUT
 //PA13
  GPIOA->CRH &=~(GPIO_CRH_CNF13|GPIO_CRH_MODE13);
  GPIOA->CRH |= GPIO_CRH_MODE13_1;
  GPIOA->ODR &= ~GPIO_ODR_ODR13;

  //PA14
  GPIOA->CRH &=~(GPIO_CRH_CNF14|GPIO_CRH_MODE14);
  GPIOA->CRH |= GPIO_CRH_MODE14_1;
  GPIOA->ODR &= ~GPIO_ODR_ODR14;

delay_ms(3000);






Time.Z = (s8)GetZone();



//delay_ms(1000);
//ViewZone();

EraseDigits();
TestSegments();
EraseDigits();

CheckZone();


  Init_UART1();
  InterruptConf();
  RTC_Config();
  IWDG_init();

   while(1){
    IWDG_ReloadCounter();
    if(CommandGPS)
        CommandGPSRunner();
if(statusSyncG !=2)PB5_O = 1;

     }

}
