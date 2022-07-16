#ifndef _digits_h
#define _digits_h
#define addr(y) (*((volatile unsigned long *) y ))
//---------BIT BAND IMPLIMENTATION---------------
#define PA0_I  addr(0x42210100)
#define PA1_O  addr(0x42210184)
#define PA2_O  addr(0x42210188)
#define PA3_O  addr(0x4221018c)
#define PA4_O  addr(0x42210190)
#define PA5_O  addr(0x42210194)
#define PA6_O  addr(0x42210198)
#define PA7_O  addr(0x4221019c)
#define PA8_O  addr(0x422101a0)
#define PA9_O  addr(0x422101a4)
#define PA10_O addr(0x422101a8)
#define PA11_O addr(0x422101ac)
#define PA12_O addr(0x422101b0)
#define PA13_O addr(0x422101b4)
#define PA14_O addr(0x422101b8)
#define PA15_O addr(0x422101bc)
#define PB0_O  addr(0x42218180)
#define PB1_O  addr(0x42218184)
#define PB2_O  addr(0x42218188)
#define PB3_I  addr(0x4221810c)
#define PB4_O  addr(0x42218190)
#define PB5_O  addr(0x42218194)
#define PB6_O  addr(0x42218198)
#define PB7_O  addr(0x4221819c)
#define PB8_O  addr(0x422181a0)
#define PB9_O  addr(0x422181a4)
#define PB10_O addr(0x422181a8)
#define PB11_O addr(0x422181ac)
#define PB12_O addr(0x422181b0)
#define PB13_O addr(0x422181b4)
#define PB14_O addr(0x422181b8)
#define PB15_O addr(0x422181bc)

//-----------------------------------------
#define ON_A1  PB1_O = 1
#define OFF_A1 PB1_O = 0
#define ON_B1  PB0_O = 1
#define OFF_B1 PB0_O = 0
#define ON_C1  PA7_O = 1
#define OFF_C1 PA7_O = 0
#define ON_D1  PA6_O = 1
#define OFF_D1 PA6_O = 0
#define ON_E1  PA5_O = 1
#define OFF_E1 PA5_O = 0
#define ON_F1  PA4_O = 1
#define OFF_F1 PA4_O = 0
#define ON_G1  PA3_O = 1
#define OFF_G1 PA3_O = 0

#define ON_A2  GPIOA->ODR |= GPIO_ODR_ODR1
#define OFF_A2 GPIOA->ODR &= ~GPIO_ODR_ODR1
#define ON_B2  GPIOA->ODR |= GPIO_ODR_ODR2
#define OFF_B2 GPIOA->ODR &= ~GPIO_ODR_ODR2
#define ON_C2  GPIOB->ODR |= GPIO_ODR_ODR9
#define OFF_C2 GPIOB->ODR &= ~GPIO_ODR_ODR9
#define ON_D2  GPIOB->ODR |= GPIO_ODR_ODR8
#define OFF_D2 GPIOB->ODR &= ~GPIO_ODR_ODR8
#define ON_E2  GPIOB->ODR |= GPIO_ODR_ODR11
#define OFF_E2 GPIOB->ODR &= ~GPIO_ODR_ODR11
#define ON_F2  GPIOB->ODR |= GPIO_ODR_ODR10
#define OFF_F2 GPIOB->ODR &= ~GPIO_ODR_ODR10
#define ON_G2  GPIOB->ODR |= GPIO_ODR_ODR2
#define OFF_G2 GPIOB->ODR &= ~GPIO_ODR_ODR2
//---------------------------------------------
#define ON_A3  GPIOA->ODR |= GPIO_ODR_ODR8
#define OFF_A3 GPIOA->ODR &= ~GPIO_ODR_ODR8
#define ON_B3  GPIOB->ODR |= GPIO_ODR_ODR15
#define OFF_B3 GPIOB->ODR &= ~GPIO_ODR_ODR15
#define ON_C3  GPIOB->ODR |= GPIO_ODR_ODR14
#define OFF_C3 GPIOB->ODR &= ~GPIO_ODR_ODR14
#define ON_D3  GPIOB->ODR |= GPIO_ODR_ODR13
#define OFF_D3 GPIOB->ODR &= ~GPIO_ODR_ODR13
#define ON_E3  GPIOB->ODR |= GPIO_ODR_ODR12
#define OFF_E3 GPIOB->ODR &= ~GPIO_ODR_ODR12
#define ON_F3  GPIOB->ODR |= GPIO_ODR_ODR7
#define OFF_F3 GPIOB->ODR &= ~GPIO_ODR_ODR7
#define ON_G3  GPIOA->ODR |= GPIO_ODR_ODR14
#define OFF_G3 GPIOA->ODR &= ~GPIO_ODR_ODR14
//---------------------------------------------
//-----------------------------------------
#define ON_A4  PB6_O = 1
#define OFF_A4 PB6_O = 0
#define ON_B4  PB4_O = 1
#define OFF_B4 PB4_O = 0
#define ON_C4  PA15_O = 1
#define OFF_C4 PA15_O = 0
#define ON_D4  PA13_O = 1
#define OFF_D4 PA13_O = 0
#define ON_E4  PA12_O = 1
#define OFF_E4 PA12_O = 0
#define ON_F4  PA11_O = 1
#define OFF_F4 PA11_O = 0
#define ON_G4  PA9_O = 1
#define OFF_G4 PA9_O = 0

void SetDigit1(unsigned char digit);
void SetDigit2(unsigned char digit);
void SetDigit3(unsigned char digit);
void SetDigit4(unsigned char digit);
void TestSegments(void);
void EraseDigits(void);

#endif
