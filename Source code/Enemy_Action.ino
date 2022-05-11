/*
 * var for the enemy mecahnics
 */

boolean prelaseron = false;
  int  random1 ;
  int killrandom = 18;
  int laserticks = 0;
  int obsticks = 0;
  int screenFlag = 0;
  int spiketicks = 0;
  int smasherwait;
  boolean lasershot;
  boolean smasherAOE;
  int beeticks;
int smasherbossticks;
int smasherbosscount;
boolean beewingchange = false;
boolean prelaser= true;
int timerFlag_enemy =  0;



/*
 *  The used art for the enemies
 */
byte prelaserbeam[] = {
  B00101,
  B10000,
  B01010,
  B10001,
  B00100,
  B10010,
  B01001,
  B10010
};
byte laserbeam[8] = {
  B00110,
  B01100,
  B00110,
  B01100,
  B00110,
  B01100,
  B00110,
  B01100
};
byte hero[8]{
  B01110,
  B01000,
  B01110,
  B00100,
  B01110,
  B10101,
  B01010,
  B10001
};
byte obstacle[] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110
};
byte spikeart[] = {
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000,
  B00000
};
byte wingup[] = {
  B00100,
  B01010,
  B10010,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000
};
byte wingdown[] = {
  B00000,
  B01000,
  B10100,
  B10010,
  B01010,
  B00100,
  B00000,
  B00000
};
byte bee[] = {
  B01100,
  B01100,
  B00011,
  B00011,
  B01110,
  B01100,
  B10000,
  B00000
};
byte smasher[] = {
  B00100,
  B01010,
  B00100,
  B00100,
  B00100,
  B01010,
  B11111,
  B11111
};
byte rightslash[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B00101,
  B01010,
  B10101,
  B11110
};
byte leftslash[] = {
  B00000,
  B00000,
  B10000,
  B01000,
  B10100,
  B01010,
  B10101,
  B01111
};

// enemy clock is slower than the hero
OneMsTaskTimer_t timerTask_Enemy = {300, EnemyActionTimerISR, 0, 0};
void setupEnemy_Action() {
    OneMsTaskTimer::add(&timerTask_Enemy);
    OneMsTaskTimer::start();
  
  
  
  
}
  void loopEnemy_Action(){
  while( timerFlag_enemy == 0) { delay(10); }
    timerFlag_enemy = 0;
  if (gamestart){
    Enemy_State();
    enemyfight();
         }

}

/* The wall enemy mechanic
 *  moves from the right side to the left side 
 */
void obsfight(){
  if( obsloc.x >=0)
  obsloc.x --;
  else
  {
  obsloc.x = 16;
  obstacleOn = false;
    lcd.setCursor(obsloc.prevx,obsloc.y);
  lcd.print(" ");
  }
}


/* The bee boss mechanic
 *  starts the battle by a quick dash atk covering all of ground
 *  starts doing a diagonal motion until the end of the screen
 *  for the last phase it moves from the right side to the left with it's y spot being random 
 */
void beebossfight(){
  
           if (beeticks >random(1,7) && beeticks <18){
            beeboss.x = beeboss.x-2;
           // Serial.println("in first stage");
            
           }
           else if (beeticks == 18){
            beeboss.x =14;
           }
           else if (beeticks >18 && beeticks <28){
               beeboss.x = beeboss.x-2;
               if (beewingchange)
               beeboss.y = 0;
               else 
               beeboss.y =1;
             //  Serial.println("in 2nd stage");
           }
           else if (beeticks >28 && beeticks < 30){

            beeboss.y =1;
            beeboss.x = 14;
           // Serial.println("in 3rd stage");
           }
           else if(beeticks > 30 && beeticks <45){
            beeboss.y = random(-1,1);
            beeboss.x = beeboss.x-2;
         //   Serial.println("in 4th stage");
           }
           else if (beeticks >45){
                        beeticks =0;
                        beebossOn = false;
                        lcd.setCursor(beeboss.prevx,beeboss.prevy);
                        lcd.print(" ");
                        lcd.setCursor(beeboss.prevx+1,beeboss.prevy);
                        lcd.print(" ");
                      //  Serial.println("in before last stage");
           }
           else {
                        beeboss.x =14;
                        beeboss.y =1;
                       // Serial.println("in last stage");
           }

           beeticks ++;   
}
/* The smasher boss mechanic
 *  spwans on top of the player
 *  waits for some random ticks then drops onto the player
 *  while the smasher is on ground it has a chance to activate an AOE atk 
 */
void smasherbossfight(){
          
           if (smasherbossticks == 4){
            smasherboss.x = HeroLocation.x;
            smasherboss.y = 0;
             smasherwait = random(6,9);
            smasherbosscount++;
           }
           else if (smasherbossticks == smasherwait){
            smasherboss.y = 1;
            smasherbossticks=0;

           }
           else if (smasherbosscount == 6){
            smasherbossOn = false;
           lcd.setCursor(smasherboss.prevx,smasherboss.prevy);
           lcd.print(" ");
           lcd.setCursor(smasherboss.prevx-1,smasherboss.prevy);
           lcd.print(" ");
           lcd.setCursor(smasherboss.prevx+1,smasherboss.prevy);
           lcd.print(" ");
           }
           smasherbossticks++;
 
}
/* The laser enemy mechanic
 *  draws the pre laser hint
 *  waits for a number of ticks 
 *  draws the actual laser shot
 */
void laserfight(){
      killrandom = -1;
              laserticks++;  
      if ( laserticks == 1 ){
        prelaser ==  true;
        lasershot = false;
        laser.x  = random(0,15);
        //Serial.println("laser stage 1");
      }
      else if (laserticks <6){
        prelaser ==  false;
       // Serial.println("laser stage 2");
      }
      else {
        lasershot = true;
        killrandom = laser.x;
        laser.prevx = laser.x;
        laserticks = 0;  
        //Serial.println("laser stage 3");
      }

}
/* The spike enemy mechanic
 *  moves from right to the left by 1 spot
 *  randomly chooses it's next y spot
 *  after a full rotation chooses a random x spot to start from ranging from 15 to 20 to decided the delay on spawn
 */
void spikefight(){

  if( spike.x >=0)
  {
  spike.x--;
  spike.y =random (0,2);

  }
  else
  {
  spike.x= random(15,20);
  spikeOn = false;
   lcd.setCursor(spike.prevx,spike.prevy);
  lcd.print(" ");
  }
}
// Timer interrupt action
void EnemyActionTimerISR(){
  timerFlag_enemy = 1;
}

/* 
 * picks one of the enemies and sets their tag on depending on the score  
 */
void pickEnemy(int picker){
  if (picker == 0)
  {
    obstacleOn = true;
  }
    else if (picker == 1){
      spikeOn = true;
    }
    else if (picker == 2)
    {
    lcd.createChar(5,wingup);
    lcd.createChar(6,wingdown);
    lcd.createChar(7,bee);
      beebossOn = true;
    }
    else if (picker == 3){
    lcd.createChar(5,rightslash);
    lcd.createChar(6,leftslash);
    lcd.createChar(7,smasher);
      smasherbossOn = true;
    }
    
}
void Enemy_State(){
  if (score <30 ){      
      pickEnemy(0); 
      Serial.println("Stage 1");
  }
  else if (score <80 && score >30){

     if (!obstacleOn && !spikeOn && !beebossOn && !smasherbossOn){          
      pickEnemy(random(0,2)); 
              laserOn = false;

  }
              Serial.println("Stage 2");
  }

  else if (score < 150 && score >80){
  if (!beebossOn && !smasherbossOn && !obstacleOn && !spikeOn){    
  pickEnemy(random(2,4)); 
  Serial.println("Stage 3");
  }
}
  else if (score < 200 && score >150){
  if (!beebossOn && !smasherbossOn && !obstacleOn && !spikeOn){    
  pickEnemy(random(2,4)); 

  } 
    Serial.println("Stage 4");
        laserOn = true;
      
}
else if (score > 200){  
  if (!obstacleOn && !spikeOn){   
  pickEnemy(random(0,2)); 
  }
  if (!beebossOn && !smasherbossOn){    
  pickEnemy(random(2,4)); 
  }
  laserOn = true;
  Serial.println("Stage 5");
}

}
/*
 * Summons the enemy that depending on which flag is on 
 */
void enemyfight(){

  if (spikeOn){
    spikefight();
  }
  if (laserOn){
     laserfight();
  }

  if(beebossOn){
     beebossfight();
  }
  if (smasherbossOn){
     smasherbossfight();
  }
  if (obstacleOn){
    obsfight();
  }
}
