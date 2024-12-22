

void draw(int level);
void display(int level);

void Delay1a00ms(unsigned long count);
extern const unsigned char logo[];

extern const unsigned char food[] ;

extern const unsigned char space[];

extern const unsigned char ball[];

extern const unsigned char PlayerShip0[] ;

extern int ballYcord,score,timerflag,sw1flag;

extern int foodArr[21][8]; 

void EnableInterrupts(void);
void WaitForInterrupt(void);
