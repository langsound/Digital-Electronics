/*
Blink-midi
 Turns on an LED on for one second, then off for one second, repeatedly.
Modified for Teensy, USB Midi control.

Note number sets speed.
velocity sets output on or off
 
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int turnPot = 1000;
int gatePot = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);

}

// the loop routine runs over and over again forever:
void loop() {
  usbMIDI.read();  

  if(gatePot > 0){

    digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(turnPot); // wait for a some time set by turnPot
    digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
    delayMicroseconds(turnPot); // wait for a some time set by turnPot
  }//end if
  
}//end loop


void OnNoteOn(byte channel, byte note, byte velocity)
{
  turnPot = (128 - note) / 20  ;
  gatePot = 127;
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  gatePot = 0;
}

