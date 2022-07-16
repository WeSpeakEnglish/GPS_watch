#include "uart.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "GPS.h"



char write_UART1(unsigned char * SMS){
  u32 tmp=0;
     while (SMS[tmp]) // ���� �� ����� ������...
     {
          while (!(USART1->SR & USART_SR_TXE)) {} // ����� ������������ ������.
          USART1->DR=SMS[tmp]; tmp++; // ��������� ����.
     }
return 0;
}

char Init_UART1(void){
    NVIC_InitTypeDef NVIC_InitStruct;

     RCC->APB2ENR|= RCC_APB2ENR_IOPAEN; // ��������� ������������ ����� A.
     RCC->APB2ENR|= RCC_APB2ENR_AFIOEN; // ������������ �������������� ������� GPIO.
     RCC->APB2ENR|= RCC_APB2ENR_USART1EN; // ��������� ������������ USART1.
 //    GPIOA->CRH |= GPIO_CRH_MODE9; // ����� TX PA.9 - �� �����.
   //  GPIOA->CRH &=~GPIO_CRH_CNF9; GPIOA->CRH |=GPIO_CRH_CNF9_1; // �������������� �����.
     USART1->CR1 |=(USART_CR1_RE);// | USART_CR1_TE); // ��������� ������ RX, TX - PA10, PA9.
     // �������� 19.200 kbps.
     USART1->BRR = 8000000/9600; // ����� ����� ������������ ������� USART1.
   //  USART1->BRR|=1; // ������� �����*16 = 0,34*16 = 5 (���).
     USART1->CR1 = USART_CR1_UE | USART_CR1_RE; // ��������� USART1. RECEIVER

  USART_Cmd(USART1, ENABLE);
//  USART_ITConfig(USART1, USART_IT_TXE , ENABLE);
  USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);

  //-----------------------------------
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);


return 0;
}

void USART1_IRQHandler(void)
{
  static int tx_index = 0;
  static int rx_index = 0;
  static char ReceivedSymbol;

  if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) // Transmit the string in a loop
  {
      tx_index++;
  }

  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Received characters modify string
  {
ReceivedSymbol = USART_ReceiveData(USART1);

if (ReceivedSymbol== '$'){
    rx_index = 0;
    CommandGPS = 1;}
else{
   arrayGPS[rx_index] = ReceivedSymbol;
   rx_index++;
   if (rx_index > 254) rx_index = 0;
}



    //if (rx_index >= (sizeof(StringLoop) - 1))

USART1->SR&=~(USART_SR_RXNE); // �������� ����� ����������
  }

}
