#ifndef __POT_H__
#define __POT_H__

typedef  unsigned char   uint8_t;
 typedef  unsigned short   uint16_t;
#include "ADC.h"

void Pot_Init(uint8_t channel, uint16_t mode);
uint16_t Pot_Read(void);

#endif // __POT_H__
