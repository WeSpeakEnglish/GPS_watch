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

void CalendarInit(void);
void SetTime(uint8_t,uint8_t,uint8_t);
void CalculateTime(void);
void RTC_Config(void);
extern u32 WatchCounter;
#endif
