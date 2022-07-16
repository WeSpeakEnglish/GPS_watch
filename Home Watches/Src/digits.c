#include "digits.h"
#include "stm32f10x_gpio.h"


#define ON_A1 GPIOB->ODR |= GPIO_ODR_ODR8
#define OFF_A1 GPIOB->ODR &= ~GPIO_ODR_ODR8
#define ON_B1 GPIOB->ODR |= GPIO_ODR_ODR9
#define OFF_B1 GPIOB->ODR &= ~GPIO_ODR_ODR9
#define ON_C1 GPIOB->ODR |= GPIO_ODR_ODR12
#define OFF_C1 GPIOB->ODR &= ~GPIO_ODR_ODR12
#define ON_D1 GPIOB->ODR |= GPIO_ODR_ODR13
#define OFF_D1 GPIOB->ODR &= ~GPIO_ODR_ODR13
#define ON_E1 GPIOB->ODR |= GPIO_ODR_ODR14
#define OFF_E1 GPIOB->ODR &= ~GPIO_ODR_ODR14
#define ON_F1 GPIOB->ODR |= GPIO_ODR_ODR15
#define OFF_F1 GPIOB->ODR &= ~GPIO_ODR_ODR15
#define ON_G1 GPIOA->ODR |= GPIO_ODR_ODR4
#define OFF_G1 GPIOA->ODR &= ~GPIO_ODR_ODR4
//---------------------------------------------
#define ON_A2 GPIOA->ODR |= GPIO_ODR_ODR3
#define OFF_A2 GPIOA->ODR &= ~GPIO_ODR_ODR3
#define ON_B2 GPIOA->ODR |= GPIO_ODR_ODR12
#define OFF_B2 GPIOA->ODR &= ~GPIO_ODR_ODR12
#define ON_C2 GPIOA->ODR |= GPIO_ODR_ODR2
#define OFF_C2 GPIOA->ODR &= ~GPIO_ODR_ODR2
#define ON_D2 GPIOB->ODR |= GPIO_ODR_ODR11
#define OFF_D2 GPIOB->ODR &= ~GPIO_ODR_ODR11
#define ON_E2 GPIOA->ODR |= GPIO_ODR_ODR0
#define OFF_E2 GPIOA->ODR &= ~GPIO_ODR_ODR0
#define ON_F2 GPIOB->ODR |= GPIO_ODR_ODR0
#define OFF_F2 GPIOB->ODR &= ~GPIO_ODR_ODR0
#define ON_G2 GPIOB->ODR |= GPIO_ODR_ODR10
#define OFF_G2 GPIOB->ODR &= ~GPIO_ODR_ODR10
//---------------------------------------------
#define ON_A3 GPIOA->ODR |= GPIO_ODR_ODR5
#define OFF_A3 GPIOA->ODR &= ~GPIO_ODR_ODR5
#define ON_B3 GPIOB->ODR |= GPIO_ODR_ODR6
#define OFF_B3 GPIOB->ODR &= ~GPIO_ODR_ODR6
#define ON_C3 GPIOB->ODR |= GPIO_ODR_ODR7
#define OFF_C3 GPIOB->ODR &= ~GPIO_ODR_ODR7
#define ON_D3 GPIOA->ODR |= GPIO_ODR_ODR6
#define OFF_D3 GPIOA->ODR &= ~GPIO_ODR_ODR6
#define ON_E3 GPIOA->ODR |= GPIO_ODR_ODR7
#define OFF_E3 GPIOA->ODR &= ~GPIO_ODR_ODR7
#define ON_F3 GPIOA->ODR |= GPIO_ODR_ODR8
#define OFF_F3 GPIOA->ODR &= ~GPIO_ODR_ODR8
#define ON_G3 GPIOA->ODR |= GPIO_ODR_ODR11
#define OFF_G3 GPIOA->ODR &= ~GPIO_ODR_ODR11
//---------------------------------------------
#define ON_A4 GPIOA->ODR |= GPIO_ODR_ODR15
#define OFF_A4 GPIOA->ODR &= ~GPIO_ODR_ODR15
#define ON_B4 GPIOB->ODR |= GPIO_ODR_ODR5
#define OFF_B4 GPIOB->ODR &= ~GPIO_ODR_ODR5
#define ON_C4 GPIOA->ODR |= GPIO_ODR_ODR10
#define OFF_C4 GPIOA->ODR &= ~GPIO_ODR_ODR10
#define ON_D4 GPIOA->ODR |= GPIO_ODR_ODR9
#define OFF_D4 GPIOA->ODR &= ~GPIO_ODR_ODR9
#define ON_E4 GPIOB->ODR |= GPIO_ODR_ODR1
#define OFF_E4 GPIOB->ODR &= ~GPIO_ODR_ODR1
#define ON_F4 GPIOB->ODR |= GPIO_ODR_ODR3
#define OFF_F4 GPIOB->ODR &= ~GPIO_ODR_ODR3
#define ON_G4 GPIOB->ODR |= GPIO_ODR_ODR2
#define OFF_G4 GPIOB->ODR &= ~GPIO_ODR_ODR2
//------------------------------------------
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
  
  
  }

}