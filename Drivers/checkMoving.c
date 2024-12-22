
#include "checkMoving.h"

#include "../Game/Nokia5110.h"
int play(void){
if(ballYcord >= 43 && ballXcord >= playerXcord && ballXcord < playerXcord + 20){//the player ship hit the ball 
			temp = ballXcord - playerXcord;
			if(temp < 8){//the ball hit the left of the player ship
				xval = -4;//the ball will go left 
			}else if(temp < 12 ){//the ball hit the center of the player ship
				xval = 0;//the ball will not change its direction
			}else{//the ball hit the right of the player ship 
				xval = 4;// the ball will go right
			}
			yval = -4;//anyway the ball will move up
		}
		Nokia5110_PrintBMP(ballXcord, ballYcord, space, 0);
		
		tx = (ballXcord + xval)/4;
		ty = (ballYcord + yval)/4;
		
		//Special Cases
		
		if(ballYcord <= 4 && ballXcord>=80){//the ball at the top right corner (updating the next food index) 
				ty=2;
			}
		if(tx==21){   //when the ball hit the right border within the food area
			tx=tx-2;
			//if the ball rebounce to eat food -> update the ball direction 
				if(foodArr[tx][ty]&&yval<0){//when the ball is moving up right
					xval=-4;
				  yval=-4;
				}else if(foodArr[tx][ty]&&yval>0){//when the ball is moving down right
				xval=-4;
				yval=4;
				}
			}
		 if((ballYcord <= 4&&ballXcord<=0)){//the ball at the top left corner (updating the next food index)
			ty=2;
			if(tx<=0){//when the ball hit the right border within the food area
			  tx=1;
				//if the ball rebounce to eat food -> update the ball direction 
				if(foodArr[tx][ty]&&yval<0){//when the ball is moving up left
					xval=4;
				yval=-4;
			}else if(foodArr[tx][ty]&&yval>0){//when the ball is moving up right
			  xval=4;
				yval=4;
			}}};
      if(ballYcord<=4){//when the ball hit the top border -> update food index 
			  ty=2;
				yval=4;
			}
		
		if(tx >= 0 && ty >= 0 && tx < 21 && ty < (5+level) && foodArr[tx][ty]){//if the ball about to hit food
			ballXcord += xval;
			ballYcord += yval;
			if(xval > 0 && yval < 0){// ball is moving up right
				if(foodArr[tx][ty + 1] && foodArr[tx - 1][ty]){ // there is  food down and left of target food
					if(ballXcord>=79){
					yval = -yval;//the ball will move down
					}else{
					xval = -xval;//the ball will move left
					yval = -yval;//the ball will move down
					}
				}else if(foodArr[tx - 1][ty]){// there is food left of target food
					yval = -yval;//the ball will move down right
				}else{//there is no food down or left of target food
					xval = -xval;//the ball will move up left
				}
			}else if(xval < 0 && yval < 0){// ball is moving up left
				if(foodArr[tx + 1][ty] && foodArr[tx][ty + 1]){// there is  food down and right of target food
					if(ballXcord<=0){
					yval = -yval;//the ball will move down
					}else{
					xval = -xval;//the ball will move right
					yval = -yval;//the ball will move down
					}
				}else if(foodArr[tx + 1][ty]){// there is food right of target food
					yval = -yval;//the ball will move down left
				}else{// there is no food down or right of target food
					xval = -xval;//the ball will move up right
				}
			}else if(xval < 0 && yval > 0){//the ball is moving left down
				if(foodArr[tx + 1][ty] && foodArr[tx][ty - 1]){// there is  food above and right of target food
					if(ballXcord<=0){
						yval = -yval;//the ball will move up
					}else{
					xval = -xval;//the ball will move right
					yval = -yval;//the ball will move up
					}}else if(foodArr[tx + 1][ty]){// there is food right of target food
					yval = -yval;//the ball will move up left
				}else{// there is no food above or right of target food
					xval = -xval;//the ball will move down right
				}
			}else if(xval>0&&yval>0){//the ball is moving down right
				if(foodArr[tx - 1][ty] && foodArr[tx][ty - 1]){// there is  food above and left of target food
					if(ballXcord>=79){
					yval = -yval;//the ball will move up
					}else{
					xval = -xval;//the ball will move left
					yval = -yval;//the ball will move up
				}}else if(foodArr[tx - 1][ty]){// there is food left of target food
					yval = -yval;//the ball will move up right
				}else{// there is no food above or left of target food
					xval = -xval;//the ball will move down left
				}
			}else{//the ball is moving up
			yval=-yval;
			}
			foodArr[tx][ty] = 0;
			score+=10*level;
			++fe;
			
			if(fe==63+(21*level)){	//   fe==1
				Nokia5110_Clear();
				Nokia5110_SetCursor(2, 1);
				Nokia5110_OutString("YOU HAVE");
				Nokia5110_SetCursor(3, 2);
				Nokia5110_OutString("PASSED");
				Nokia5110_SetCursor(1,3);
				Nokia5110_OutString("level");
				Nokia5110_OutUDec(level);
				Nokia5110_SetCursor(2, 4);
				Nokia5110_OutString(" SCORE");
				Nokia5110_SetCursor(1, 5);
				Nokia5110_OutUDec(score);
				Delay100ms(40);
				++level;
				if(level>3){
					WinGame();
					return 0;
				}
				ballXcord=36;
				ballYcord=36;
				xval=4;
				yval=-4;
				fe=0;
				Nokia5110_Clear();
				Nokia5110_SetCursor(1, 2);
				Nokia5110_OutString("  Level  ");	
				Nokia5110_SetCursor(1, 4);
				Nokia5110_OutUDec(level);
				Nokia5110_SetCursor(0, 0); // renders screen
				Delay100ms(20);
				display(level);
			}
				
   
		}else{
			if(ballXcord <=0 || ballXcord >= 79){//the ball is out of range of the screen left or right 
				xval = -xval;//the ball will reverse its direction 
			}
			if(ballYcord < 4){//the ball is moving up and  exceeded the foods 
				yval = -yval;//the ball will go down 
				
			}
			if(ballYcord >= 47){//the player ship missed the ball 
				--lifes;
				if(lifes==0){
				   EndGame();
						
				    return 0;
				}
				ballXcord=36;
				ballYcord=36;
				xval=4;
				yval=-4;
			}
			ballXcord += xval;
			ballYcord += yval;
		}
		Delay100ms((35-(level*10)));   // control the ball speed 23
		Nokia5110_PrintBMP(ballXcord, ballYcord, ball, 0);
		Nokia5110_DisplayBuffer();
    return 1;
}
   
	
