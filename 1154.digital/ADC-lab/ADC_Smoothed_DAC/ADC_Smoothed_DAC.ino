/*
    analog read to analog write with mapping and smoothing
    connect a switch or button to analog input pin 2 for most easily observable results
*/
 
//set pwm Min/Max here, as needed
int pwmMin = 0;
int pwmMax = 255;

// change pwmSmooth here 
float pwmSmooth = 0.5;
float pwmOut;
 
int pwmPin = 3;
int onOffPin = 4;
 
void setup(){
  pinMode(pwmPin, OUTPUT);
  pinMode(onOffPin, OUTPUT);
}//endsetup
 
void loop(){
 
  //read analog pin TWO, map to min and max range smooth and, write to pwmPin
  pwmOut = map(analogRead(2), 0, 1024, pwmMin, pwmMax) * (1-pwmSmooth) + pwmOut * pwmSmooth;
 
  //write output smoothed
  analogWrite(pwmPin, pwmOut );
  
 // write output not smoothed
  analogWrite(onOffPin, map(analogRead(2), 0, 1024, pwmMin, pwmMax));
  
 
  delay(33); // change the delay so that smoothing can be more easily observed.
 
}//endloop
