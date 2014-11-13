// MIDI continuous control of analog circuits

// you will need to change the LED pin to a PWM capable pin
int ledPin = 13;
int ctlArray[128];


void setup()
{
  pinMode(ledPin, OUTPUT);
//flash lights for a second
  for(int i; i<11; i++){
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
   }
}


void loop(){
  // see if there are any MIDI messages to comming in.
  usbMIDI.read();
  
  //only type 3 is MIDI continuous control
  if(usbMIDI.getType() == 3) {
  //store all the continuous controller data values in an array
  // the position of the array is set by the controller number
  // the data in that position of the array is the controller value
  ctlArray[usbMIDI.getData1()] = usbMIDI.getData2();
  }  
    
   //lets do something with these continous controls 
    
    //use continuous controller number 7 to control the brightness of an LED
    // MIDI is 7 bit, and analogWrite is 8 bit, so multiply by two to get a full range.
    analogWrite(ledPin, ctlArray[7] * 2);
    
  

delay(1);
}

