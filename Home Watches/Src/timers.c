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
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //��������� ������ �������� ��������� �� TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //�������� �������
   TIM2->CR1=0x0;          //�������� �������

   TIM2->PSC = 99;          // ������������ ������� 2
   TIM2->ARR = 99;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //������ ���� - 0 (�������� - 1) ������
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //����.-1; ��������� ������� �� �������.������� -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //��������� 0 - ����� �������� �� ���� ������ �������� ARR;���������=1 �����������
   TIM2->CR1 &= ~TIM_CR1_OPM;      //��������� ������ � ������ ���������� ��������
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - ���������� �� ������������ &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // ���������� 0 ;update enable  ARR � ��������� �������� �� ���������������� � ������� �������
   TIM2->CR1 |= TIM_CR1_CEN;       //��������� ������2
    NVIC_EnableIRQ (TIM2_IRQn);    //��������� ����������

}

void TIM3_init(void) // make delays
{
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //������ ������������ �� TIM3                           /
TIM3->PSC     = 8-1;                  //��������� �������� ��� ������������
TIM3->ARR     = 1667;                 //1000 ��� ���� 8 ���
TIM3->CR1     = TIM_CR1_CEN;
}


void TIM2_IRQHandler(void)
{

  u8 RetVal;
  u32 CorrTimeCounter;
  u32 CorrTimeCounter1;

   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // ������� ���� ����������
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

