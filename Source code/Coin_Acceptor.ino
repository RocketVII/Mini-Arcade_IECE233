int CApin = P5_2;
int pulse;
/*
 * this thread just attaches the interrupt
 */
void setup() {
    Serial.begin(9600); //Baud Rate
  pinMode(CApin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CApin),counterISR,RISING);

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
/*
 * checks the pulses and if the payment is is the right amount
 */
void counterISR(){
  if (pulse <4){
    pulse ++;
  }
  else{
    payment = true;
pulse =0;
  }
      Serial.println(" counter read");
}
