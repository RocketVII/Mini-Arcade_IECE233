int xout = P6_1 ;
int yout = P4_0;
int xjoy;
int sw = P4_6;
int cnt;
boolean gamestart = false;
boolean payment= false;
#include "OneMsTaskTimer.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(P6_7, P2_3, P2_6, P2_4, P5_6, P6_6);

#include "OneMsTaskTimer.h"
enum PA_States { PA_Start, PA_SG , PA_WA , PA_MF, PA_MB ,PA_JP} PA_State;
enum menu_States { menu_Start,menu_insertCoin ,menu_option1 ,  menu_option2 , menu_Story, menu_gameon,menu_gameover} menu_State;

int score;
int highscore;


boolean obstacleOn = false;
boolean laserOn = false;
boolean spikeOn = false;
boolean beebossOn = false;
boolean smasherbossOn = false;

typedef struct xy_struct{
  int x;
  int y;
  int prevx;
  int prevy;
} XY;
XY HeroLocation;
XY obsloc;
XY beeboss;
XY smasherboss;
XY laser;
XY spike;
int timerFlag = 0;
boolean backflag,forwardflag, jumpflag;

//timerTask must be stored in static memory region
//  1st parameter is time in milliseconds.  
//  2nd paramter is the name of the interrupt service routine
OneMsTaskTimer_t timerTask = {125, PlayerActionTimerISR, 0, 0};
/*
 * The quick set up for the player action 
 */
void setupPlayerActions() {
  Serial.begin(9600); //Baud Rate

  menu_State = menu_Start;
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw),jumpISR,RISING);

  //Attach and start the interrupt
  OneMsTaskTimer::add(&timerTask);
 
  OneMsTaskTimer::start();
      lcd.begin(16, 2);
}

/*
 * the main looping function
 */
void loopPlayerActions() {
Serial.println(payment);
  while( timerFlag == 0) { delay(10); }
  //reads the x input from the joy stick
  xjoy = analogRead(xout);
 //Serial.println(xjoy);
  backflag = false;
  forwardflag= false;
  //Serial.println("Clock Tick");
  
  timerFlag = 0;
if ( xjoy < 100){
backflag = true;
}


else if (xjoy > 400 && xjoy <600){
forwardflag = true;
}
menustate();
Playerstate();
/*
Serial.print("Hero position: ");
Serial.print(HeroLocation.x);
Serial.print(" ");
Serial.println(HeroLocation.y);
*/

/*
 * the jump interupt 
 */
}
void jumpISR(){
  jumpflag = true;
}
/*
 * Player action state machine
 */
void PlayerActionTimerISR(){
  timerFlag = 1;
}
void Playerstate(){
  switch (PA_State){
  case PA_Start:
  PA_State = PA_SG;
  break;
    case PA_SG:
  PA_State = PA_WA;
  break;
    case PA_MF:
  PA_State = PA_WA;
  break;
    case PA_MB:
  PA_State = PA_WA;  
  break;
    case PA_JP:
    if (cnt >=5){
        PA_State = PA_WA;
        cnt = 0;
        HeroLocation.y =1;
        jumpflag = false;
    }

  break;
    case PA_WA:
    if( backflag){
  PA_State = PA_MB;
    }
  else if (forwardflag){
    PA_State = PA_MF;
  }
else if (jumpflag){
      PA_State = PA_JP;
}
  break;
  }
    switch (PA_State){

    case PA_SG:
  HeroLocation.x= 0;
  HeroLocation.y =1;
  break;
    case PA_MF:
    if(HeroLocation.x <15)
   HeroLocation.x++;
  break;
    case PA_MB:
    if (HeroLocation.x > 0)
   HeroLocation.x--; 
  break;
    case PA_JP:
  HeroLocation.y =0;
  cnt ++;
  break;
    case PA_WA:
  break;
    }
    
}


/*
 * the menu state machine
 */
void menustate(){
  switch(menu_State){
    case menu_Start:
    menu_State = menu_insertCoin;
    drawInsertCoin();
    break;
    case menu_insertCoin:
    if (payment){
      menu_State = menu_option1;
     // payment = false;
      drawoption1();
    }
    break;
    case menu_option1:
   if (jumpflag){
    menu_State = menu_gameon;
    gamestart = true;
    delay(100);
    jumpflag = false;
    PA_State = PA_Start;
    score = 0;
    lcd.clear();
   }
   else if ( backflag || forwardflag){
    menu_State = menu_option2;
    drawoption2();
    backflag = false;
    forwardflag= false;
   }
   break;
       case menu_option2:
   if (jumpflag){
    menu_State = menu_Story;
   }
   else if ( backflag || forwardflag){
    menu_State = menu_option1;
    drawoption1();
    backflag = false;
    forwardflag= false;
   }
   break;

  case menu_Story:
    drawStory();
    jumpflag= false;
    menu_State = menu_option1;
        drawoption1();

  break;
  case menu_gameover:
  if (jumpflag){
    menu_State = menu_insertCoin;
        drawInsertCoin();

            delay(1000);
            jumpflag = false;
  }
  break;
    }
}
/*
 * The LCD menu drawing functions
 */
void drawoption1(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Start Game");
      lcd.setCursor(0, 1);
      lcd.print(" Story ");
}
void drawoption2(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Start Game");
      lcd.setCursor(0, 1);
      lcd.print(">Story ");
}
void drawInsertCoin(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Insert $0.25");
}
void drawStory(){

            lcd.setCursor(0, 0);
      lcd.print("Our story begins");
       lcd.setCursor(0, 1);
      lcd.print("A long time ago");
      delay(4000);
      lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("A time before ");
       lcd.setCursor(0, 1);
      lcd.print("the age of heroes");
       delay(4000);
           lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("Where a man ");
      lcd.setCursor(0, 1);
      lcd.print("lost his mind");
       delay(4000);
           lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("& wondered into");
      lcd.setCursor(0, 1);
      lcd.print("The unknown");
       delay(4000);
           lcd.clear();
}
