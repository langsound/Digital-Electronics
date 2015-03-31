/*
analog read to analog digital and analog write with mapping
*/
 
//set pwmMin/Max here (rather than in the middle of the code)
int pwmMin = 0;
int pwmMax = 255;

//set aMin/Max here (rather than in the middle of the code)
int aMin = 0;
int aMax = 1024;

  
// you may change these if needed
int pwmPin = 3;  // pwm capable pins on teeensy: 3, 4, 5, 6, 9, 10, 20, 21, 22, 23, 25, 32
int onOffPin = 2;
 
void setup(){
pinMode(pwmPin, OUTPUT);
pinMode(onOffPin, OUTPUT);
}//endsetup
 
void loop(){
 
 //read analog pin zero, map to min and max range, write to pwmPin
 analogWrite(pwmPin, map(analogRead(0), 0, 1024, pwmMin, pwmMax));
 
 // control on/off LED with a potentiometer...
 digitalWrite(onOffPin, map(analogRead(0), aMin, aMax, 0, 1));
 
}//endloop
