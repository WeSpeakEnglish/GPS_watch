#include "RTC.h"
#include "misc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_pwr.h"
#include "digits.h"
//share
  u32 WatchCounter = 0;
/* Private variables--------------------------------------------------------- */
uint8_t ClockSource;
//uint8_t *MonthsNames[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug",
//"Sep","Oct","Nov","Dec"};
const uint8_t CalibrationPpm[128]={0,1,2,3,4,5,6,7,8,9,10,10,11,12,13,14,15,16,17,\
                         18,19,20,21,22,23,24,25,26,27,28,29,30,31,31,32,33,34,\
                         35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,51,\
                         52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,\
                         70,71,72,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,\
                         87,88,89,90,91,92,93,93,94,95,96,97,98,99,100,101,102,\
                         103,104,105,106,107,108,109,110,111,112,113,113,114,\
                         115,116,117,118,119,120,121};
/*Structure variable declaration for system time, system date,
alarm time, alarm date */
struct Time_s s_TimeStructVar;

u8 TamperEvent = 0;
u16 SummerTimeCorrect = 0x0000;
u8 BatteryRemoved = 0;
/** @addtogroup RTC
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  COnfiguration of RTC Registers, Selection and Enabling of
  *   RTC clock
  * @param  None
  * @retval : None
  */
 // RTC_InitTypeDef   RTC_InitStructure;
//  RTC_AlarmTypeDef  RTC_AlarmStructure;
//  RTC_TimeTypeDef   RTC_TimeStructure;


void RTC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

        /* Configure one bit for preemption priority */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

        /* Enable the RTC Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

        PWR_BackupAccessCmd(ENABLE);
        RCC_LSEConfig(RCC_LSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
        RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
        RTC_WaitForLastTask();
}



void SetTime(uint8_t Hour,uint8_t Minute,uint8_t Seconds)
{
  uint32_t CounterValue;

  CounterValue=((Hour * 3600)+ (Minute * 60)+Seconds);

  RTC_WaitForLastTask();
  RTC_SetCounter(CounterValue);
  RTC_WaitForLastTask();
}







/**
  * @brief  RTC Application runs in while loop
  * @param  None
  * @retval : None
  */
void RTC_Application(void)
{

//  CalculateTime();


  if(TamperEvent == 1) /* Tamper event is detected */
  {
  //  TamperNumber = TamperNumber + 1;
 //   BKP_WriteBackupRegister(BKP_DR5,TamperNumber);
 //   BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
 //   BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
 //   BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
 //   BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
 //   BKP_WriteBackupRegister(BKP_DR9,s_AlarmDateStructVar.Day);
 //   BKP_WriteBackupRegister(BKP_DR8,s_AlarmDateStructVar.Month);
 //   BKP_WriteBackupRegister(BKP_DR10,s_AlarmDateStructVar.Year);
//    BKP_WriteBackupRegister(BKP_DR6,ClockSource);
//    BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
 //   ReturnValue=EE_WriteVariable(TamperNumber);

/*
    ReturnValue=EE_WriteVariable(s_DateStructVar.Day);
    ReturnValue=EE_WriteVariable(s_DateStructVar.Month);
    ReturnValue=EE_WriteVariable((s_DateStructVar.Year)/100);
    ReturnValue=EE_WriteVariable((s_DateStructVar.Year)%100);
    ReturnValue=EE_WriteVariable((s_TimeStructVar.HourHigh*10)+\
                    s_TimeStructVar.HourLow);
    ReturnValue=EE_WriteVariable((s_TimeStructVar.MinHigh*10)+\
                    s_TimeStructVar.MinLow);
    ReturnValue=EE_WriteVariable((s_TimeStructVar.SecHigh*10)+\
                    s_TimeStructVar.SecLow);
    while(!(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)))
    {
    }

    TamperEvent=0;
    */
    BKP_TamperPinCmd(ENABLE);
  }

  if(BatteryRemoved != 0) /* Battery tamper is detected */
  {
    BKP_TamperPinCmd(ENABLE);
  }
}



/**
  * @brief  This function is executed after wakeup from STOP mode
  * @param  None
  * @retval : None
  */
void ReturnFromStopMode(void)
{
  /* RCC Configuration has to be called after waking from STOP Mode*/
  //RCC_Configuration();
  /*Enables the clock to Backup and power interface peripherals after Wake Up */
 // RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);
  /* Enable access to Backup Domain */
 // PWR_BackupAccessCmd(ENABLE);

}



/**
  * @brief Determines the weekday
  * @param Year,Month and Day
  * @retval :Returns the CurrentWeekDay Number 0- Sunday 6- Saturday
  */
uint16_t WeekDay(uint16_t CurrentYear,uint8_t CurrentMonth,uint8_t CurrentDay)
{
  uint16_t Temp1,Temp2,Temp3,Temp4,CurrentWeekDay;

  if(CurrentMonth < 3)
  {
    CurrentMonth=CurrentMonth + 12;
    CurrentYear=CurrentYear-1;
  }

  Temp1=(6*(CurrentMonth + 1))/10;
  Temp2=CurrentYear/4;
  Temp3=CurrentYear/100;
  Temp4=CurrentYear/400;
  CurrentWeekDay=CurrentDay + (2 * CurrentMonth) + Temp1 \
     + CurrentYear + Temp2 - Temp3 + Temp4 +1;
  CurrentWeekDay = CurrentWeekDay % 7;

  return(CurrentWeekDay);
}



/**
  * @brief Displays the Date(DD/MM/YY and DAY ) on LCD
  * @param None
  * @retval :None
  */




/**
  * @brief Displays the Time on LCD
  * @param None
  * @retval :None
  */





/**
  * @brief Calcuate the Time (in hours, minutes and seconds  derived from
  *   COunter value
  * @param None
  * @retval :None
  */
void CalculateTime(void)
{
  uint32_t TimeVar;

  TimeVar=WatchCounter%86400;//RTC_GetCounter();
  //RTC_WaitForLastTask();
 // if(TimeVar > 86399){

    /* Wait until last write operation on RTC registers has finished */
 // PWR_BackupAccessCmd(ENABLE);
 // RTC_WaitForLastTask();
    /* Reset counter value */
 // RTC_SetCounter(TimeVar%86400 );
 // RTC_WaitForLastTask();
 // PWR_BackupAccessCmd(DISABLE);
    /* Wait until last write operation on RTC registers has finished */

 // }


  s_TimeStructVar.HourHigh=(uint8_t)(TimeVar/3600)/10;
  s_TimeStructVar.HourLow=(uint8_t)(TimeVar/3600)%10;
  s_TimeStructVar.MinHigh=(uint8_t)((TimeVar%3600)/60)/10;
  s_TimeStructVar.MinLow=(uint8_t)((TimeVar%3600)/60)%10;
  s_TimeStructVar.SecHigh=(uint8_t)((TimeVar%3600)%60)/10;
  s_TimeStructVar.SecLow=(uint8_t)((TimeVar %3600)%60)%10;
}

/**
  * @brief  Calibration of External crystal oscillator manually
  * @param  None
  * @retval : None
  */


/**
  * @brief  Configures the Tamper Interrupts
  * @param  None
  * @retval : None
  */
void Tamper_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TAMPER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



/**
  * @brief  Configures RTC Interrupts
  * @param  None
  * @retval : None
  */
void RTC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  EXTI_DeInit();

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the EXTI Line17 Interrupt */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  EXTI_ClearITPendingBit(EXTI_Line16 );
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


 void TAMPER_IRQHandler(void)
{
  BKP_TamperPinCmd(DISABLE);

  TamperEvent = 1;

  BKP_ClearITPendingBit();

  BKP_ClearFlag();

  NVIC_ClearPendingIRQ(TAMPER_IRQn);
}


void RTC_Config(void)
{

   NVIC_InitTypeDef NVIC_InitStructure;

 /* Configure one bit for preemption priority */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

 /* Enable the RTC Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

   PWR_BackupAccessCmd(ENABLE);
   RCC_LSEConfig(RCC_LSE_ON);
   while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
   RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
   RCC_RTCCLKCmd(ENABLE);

   RTC_WaitForSynchro();
 //  RTC_WaitForLastTask();
   RTC_ITConfig(RTC_IT_SEC, ENABLE);
 //  RTC_WaitForLastTask();
 ////
   BKP->RTCCR |= 25;                                                             //калибровка RTC
//   while (!(RTC->CRL & RTC_CRL_RTOFF));                                         //проверить закончены ли изменения регистров RTC
 //  RTC->CRL  |=  RTC_CRL_CNF;                                                   //Разрешить запись в регистры RTC
 //RTC_WaitForLastTask();
   RTC_SetPrescaler(32774); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
   RTC_WaitForLastTask();
   PWR_BackupAccessCmd(DISABLE);
}
/**
  * @brief  This function handles RTC_IRQHandler .
  * @param  None
  * @retval : None
  */
void RTC_IRQHandler(void)
{
  static u8 InCount=1;
  static u8 FlagEntrance = 0;
//  static u32 SecondsIn;


   RTC_ClearITPendingBit(RTC_IT_SEC);
   if(!FlagEntrance){
           FlagEntrance++;
           WatchCounter = RTC_GetCounter();
   }
   else{
    WatchCounter++;
   }

  if((InCount)%2) GPIOB->BSRR |= GPIO_BSRR_BS4;
  else GPIOB->BSRR |= GPIO_BSRR_BR4;
  CalculateTime();
  SetDigit4(s_TimeStructVar.MinLow);
  SetDigit3(s_TimeStructVar.MinHigh);
  SetDigit2(s_TimeStructVar.HourLow);
  SetDigit1(s_TimeStructVar.HourHigh);
  InCount++;
}



