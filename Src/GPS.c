#include "GPS.h"
#include "RTC.h"
#include "stm32f10x_iwdg.h"

volatile u8 CommandGPS = 0;
u8 arrayGPS[256];
u8 i=0;
volatile u8 statusSyncG = 0;
volatile struct HMS Time;


volatile struct HMS * takeHoursMinsSeconds(u8 * timeArray){
for(i=0; i<6; i++){
if(*(timeArray+i)>0x39 || *(timeArray+i)<0x30)
return 0;
}
Time.H = (timeArray[0] - 0x30) *10 + (timeArray[1] - 0x30) + Time.Z;
if(Time.H > 23) Time.H -= 24;
if(Time.H < 0) Time.H += 24;
Time.M = (timeArray[2] - 0x30) *10 + (timeArray[3] - 0x30);
Time.S = (timeArray[4] - 0x30) *10 + (timeArray[5] - 0x30);
return &Time;
}

u8 * CommandGPSRunner(void){
u8 index;
s8 countSemicolon;
u8 * pointerToTime = arrayGPS;

    CommandGPS = 0;
if(arrayGPS[0]=='G'&&
   arrayGPS[1]=='P'&&
   arrayGPS[2]=='G'&&
   arrayGPS[3]=='L'&&
   arrayGPS[4]=='L'
   ){
  for(index = 5, countSemicolon = 0; index< 255; index++ ){
   if (arrayGPS[index] == ',') countSemicolon++;
   if (countSemicolon == 5){
     if (arrayGPS[index+1] == ',' ){
             statusSyncG = 0; //no datatime
             return pointerToTime;}
     else
      if (index > 20){
      statusSyncG = 2; //FULL datatime
       }
      else
      statusSyncG = 1; //HALF datatime without PPS

      pointerToTime = &arrayGPS[index+1];
      takeHoursMinsSeconds(pointerToTime);

      if(statusSyncG == 1){

               SetTime(Time.H, Time.M, Time.S);
                 CalculateTime();
                 SetDigit4(s_TimeStructVar.MinLow);
                 SetDigit3(s_TimeStructVar.MinHigh);
                 SetDigit2(s_TimeStructVar.HourLow);
                 SetDigit1(s_TimeStructVar.HourHigh);
      }

      return pointerToTime;
    }
   }
  }

return pointerToTime;
}

