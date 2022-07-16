#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED
#include "stm32f10x.h"

extern volatile u8 CommandGPS;
extern volatile u8 statusSyncG;
extern u8 arrayGPS[256];

struct HMS{
signed char H; // hours
signed char M; // minutes
signed char S; // seconds
signed char Z; // zone
};
extern volatile struct HMS Time;


volatile struct HMS * takeHoursMinsSeconds(u8 * timeArray);
u8 * CommandGPSRunner(void);

#endif /* GPS_H_INCLUDED */
