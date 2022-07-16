#include "user_interface.h"
#include "digits.h"
#include "timers.h"
#include "GPS.h"
#include "flash.h"
#define PIN_ZONE (*((volatile unsigned long *) 0x42220134))



void CheckZone(void){
register u8 i;
u8 goChange = 0;


ViewZone();
delay_ms(2000);

 while(1){
   if (PIN_ZONE == 0){


  if(i>1)
      Time.Z = Time.Z + 1;

    if (Time.Z == 13){
            Time.Z = -12;
     }

     ViewZone();
     goChange =1;
    }
    else
        {
    if(i > 0)
    if(goChange )SetFlashVar((int16_t) Time.Z);

    break;
        }
  i++;
    delay_ms(2000);

 }
delay_ms(2000);
 return;
}

void ViewZone(void){
    SetDigit1(10);
    SetDigit2(10);
    SetDigit3(10);
    SetDigit4(10);
    ON_D1;ON_E1;ON_F1;

    if (Time.Z < 0) {
            ON_G2; // disp "-"
            SetDigit3((u8)(-Time.Z)/10);
            SetDigit4((u8)(-Time.Z)%10);
     }
    else{
            OFF_G2; // disp "-"
            SetDigit3((Time.Z)/10);
            SetDigit4((Time.Z)%10);
     }
}
