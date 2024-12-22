#ifndef __temp_H_
#define __temp_H_
#include "../Game/tm4c123gh6pm.h"
typedef  unsigned char   uint8_t;
 typedef  unsigned long   uint32_t;
  typedef  unsigned short   uint16_t;



void ADC0_Init1(void);

uint16_t Tempsensor_read(void);

#endif // __temp_H__

