#ifndef DHT11_H
#define DHT11_H

#include "../Game/tm4c123gh6pm.h"
typedef  unsigned char   uint8_t;
 typedef  unsigned long   uint32_t;
  typedef  unsigned short   uint16_t;




// Define GPIO Port E base and offset values
#define GPIO_PORT_E_BASE 0x40024000
#define GPIO_DATA_OFFSET 0x3FC
#define GPIO_DIR_OFFSET  0x400

// GPIO Data and Direction register macros
#define GPIOE_DATA  (*((volatile uint32_t *)(GPIO_PORT_E_BASE + GPIO_DATA_OFFSET)))
#define GPIOE_DIR   (*((volatile uint32_t *)(GPIO_PORT_E_BASE + GPIO_DIR_OFFSET)))

// Function prototype for Delay_ms
void Delay_ms(uint32_t delay); // Millisecond delay function to be implemented externally

// Function prototype for DHT11 sensor reading
void readDHT11(uint8_t* humidity, uint8_t* temperature);

#endif // DHT11_H

