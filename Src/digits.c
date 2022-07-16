#include "digits.h"
#include "stm32f10x_gpio.h"



void SetDigit1(unsigned char digit){

  switch(digit){
    case 0:
    ON_A1;ON_B1;ON_C1;ON_D1;ON_E1;ON_F1;OFF_G1;
    break;
  case 1:
    OFF_A1;ON_B1;ON_C1;OFF_D1;OFF_E1;OFF_F1;OFF_G1;
    break;
  case 2:
    ON_A1;ON_B1;OFF_C1;ON_D1;ON_E1;OFF_F1;ON_G1;
    break;
  case 3:
    ON_A1;ON_B1;ON_C1;ON_D1;OFF_E1;OFF_F1;ON_G1;
    break;
  case 4:
    OFF_A1;ON_B1;ON_C1;OFF_D1;OFF_E1;ON_F1;ON_G1;
    break;
  case 5:
    ON_A1;OFF_B1;ON_C1;ON_D1;OFF_E1;ON_F1;ON_G1;
    break;
  case 6:
    ON_A1;OFF_B1;ON_C1;ON_D1;ON_E1;ON_F1;ON_G1;
    break;
  case 7:
    ON_A1;ON_B1;ON_C1;OFF_D1;OFF_E1;OFF_F1;OFF_G1;
    break;
  case 8:
    ON_A1;ON_B1;ON_C1;ON_D1;ON_E1;ON_F1;ON_G1;
    break;
  case 9:
    ON_A1;ON_B1;ON_C1;ON_D1;OFF_E1;ON_F1;ON_G1;
    break;
  case 10:
    OFF_A1;OFF_B1;OFF_C1;OFF_D1;OFF_E1;OFF_F1;OFF_G1;
    break;
    }

}
void SetDigit2(unsigned char digit){
  switch(digit){
  case 0:
    ON_A2;ON_B2;ON_C2;ON_D2;ON_E2;ON_F2;OFF_G2;
    break;
  case 1:
    OFF_A2;ON_B2;ON_C2;OFF_D2;OFF_E2;OFF_F2;OFF_G2;
    break;
  case 2:
    ON_A2;ON_B2;OFF_C2;ON_D2;ON_E2;OFF_F2;ON_G2;
    break;
  case 3:
    ON_A2;ON_B2;ON_C2;ON_D2;OFF_E2;OFF_F2;ON_G2;
    break;
  case 4:
    OFF_A2;ON_B2;ON_C2;OFF_D2;OFF_E2;ON_F2;ON_G2;
    break;
  case 5:
    ON_A2;OFF_B2;ON_C2;ON_D2;OFF_E2;ON_F2;ON_G2;
    break;
  case 6:
    ON_A2;OFF_B2;ON_C2;ON_D2;ON_E2;ON_F2;ON_G2;
    break;
  case 7:
    ON_A2;ON_B2;ON_C2;OFF_D2;OFF_E2;OFF_F2;OFF_G2;
    break;
  case 8:
    ON_A2;ON_B2;ON_C2;ON_D2;ON_E2;ON_F2;ON_G2;
    break;
  case 9:
    ON_A2;ON_B2;ON_C2;ON_D2;OFF_E2;ON_F2;ON_G2;
    break;
  case 10:
    OFF_A2;OFF_B2;OFF_C2;OFF_D2;OFF_E2;OFF_F2;OFF_G2;
    break;
  }

}
void SetDigit3(unsigned char digit){
  switch(digit){
  case 0:
    ON_A3;ON_B3;ON_C3;ON_D3;ON_E3;ON_F3;OFF_G3;
    break;
  case 1:
    OFF_A3;ON_B3;ON_C3;OFF_D3;OFF_E3;OFF_F3;OFF_G3;
    break;
  case 2:
    ON_A3;ON_B3;OFF_C3;ON_D3;ON_E3;OFF_F3;ON_G3;
    break;
  case 3:
    ON_A3;ON_B3;ON_C3;ON_D3;OFF_E3;OFF_F3;ON_G3;
    break;
  case 4:
    OFF_A3;ON_B3;ON_C3;OFF_D3;OFF_E3;ON_F3;ON_G3;
    break;
  case 5:
    ON_A3;OFF_B3;ON_C3;ON_D3;OFF_E3;ON_F3;ON_G3;
    break;
  case 6:
    ON_A3;OFF_B3;ON_C3;ON_D3;ON_E3;ON_F3;ON_G3;
    break;
  case 7:
    ON_A3;ON_B3;ON_C3;OFF_D3;OFF_E3;OFF_F3;OFF_G3;
    break;
  case 8:
    ON_A3;ON_B3;ON_C3;ON_D3;ON_E3;ON_F3;ON_G3;
    break;
  case 9:
    ON_A3;ON_B3;ON_C3;ON_D3;OFF_E3;ON_F3;ON_G3;
    break;
  case 10:
    OFF_A3;OFF_B3;OFF_C3;OFF_D3;OFF_E3;OFF_F3;OFF_G3;
    break;
  }
}
void SetDigit4(unsigned char digit){
  switch(digit){
  case 0:
    ON_A4;ON_B4;ON_C4;ON_D4;ON_E4;ON_F4;OFF_G4;
    break;
  case 1:
    OFF_A4;ON_B4;ON_C4;OFF_D4;OFF_E4;OFF_F4;OFF_G4;
    break;
  case 2:
    ON_A4;ON_B4;OFF_C4;ON_D4;ON_E4;OFF_F4;ON_G4;
    break;
  case 3:
    ON_A4;ON_B4;ON_C4;ON_D4;OFF_E4;OFF_F4;ON_G4;
    break;
  case 4:
    OFF_A4;ON_B4;ON_C4;OFF_D4;OFF_E4;ON_F4;ON_G4;
    break;
  case 5:
    ON_A4;OFF_B4;ON_C4;ON_D4;OFF_E4;ON_F4;ON_G4;
    break;
  case 6:
    ON_A4;OFF_B4;ON_C4;ON_D4;ON_E4;ON_F4;ON_G4;
    break;
  case 7:
    ON_A4;ON_B4;ON_C4;OFF_D4;OFF_E4;OFF_F4;OFF_G4;
    break;
  case 8:
    ON_A4;ON_B4;ON_C4;ON_D4;ON_E4;ON_F4;ON_G4;
    break;
  case 9:
    ON_A4;ON_B4;ON_C4;ON_D4;OFF_E4;ON_F4;ON_G4;
    break;
  case 10:
    OFF_A4;OFF_B4;OFF_C4;OFF_D4;OFF_E4;OFF_F4;OFF_G4;
    break;

  }

}

void EraseDigits(void){
    SetDigit1(10);
    SetDigit2(10);
    SetDigit3(10);
    SetDigit4(10);
    PB5_O = 0;
}

void TestSegments(void){
ON_A1;
delay_ms(1000);
ON_B1;
delay_ms(1000);
ON_C1;
delay_ms(1000);
ON_D1;
delay_ms(1000);

ON_E1;
delay_ms(1000);

ON_F1;
delay_ms(1000);
ON_G1;
delay_ms(1000);
ON_A2;
delay_ms(1000);
ON_B2;
delay_ms(1000);
ON_C2;
delay_ms(1000);
ON_D2;
delay_ms(1000);
ON_E2;
delay_ms(1000);
ON_F2;
delay_ms(1000);
ON_G2;
delay_ms(1000);
ON_A3;
delay_ms(1000);
ON_B3;
delay_ms(1000);
ON_C3;
delay_ms(1000);
ON_D3;
delay_ms(1000);
ON_E3;
delay_ms(1000);
ON_F3;
delay_ms(1000);
ON_G3;
delay_ms(1000);
ON_A4;
delay_ms(1000);
ON_B4;
delay_ms(1000);
ON_C4;
delay_ms(1000);
ON_D4;
delay_ms(1000);
ON_E4;
delay_ms(1000);
ON_F4;
delay_ms(1000);
ON_G4;
delay_ms(1000);
PB5_O = 1;
delay_ms(1000);
}
