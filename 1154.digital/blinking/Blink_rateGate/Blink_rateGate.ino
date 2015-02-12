/*
Blink
Turns on an LED on for one second, then off for one second, repeatedly.

Blink_RateGate changes the delay time of the loop, thus the rate of the blinking, Changes to rate are gated by button
connect potentiometer to pin A0 and button to A1.
*/

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int turnPot = 1000;

// the setup routine runs once when you press reset:
void setup() {
// initialize the digital pin as an output.
pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
if(analogRead(1) > 512){
turnPot = (analogRead(0) * 2) + 250 // measure A1 return a value 250 to 2298 (being used a milliseconds
}//end if

digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
delay(turnPot); // wait for a some time set by turnPot
digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
delay(turnPot); // wait for a some time set by turnPot
}//end loop
