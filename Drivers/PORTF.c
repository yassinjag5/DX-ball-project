#include "PORTF.h"
#include "../Game/Nokia5110.h"
#include "../Game/potentiometer.h"

void PORTF_Init(void){  
  unsigned long volatile delay;

  // Enable clock for Port F
  SYSCTL_RCGC2_R |= (1 << 5); // (a) Activate clock for port F
  delay = SYSCTL_RCGC2_R;     // Allow time for the clock to stabilize

  // Unlock Port F for configuration
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock GPIO Port F
  GPIO_PORTF_CR_R = (1 << 4) | (1 << 0); // Allow changes to PF4 and PF0

  // Configure PF4, PF0 as inputs; PF3, PF2, PF1 as outputs
  GPIO_PORTF_DIR_R = (1 << 3) | (1 << 2) | (1 << 1); // PF3, PF2, PF1 output
                                                    // PF4, PF0 input
  
  // Disable alternate functions on PF4 and PF0
  GPIO_PORTF_AFSEL_R &= ~((1 << 4) | (1 << 0));  

  // Enable digital I/O on PF4–PF0
  GPIO_PORTF_DEN_R |= (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);

  // Configure PF4 and PF0 as GPIO (disable alternate functions)
  GPIO_PORTF_PCTL_R &= ~((0xF << 16) | (0xF << 0)); 

  // Disable analog functionality on PF4 and PF0
  GPIO_PORTF_AMSEL_R &= ~((1 << 4) | (1 << 0));  

  // Enable weak pull-up resistors on PF4 and PF0
  GPIO_PORTF_PUR_R |= (1 << 4) | (1 << 0);     

  // Configure PF4 and PF0 as edge-sensitive
  GPIO_PORTF_IS_R &= ~((1 << 4) | (1 << 0));     

  // Set PF4 and PF0 to single-edge triggering
  GPIO_PORTF_IBE_R &= ~((1 << 4) | (1 << 0));    

  // Set PF4 and PF0 for falling-edge triggering
  GPIO_PORTF_IEV_R &= ~((1 << 4) | (1 << 0));    

  // Clear interrupt flags for PF4 and PF0
  GPIO_PORTF_ICR_R = (1 << 4) | (1 << 0);      

  // Arm interrupts for PF4 and PF0
  GPIO_PORTF_IM_R |= (1 << 4) | (1 << 0);      

  // Set interrupt priority to 2 (priority field bits [23:21])
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (2 << 21); 

  // Enable interrupt 30 in NVIC (corresponding to Port F)
  NVIC_EN0_R |= (1 << 30);      

  EnableInterrupts(); // Enable global interrupts
}

void GPIOPortF_Handler(void){ // Called on touch of either SW1 or SW2
  if(GPIO_PORTF_RIS_R & (1 << 4)){  // SW1 (PF4) touch
    GPIO_PORTF_DATA_R &= 0x00;      // Clear all bits in Port F
    GPIO_PORTF_DATA_R |= (1 << 3);  // Turn on PF3 (Green LED)

    sw1flag = 0;  // Flag to start the game
    if(playerXcord < 63){
      Nokia5110_PrintBMP(playerXcord, 47, space, 0); // Clear the old position
      playerXcord += 4; // Move right
    }
    GPIO_PORTF_ICR_R = (1 << 4);  // Acknowledge interrupt for PF4
  }

  if(GPIO_PORTF_RIS_R & (1 << 0)){  // SW2 (PF0) touch
    GPIO_PORTF_DATA_R &= 0x00;      // Clear all bits in Port F
    GPIO_PORTF_DATA_R |= (1 << 1);  // Turn on PF1 (Red LED)

    if(playerXcord > 0){
      Nokia5110_PrintBMP(playerXcord + 16, 47, space, 0); // Clear the old position
      playerXcord -= 4; // Move left
    }
    GPIO_PORTF_ICR_R = (1 << 0);  // Acknowledge interrupt for PF0
  }

  // Draw the player ship at the new position
  Nokia5110_PrintBMP(playerXcord, 47, PlayerShip0, 0);
}
