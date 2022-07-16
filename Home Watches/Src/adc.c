#include "adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "timers.h"


GPIO_InitTypeDef GPIO_InitStructure;
ADC_InitTypeDef ADC_InitStructure;

NVIC_InitTypeDef                NVIC_InitStructure;
u16                             ADC_ConvertedValue[8];


void ConfigADC(void){
          GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 ;            // that's ADC1 (PA1 on STM32)
        GPIO_Init(GPIOA, &GPIO_InitStructure);

//clock for ADC (max 14MHz --> 72/6=12MHz)
        RCC_ADCCLKConfig (RCC_PCLK2_Div6);
// enable ADC system clock
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

// define ADC config
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;      // we work in continuous sampling mode
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 1;

        ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 1,ADC_SampleTime_239Cycles5); // define regular conversion config
        ADC_Init ( ADC1, &ADC_InitStructure);   //set config of ADC1

// enable ADC
        ADC_Cmd (ADC1,ENABLE);  //enable ADC1

//      ADC calibration (optional, but recommended at power on)
        ADC_ResetCalibration(ADC1);     // Reset previous calibration
        while(ADC_GetResetCalibrationStatus(ADC1));
        ADC_StartCalibration(ADC1);     // Start new calibration (ADC must be off at that time)
        while(ADC_GetCalibrationStatus(ADC1));

// start conversion
        ADC_Cmd (ADC1,ENABLE);  //enable ADC1
        ADC_SoftwareStartConvCmd(ADC1, ENABLE); // start conversion (will be endless as we are in continuous mode)
 ADC1->CR1 = ADC_CR1_EOCIE; // Enable interrupt form End Of Conversion
   NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
  NVIC_EnableIRQ(ADC1_IRQn); // Enable interrupt form ACD1 peripheral


}

u16 readADC1(u8 channel)
{
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}

void LookADC(void){
static u8 pValue;
static s16 OldValue = 4096;
pValue = pValue%8;
ADC_ConvertedValue[pValue] = ADC_GetConversionValue(ADC1);
if((s16)ADC_ConvertedValue[pValue] - OldValue > 250)OutsideCounter = 117;
OldValue = (s16)ADC_ConvertedValue[pValue];
pValue++;
  }

u8 ADC_array_check(void){
u16 max=0, min=4096, index;
for(index = 0; index < 8; index++){
 if(ADC_ConvertedValue[index] > max) max = ADC_ConvertedValue[index];
 if(ADC_ConvertedValue[index] < min) min = ADC_ConvertedValue[index];
}

if((min > 528) && (max<646))
   return 1;
if((min > 789) && (max<965))
   return 2;
if((min > 679) && (max<830))
   return 3;
if((min > 1846) && (max<2257))
   return 4;

return 0;
}

void ADC1_IRQHandler(void)
{

  ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
  LookADC();
}
