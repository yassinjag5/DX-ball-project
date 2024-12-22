// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include "Drivers/PORTF.h"
#include <string.h>
#include <stdlib.h>
#include "Drivers/TIMER2.h"
#include "Drivers/shapes.h"
#include "Drivers/screen_draw.h"
#include "Drivers/checkMoving.h"
#include "potentiometer.h"
#include "pwm.h"
#include "dht11.h"
#include "temp.h"
#include "uart.h"
#include "port.h"
//#include"uart_driver.h"


// *************************** FUNCTIONS DEFINATIONS  ***************************

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long count); // time delay in 0.1 seconds

void led_smart_home(void);
void WaitForInterrupt(void);  // low power mode
void EndGame(void);
void WinGame(void);


// *************************** Capture image dimensions out of BMP**********


	
int score=0,level=2,fe=0,lifes=3;
int playerXcord = 32, ballXcord = 36, ballYcord = 36, xval = 4, yval = -4, tx, ty, temp,sw1flag=1,timerflag=1;
int foodArr[21][8]; 
unsigned long Semaphore;



static unsigned int  pot_read=1000;



        int main(void){
 TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
					UART_Init();// delete
	//				UART_Init_driver(0);

	Nokia5110_Init();
	PORTF_Init();
	//GPIO_PORTF_DATA_R|=(1<<1);
			
		Timer2_Init(80000000);//delay 1 sec //2
Pot_Init(AIN8,ADC_EMUX_EM3_PROCESSOR); 
	display(level);
					
  while(1){
						
		play();
		if(play()==0){			
			Nokia5110_SetCursor(1,5);
			Nokia5110_OutString("press 1");
			while(UART_InChar()!='1'){}
		Nokia5110_Clear();
       
        Nokia5110_SetCursor(0, 0); // Column 2, Row 2
    Nokia5110_OutString("play again");

    // "yes press sw1" centered
    Nokia5110_SetCursor(3, 2); // Column 2, Row 3
			Nokia5110_OutString("yes: sw1");

    // "no press sw2" centered
    Nokia5110_SetCursor(3, 4); // Column 2, Row 4
			Nokia5110_OutString("no : sw2");
			while((GPIO_PORTF_DATA_R &(1<<4)))
			{
						if(!(GPIO_PORTF_DATA_R &(1<<0))) // 
						{
							
							Nokia5110_Clear();
				Nokia5110_SetCursor(1, 1); // Centered in row 2
							Nokia5110_OutString(" you are");

    // "my friend" centered
    Nokia5110_SetCursor(1, 2); // Centered in row 3
    Nokia5110_OutString(" in smart");
							Nokia5110_SetCursor(1,3); // Centered in row 3
    Nokia5110_OutString(" home");
							Nokia5110_SetCursor(1,5); // Centered in row 3
								Nokia5110_OutString("press 1");
					while(UART_InChar()!='1'){}
							led_smart_home();
							return 0;
						}
							
			
			}
			
        Nokia5110_SetCursor(0, 0);
		 score = 0;
        level = 2;
        fe = 0;
        lifes = 3;
        playerXcord = 32;
        ballXcord = 36;
        ballYcord = 36;
        xval = 4;
        yval = -4;
        memset(foodArr, 0, sizeof(foodArr)); // Clear food array

        display(level); // Display initial level
		}
			 // 
		
					
				

			
}

}




void Delay100ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 72724;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void led_smart_home(void)
{
		
						
	
	uint8_t temp=0,  humidity=0;
	
	
	Nokia5110_Clear();
	Port_Init(4);
	pwm_init();
	GPIO_PORTF_DATA_R=0;
	ADC0_Init1();
	DisableInterrupts();
	while(1)
	{
		
	
		
		pot_read= (Pot_Read()/4095.0)*100;
		temp=Tempsensor_read();
		
		Nokia5110_OutString("SMART HOME: ");
		Nokia5110_SetCursor(0,1);
			Nokia5110_OutString("- - - - - - - - - - - - ");
		
		Nokia5110_SetCursor(0,2);
		Nokia5110_OutString("TEMPERATURE: ");
		Nokia5110_SetCursor(0,3);
		Nokia5110_OutUDec(temp);
		Nokia5110_OutString("^C");
		Nokia5110_SetCursor(0,4);
		Nokia5110_OutString("LIGHTNESS :");
		Nokia5110_SetCursor(0,5);
		Nokia5110_OutUDec(pot_read);
		
	
		//	Nokia5110_OutUDec(humidity);
		
		Nokia5110_SetCursor(0,0);
		pwm_setDutycycle(pot_read);
		
	}



}


