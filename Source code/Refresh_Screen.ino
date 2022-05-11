void setupRefresh_Screen() {

    lcd.createChar(0,hero);
    lcd.createChar(1,obstacle);
    lcd.createChar(2,prelaserbeam);
    lcd.createChar(3,laserbeam);
    lcd.createChar(4,spikeart);

//Sets up the enemy spots
  
obsloc.y = 1;
obsloc.x = 18;
beeboss.y = 1;
beeboss.x = 14;
beeboss.prevx = 18;
obsloc.prevx = 18;
smasherboss.x =  14;
smasherboss.prevx =  18;
smasherboss.y =  1;
}
/*
 * Loops the drawing functions
 */
void loopRefresh_Screen() {
  while( timerFlag == 0){ delay(10); }
  if(gamestart){
  drawenemy();
  drawHero();
  checkgameover();
  score++;

}
  }
  
 /*
  * The drawing functions
  * 
  */
void drawbeeboss(){
           lcd.setCursor(beeboss.prevx,beeboss.prevy);
           lcd.print(" ");
           lcd.setCursor(beeboss.prevx+1,beeboss.prevy);
           lcd.print(" ");
           lcd.setCursor(beeboss.x,beeboss.y);
           lcd.write(byte(7));
           beeboss.prevx =beeboss.x;
           beeboss.prevy = beeboss.y;
           if (beewingchange){
            lcd.setCursor(beeboss.x+1,beeboss.y);
           lcd.write(byte(6));
           beewingchange = false;

           }
           else {
           lcd.setCursor(beeboss.x+1,beeboss.y);
           lcd.write(byte(5));
           beewingchange = true;
           }      
}
void smasherbossdraw(){
              smasherAOE =false; 
           lcd.setCursor(smasherboss.prevx,smasherboss.prevy);
           lcd.print(" ");
           lcd.setCursor(smasherboss.prevx-1,smasherboss.prevy);
           lcd.print(" ");
           lcd.setCursor(smasherboss.prevx+1,smasherboss.prevy);
           lcd.print(" ");
           lcd.setCursor(smasherboss.x,smasherboss.y);
           lcd.write(7);
           smasherboss.prevx= smasherboss.x;
           smasherboss.prevy= smasherboss.y;
           if (smasherboss.y == 1 && random (-1,3) == 1 ){
            lcd.setCursor(smasherboss.x+1,1);
            lcd.write(5);
            lcd.setCursor(smasherboss.x-1,1);
            lcd.write(6);         
            smasherAOE = true;  
           }
 
         
}
void drawspike(){
  lcd.setCursor(spike.prevx,spike.prevy);
  lcd.print(" ");
  lcd.setCursor(spike.x,spike.y);
  lcd.write(byte(4));
  spike.prevx = spike.x;
  spike.prevy = spike.y;

}
void drawHero(){
  lcd.setCursor(HeroLocation.prevx,HeroLocation.prevy);
  lcd.print(" ");
  lcd.setCursor(HeroLocation.x,HeroLocation.y);
  lcd.write(byte(0));
  HeroLocation.prevx = HeroLocation.x;
    HeroLocation.prevy = HeroLocation.y;
}
void drawObstacle(){
  lcd.setCursor(obsloc.prevx,obsloc.y);
  lcd.print(" ");
  lcd.setCursor(obsloc.x,obsloc.y);
  lcd.write(byte(1));
  obsloc.prevx = obsloc.x;
 
  
}
void drawlaster(){
  if (prelaser == true ){
      lcd.setCursor(laser.prevx,1);
      lcd.print(" ");
      lcd.setCursor(laser.prevx,0);
      lcd.print(" ");
      lcd.setCursor(laser.x,1);
      lcd.write(byte(2));

  }
  else if (prelaser == false && lasershot ==false){

          lcd.setCursor(laser.x,1);
}
     if (lasershot == true){
       lcd.setCursor(laser.x ,1);
       lcd.write(byte(3));
       lcd.setCursor(laser.x ,0);
       lcd.write(byte(3));

       
  }

  
}
/*
 * A function to check if the hero died to keep it clean
 */
void checkgameover(){
  if (HeroLocation.prevx == obsloc.prevx && HeroLocation.prevy == 1 && obstacleOn){
   gameover();
     Serial.println("obs death");
  }
  else if (HeroLocation.prevx == killrandom && laserOn){
    gameover();
      Serial.println("laser death");
  }
  else if (HeroLocation.prevx == spike.prevx && HeroLocation.prevy == spike.prevy && spikeOn){
    gameover();
      Serial.println("spike death");
  }
  else if ((HeroLocation.prevx == beeboss.prevx ||HeroLocation.prevx == beeboss.prevx+1) && HeroLocation.prevy == beeboss.prevy && beebossOn ){
    gameover();
      Serial.println("bee death");
  }
  else if (HeroLocation.prevx == smasherboss.prevx && HeroLocation.prevy == smasherboss.prevy && smasherbossOn){
    gameover();
      Serial.println("smasher death");
  }
  else if ((HeroLocation.prevx ==smasherboss.prevx+1 ||HeroLocation.prevx ==smasherboss.prevx-1) && HeroLocation.prevy == smasherboss.prevy &&smasherAOE){
    gameover();
      Serial.println("smasher AOE death");
}
else {
}
}
/*
 * The game over display command
 */
void gameover(){
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  lcd.clear();
    enemyreset();
  lcd.print("Game Over!");
   lcd.setCursor(0,1);
  lcd.print(score);
  menu_State = menu_gameover;
  gamestart =false;
   payment = false;
  score=0;
 
}
/*
 * Resets all the enemies into a starting spot
 */
void enemyreset(){
 killrandom = 18;
 laserticks = 0;
 obsticks = 0;
 screenFlag = 0;
 spike.x = 16;
 spike.y=3;
 spiketicks = 0;
 obsloc.x =18;
 beeboss.x =18;
 smasherboss.x = 18;
 smasherboss.prevx = 18;
 beeticks =0;
 laserOn = false;
 spikeOn = false;
 obstacleOn = false;
 beebossOn = false;
  smasherbossOn = false;
  smasherbosscount=0;
  smasherbossticks = 0;

}
/*
 * Draws the enemy based on which enemy flag is on
 */
void drawenemy(){
  if (obstacleOn){
    drawObstacle();
  }
  if (spikeOn){
    drawspike();
  }
  if (laserOn){
     drawlaster();
  }

  if(beebossOn){
     drawbeeboss();
  }
  if (smasherbossOn){
     smasherbossdraw();
  }

}
