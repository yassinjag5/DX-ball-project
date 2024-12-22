
#include "../Game/tm4c123gh6pm.h"


int play(void);
extern int score,level,fe,lifes;
extern int playerXcord , ballXcord , ballYcord , xval , yval , tx, ty, temp;


extern const unsigned char logo[];

extern const unsigned char food[] ;

extern const unsigned char space[];

extern const unsigned char ball[];

extern const unsigned char PlayerShip0[];

extern void WinGame(void);
extern void EndGame(void);
extern void display(int level);
 
 extern int foodArr[21][8];

void Delay100ms(unsigned long count);
