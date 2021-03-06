#ifndef _rtc_h
#define _rtc_h
#include "stm32f10x.h"


/* Exported types ------------------------------------------------------------*/
/* Time Structure definition */
struct Time_s
{
  uint8_t SecLow;
  uint8_t SecHigh;
  uint8_t MinLow;
  uint8_t MinHigh;
  uint8_t HourLow;
  uint8_t HourHigh;
};
extern struct Time_s s_TimeStructVar;

/* Alarm Structure definition */
struct AlarmTime_s
{
  uint8_t SecLow;
  uint8_t SecHigh;
  uint8_t MinLow;
  uint8_t MinHigh;
  uint8_t HourLow;
  uint8_t HourHigh;
};
extern struct AlarmTime_s s_AlarmStructVar;

/* Date Structure definition */
struct Date_s
{
  uint8_t Month;
  uint8_t Day;
  uint16_t Year;
};
extern struct Date_s s_DateStructVar;

/* Alarm Date Structure definition */
struct AlarmDate_s
{
  uint8_t Month;
  uint8_t Day;
  uint16_t Year;
};
extern struct AlarmDate_s s_AlarmDateStructVar;

/* Exported constants --------------------------------------------------------*/
#define BATTERY_REMOVED 98
#define BATTERY_RESTORED 99
#define SECONDS_IN_DAY 86399
#define CONFIGURATION_DONE 0xAAAA
#define CONFIGURATION_RESET 0x0000
#define OCTOBER_FLAG_SET 0x4000
#define MARCH_FLAG_SET 0x8000
#define DEFAULT_DAY 15
#define DEFAULT_MONTH 5
#define DEFAULT_YEAR 2008
#define DEFAULT_HOURS 9
#define DEFAULT_MINUTES 24
#define DEFAULT_SECONDS 0
#define LEAP 1
#define NOT_LEAP 0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CalendarInit(void);
void RTC_Configuration(void);
void SetTime(uint8_t,uint8_t,uint8_t);
void SetAlarm(uint8_t,uint8_t,uint8_t);
void SetDate(uint8_t,uint8_t,uint16_t);
void RTC_Application(void);
void DateUpdate(void);
uint16_t WeekDay(uint16_t,uint8_t,uint8_t);
uint8_t CheckLeap(uint16_t);
void CalculateTime(void);
void DisplayDate(void);
void DisplayTime(void);
void DisplayAlarm(void);
void RTC_NVIC_Configuration(void);
void GPIO_Configuration(void);
void DelayLowPower(__IO uint32_t nCount);
void SysTickConfig(void);
void SummerTimeCorrection(void);
void Tamper_NVIC_Configuration(void);
void ManualClockCalibration(void);
void AutoClockCalibration(void);
void ReturnFromStopMode(void);
void RTC_Config(void);
extern u32 WatchCounter;
//extern u8 statusSync;
#endif
