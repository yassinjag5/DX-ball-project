#include "screen_draw.h"
#include "../Game/Nokia5110.h"
void draw(int level){
	int i , j ;
for(i=0;i<84;i+=4){
		for(j=8;j<20+level*4;j+=4){
			Nokia5110_PrintBMP(i, j , food, 0);
			
			foodArr[i/4][j/4] = 1;
		}
	}
}

	void WinGame(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("CONGRATS");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("YOU WIN");
  Nokia5110_SetCursor(0, 0); // renders screen
	}		
	void startingScreen(){
	Nokia5110_SetCursor(0,0);
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(20, 25, logo, 0);
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(3,5);
	Nokia5110_OutString("DX BALL");	
		

		

while(timerflag){//delay 2 sec using timer
    WaitForInterrupt();
  }
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_SetCursor(0,0);
	Nokia5110_OutString("To Play ");	
	Nokia5110_SetCursor(0,1);
	Nokia5110_OutString("Press push ");	
	Nokia5110_SetCursor(0,2);
	Nokia5110_OutString("button 1");	

		while(sw1flag){
		
		WaitForInterrupt();

}
}
	void display(int level){
	
	Nokia5110_Clear();
  Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
	startingScreen();								//draw logo
	Nokia5110_Clear();
  Nokia5110_ClearBuffer();
  Nokia5110_PrintBMP(32, 47, PlayerShip0, 0); // player ship middle bottom
	Nokia5110_PrintBMP(ballYcord, ballYcord, ball, 0);
  Nokia5110_DisplayBuffer();     // draw buffer
	draw(level);
	Nokia5110_DisplayBuffer();
}



	void EndGame(){
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("GAME OVER");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("Nice try,");
	Nokia5110_SetCursor(1, 3);
  Nokia5110_OutString("  Score");
	Nokia5110_SetCursor(1, 4);
  Nokia5110_OutUDec(score);
  Nokia5110_SetCursor(0, 0); // renders screen
		
		
	}
	
	


void Delay1a00ms(unsigned long count){unsigned long volatile time;
  while(count>0){
    time = 72724;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}


