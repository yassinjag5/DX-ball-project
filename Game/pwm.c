#include "pwm.h"
#include "../Game/tm4c123gh6pm.h"

void pwm_init()
{
    // Enable PWM module 1
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;

    // Enable clock for Port F
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Wait for peripherals to be ready
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);

    // Set the system clock to use the PWM divider
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;

    // Set PWM clock divider to divide by 64 (PWMDIV = 0b111 -> divide by 64)
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~SYSCTL_RCC_PWMDIV_M) | SYSCTL_RCC_PWMDIV_64;

    // Set PWM clock frequency
    // System Clock = 80 MHz
    // PWM Clock = System Clock / 64 = 1.25 MHz
    // Load Value = PWM Clock / Desired Frequency
    PWM1_3_CTL_R = 0x00000000;              // Disable generator 3 during configuration
    PWM1_3_GENA_R = 0x0000008C;             // Drive PWM High at reload, low on match
    PWM1_3_LOAD_R = 1250 - 1;               // 1 kHz PWM frequency (1 ms period)
    PWM1_3_CMPA_R = 1248;                   // 0% duty cycle initially
    PWM1_3_CTL_R |= 0x01;                   // Enable generator 3

    // Configure PF2 for PWM output
    GPIO_PORTF_AFSEL_R |= 0x04;             // Enable alternate function on PF2
    GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFF0FF) | GPIO_PCTL_PF2_M1PWM6;
    GPIO_PORTF_DIR_R |= 0x04;               // Set PF2 as output
    GPIO_PORTF_DEN_R |= 0x04;               // Enable digital functionality on PF2

    // Enable PWM1 module 6 output (M1PWM6 on PF2)
    PWM1_ENABLE_R |= 0x40;
}

void pwm_setDutycycle(uint8_t duty_cycle)
{
    if (duty_cycle >= 100) {
        PWM1_3_CMPA_R = 1;                  // 100% duty cycle
    } else if (duty_cycle == 0) {
        PWM1_3_CMPA_R = 1248;               // 0% duty cycle
    } else {
        PWM1_3_CMPA_R = (uint16_t)(1250 * (1 - (duty_cycle / 100.0)) - 1);
    }
}
