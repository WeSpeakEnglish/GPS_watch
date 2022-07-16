#ifndef FLASH_H_INCLUDED
#define FLASH_H_INCLUDED
#include "stm32f10x.h"

/*
struct{
int16_t Tmin;
int16_t Tmax;
}tempLimits;
*/
#define ADDR_TMIN ((uint32_t)0x08007000)
//#define ADDR_TMAX 0x800C008

void FLASH_WriteInts(uint32_t addr , uint16_t *p , uint16_t Ints_Num);
void FLASH_ReadInts(uint32_t addr , uint16_t *p , uint16_t Ints_Num);
void SetSetFlashVar(int16_t Tmin);
//void SetTmax(int16_t Tmax);
int16_t GetZone(void);
int16_t GetTmax(void);
int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf);

#endif /* FLASH_H_INCLUDED */
