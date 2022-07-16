#include "flash.h"
#include "stm32f10x_flash.h"
#include "timers.h"


void FLASH_WriteInts(uint32_t address , uint16_t *p , uint16_t Ints_Num)
 {
 	uint32_t HalfWord;


  FLASH->CR |=  FLASH_CR_PER;                    // Page Erase Enabled
  FLASH->AR  =  address;                            // Page Address
  FLASH->CR |=  FLASH_CR_STRT;                    // Start Erase
    asm("nop");
    asm("nop");
  while (FLASH->SR & FLASH_SR_BSY) {
    IWDG->KR = 0xAAAA;                          // Reload IWDG
  }

  FLASH->CR &= ~FLASH_CR_PER;                      // Page Erase Disabled

 // delay_ms(3);
 	while(Ints_Num --)
 	{
 		HalfWord=*(p++);
 		FLASH_ProgramHalfWord(address, HalfWord);
 		address += 2;
 	}
 	FLASH_Lock();
 }

void FLASH_ReadInts(uint32_t address , uint16_t *p , uint16_t Ints_Num)
 {
   while(Ints_Num--)
   {
    *(p++)=*((uint16_t*)address);
     address+=2;
   }
 }

void SetFlashVar(int16_t Tm){
 //FLASH_WriteInts(ADDR_TMIN, (uint16_t *)&Tm, 2);

 ProgramPage (ADDR_TMIN, 2, (u8 *)&Tm);

 return;
}
//void SetTmax(int16_t Tmax){
// FLASH_WriteInts(ADDR_TMAX, (uint16_t *)&Tmax, 1);
// return;
//}
int16_t GetZone(void){
return *((int16_t*)ADDR_TMIN);
}
int16_t GetTmax(void){
return *((int16_t*)ADDR_TMIN + 1);
}

int ProgramPage (unsigned long address, unsigned long sz, unsigned char *buf) {
 FLASH_Unlock();

  sz = (sz + 1) & ~1;                           // Adjust size for Half Words

FLASH->CR |=  FLASH_CR_PER;                    // Page Erase Enabled
  FLASH->AR  =  address;                            // Page Address
  FLASH->CR |=  FLASH_CR_STRT;                    // Start Erase
    asm("nop");
    asm("nop");
  while (FLASH->SR & FLASH_SR_BSY) {
    IWDG->KR = 0xAAAA;                          // Reload IWDG
  }

  FLASH->CR &= ~FLASH_CR_PER;                      // Page Erase Disabled

  while (sz) {

    FLASH->CR |=  FLASH_CR_PG;                     // Programming Enabled

    *(__IO uint16_t*)address = *((unsigned short *)buf);        // Program Half Word
    while (FLASH->SR & FLASH_SR_BSY);

    FLASH->CR &= ~FLASH_CR_PG;                     // Programming Disabled

    // Check for Errors
    if (FLASH->SR & (FLASH_SR_PGERR | FLASH_SR_WRPRTERR)) {
      FLASH->SR |= FLASH_SR_PGERR | FLASH_SR_WRPRTERR;
      return (1);                               // Failed
    }

    // Go to next Half Word
    address += 2;
    buf += 2;
    sz  -= 2;

  }
 FLASH_Lock();
  return (0);                                   // Done
}
