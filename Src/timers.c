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
  IWDG->KR=0X5555;//���� ��� ������� � �������
  IWDG->PR=prer; //���������� ������������
  IWDG->RLR=rlr; //��������� ������� ������������, ���� ���� ���� �� ����� ��������
  IWDG->KR=0XAAAA;//������������
  IWDG->KR=0XCCCC;//������ � ������
 }
*/
void delay_ms(u16 millisec){

    TIM2_init(millisec);
    while(TIM2_flag < 0x01)continue;
}

void TIM4_init(void){
RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;   //��������� ������ �������� ��������� �� TIM4
TIM4->CR1 &=~ TIM_CR1_CEN;

  TIM4->PSC = 249;
  TIM4->ARR = 1900;
  TIM4->CR1 &= ~TIM_CR1_CEN;
  TIM4->DIER |= TIM_DIER_UIE;
//  TIM4->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ (TIM4_IRQn);    //��������� ����������

}


void TIM2_init(u16 milliseconds)
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //��������� ������ �������� ��������� �� TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //�������� �������
   TIM2->CR1=0x0;          //�������� �������

   TIM2->PSC = milliseconds-1;          // ������������ ������� 2
   TIM2->ARR = 7999;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //������ ���� - 0 (�������� - 1) ������
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //����.-1; ��������� ������� �� �������.������� -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //��������� 0 - ����� �������� �� ���� ������ �������� ARR;���������=1 �����������
   TIM2->CR1 |= TIM_CR1_OPM;      // ���������� ��������
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - ���������� �� ������������ &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // ���������� 0 ;update enable  ARR � ��������� �������� �� ���������������� � ������� �������
   TIM2->CR1 |= TIM_CR1_CEN;       //��������� ������2
   NVIC_EnableIRQ (TIM2_IRQn);    //��������� ����������
   TIM2_flag = 0;
}

void TIM2_IRQHandler(void)
{


   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // ������� ���� ����������
   }
 TIM2_flag = 1;
// TIM2->CR1 &= ~TIM_CR1_CEN;
}

