#include "timers.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_pwr.h"
#include "RTC.h"
#include "digits.h"
#include "stm32f10x_iwdg.h"
#include "GPS.h"
//////////////////////////////////////////////
volatile u8 TIM2_flag = 0;
/////////////////////////////////////////////

void IWDG_init(void){
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
 IWDG_SetPrescaler(IWDG_Prescaler_32); //32000/32 = 1 kHz clock
 IWDG_SetReload(999); //1 sek
 IWDG_ReloadCounter();
 IWDG_Enable();
}
/*
void IWDG_Init(u8 prer,u16 rlr)
 {
  IWDG->KR=0X5555;//Ключ для доступа к таймеру
  IWDG->PR=prer; //Обновление предделителя
  IWDG->RLR=rlr; //Загружаем регистр перезагрузки, счет идет вниз от этого значения
  IWDG->KR=0XAAAA;//перезагрузка
  IWDG->KR=0XCCCC;//Запуск в работу
 }
*/
void delay_ms(u16 millisec){

    TIM2_init(millisec);
    while(TIM2_flag < 0x01)continue;
}

void TIM4_init(void){
RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;   //разрешить подачу тактовых импульсов на TIM4
TIM4->CR1 &=~ TIM_CR1_CEN;

  TIM4->PSC = 249;
  TIM4->ARR = 1900;
  TIM4->CR1 &= ~TIM_CR1_CEN;
  TIM4->DIER |= TIM_DIER_UIE;
//  TIM4->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ (TIM4_IRQn);    //разрешаем прерывание

}


void TIM2_init(u16 milliseconds)
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //разрешить подачу тактовых импульсов на TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //обнуляем регистр
   TIM2->CR1=0x0;          //обнуляем регистр

   TIM2->PSC = milliseconds-1;          // предделитель таймера 2
   TIM2->ARR = 7999;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //прямой счёт - 0 (обратный - 1) отсчёт
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //запр.-1; разрешаем событие по перепол.таймера -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //запрещаем 0 - когда прграмно не надо менять значение ARR;разрешаем=1 перзагрузку
   TIM2->CR1 |= TIM_CR1_OPM;      // одиночного импульса
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - прерывание по переполнению &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // сбрасываем 0 ;update enable  ARR и прескалер грузятся из предварительного в теневой регистр
   TIM2->CR1 |= TIM_CR1_CEN;       //запускаем таймер2
   NVIC_EnableIRQ (TIM2_IRQn);    //разрешаем прерывание
   TIM2_flag = 0;
}

void TIM2_IRQHandler(void)
{


   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания
   }
 TIM2_flag = 1;
// TIM2->CR1 &= ~TIM_CR1_CEN;
}

