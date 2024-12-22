#ifndef PWM_H_
#define PWM_H_

typedef  unsigned char   uint8_t;
 typedef  unsigned long   uint32_t;
  typedef  unsigned short   uint16_t;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void pwm_init(void);
void pwm_setDutycycle(uint8_t duty_cycle);
void _delay_ms(uint32_t y);
#endif
