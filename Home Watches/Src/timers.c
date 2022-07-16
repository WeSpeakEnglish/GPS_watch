#include "timers.h"
#include "adc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_pwr.h"
#include "RTC.h"
#include "digits.h"
//////////////////////////////////////////////
u16 Hum;
u16 Temp;
u8 Crc;

float CalculatedHum;
float CalculatedTemp;
u16 OutsideCounter = 0;
enum{TEMP=1,HUM};
//////////////////////////////////////////////////


void TIM2_init(void)
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //разрешить подачу тактовых импульсов на TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //обнуляем регистр
   TIM2->CR1=0x0;          //обнуляем регистр

   TIM2->PSC = 99;          // предделитель таймера 2
   TIM2->ARR = 99;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //прямой счёт - 0 (обратный - 1) отсчёт
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //запр.-1; разрешаем событие по перепол.таймера -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //запрещаем 0 - когда прграмно не надо менять значение ARR;разрешаем=1 перзагрузку
   TIM2->CR1 &= ~TIM_CR1_OPM;      //Запрещаем работу в режиме одиночного импульса
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - прерывание по переполнению &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // сбрасываем 0 ;update enable  ARR и прескалер грузятся из предварительного в теневой регистр
   TIM2->CR1 |= TIM_CR1_CEN;       //запускаем таймер2
    NVIC_EnableIRQ (TIM2_IRQn);    //разрешаем прерывание

}

void TIM3_init(void) // make delays
{
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //подать тактирование на TIM3                           /
TIM3->PSC     = 8-1;                  //настроить делитель для формирования
TIM3->ARR     = 1667;                 //1000 мкс если 8 Мгц
TIM3->CR1     = TIM_CR1_CEN;
}


void TIM2_IRQHandler(void)
{

  u8 RetVal;
  u32 CorrTimeCounter;
  u32 CorrTimeCounter1;

   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания
   }

  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  if(!(OutsideCounter%128)){
   RetVal = ADC_array_check();
   if(RetVal){

     CorrTimeCounter = WatchCounter%86400;//RTC_GetCounter();
     CorrTimeCounter1 = CorrTimeCounter;

    switch(RetVal){
        case 1: CorrTimeCounter1 += 3600;
                break;
        case 2: if(CorrTimeCounter1 >= 3600 )CorrTimeCounter1 -=3600;
                else CorrTimeCounter1 += 23*3600;
                break;
        case 3: if(CorrTimeCounter1%3600 < 60*59 )CorrTimeCounter1 += 60;
                else CorrTimeCounter1 -= 60*59;
                break;
        case 4: if(CorrTimeCounter1 >= 60 && (CorrTimeCounter1%3600) >=60 )CorrTimeCounter1 -= 60;
                else CorrTimeCounter1 += 59*60;
    }


    if(RetVal > 2) CorrTimeCounter1 = CorrTimeCounter1 - CorrTimeCounter1%60;// zeroe seconds

    if((CorrTimeCounter1 != CorrTimeCounter) || (CorrTimeCounter1 != CorrTimeCounter1%86400 )){
  PWR_BackupAccessCmd(ENABLE);
  RTC_WaitForLastTask();
  CorrTimeCounter = CorrTimeCounter1%86400;
  RTC_SetCounter(CorrTimeCounter);
  WatchCounter = CorrTimeCounter;
  RTC_WaitForLastTask();
  PWR_BackupAccessCmd(DISABLE);
    }
    CalculateTime();
    SetDigit4(s_TimeStructVar.MinLow);
    SetDigit3(s_TimeStructVar.MinHigh);
    SetDigit2(s_TimeStructVar.HourLow);
    SetDigit1(s_TimeStructVar.HourHigh);
   }
  }

  OutsideCounter++;
}

