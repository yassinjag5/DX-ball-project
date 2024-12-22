#ifndef DIO_H_
#define DIO_H_

#include "../Game/tm4c123gh6pm.h"
typedef  unsigned char   uint8_t;
 typedef  unsigned long   uint32_t;
  typedef  unsigned short   uint16_t;


typedef enum
{
	STD_LOW , STD_HIGH
}Dio_LevelType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
uint8_t DIO_ReadPort(uint8_t port_index, uint8_t pins_mask);
void DIO_WritePort(uint8_t port_index, uint8_t pins_mask,Dio_LevelType pins_level);
void DIO_FlipPort(uint8_t port_index, uint8_t pins_maskl);
#endif