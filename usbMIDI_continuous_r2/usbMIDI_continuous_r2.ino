/*
describe the program here.  put your name on it and stuff... date it. version.

describe the pin configuration,  or remind yourself of what needs to be 
connected to what.
*/

// name the pins and declare stuff 

// Mux related stuff
int muxS0 = 2; //this is the digital pin connected to mux S0
int muxS1 = 3; //this is the digital pin connected to mux S1
int muxS2 = 4; //this is the digital pin connected to mux S2
int muxS3 = 5; //this is the digital pin connected to mux S3
int muxSigPin = 0;// this is the analog pin connected to mux Sig pin

// storage and processing stuff
int NumberOfAnalogPins = 16;
float smoothingCo = 0.9;// must be between 0.001 and 0.999

int pinReadingStorage[NumberOfAnalogPins];


//every sketch needs a setup fuction
void setup(){
  // setting digital pins as inputs or outputs
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  
  // maybe blink some lights.
  // maybe send a midinote to confirm things are working
  
}//

////////   describe modular function here

void sendMidi(int statusByte, int Data1Byte, int Data2Byte){
 
 if( statusByte > 143 && statusByte < 160){
  usbMIDI.sendNoteOn(Data1Byte, Data2Byte, statusByte);
 }

 if( statusByte > 175 && statusByte < 192){
  usbMIDI.sendControlChange(Data1Byte, Data2Byte, statusByte);
 }
 
  if( statusByte > 223 && statusByte < 240){
  usbMIDI.sendPitchBend(Data1Byte, statusByte);  
 }
 
  
 
 
}//end sendMIDI


/// read the Pins please

void readThePins(int numberOfPins){
  for(int i; i< numberOfPins; i++){
     digitalWrite(muxS0, i & 1);
     digitalWrite(muxS1, i & 2);
     digitalWrite(muxS2, i & 4);
     digitalWrite(muxS3, i & 8);
     // put a little bit of time between mux channel set and the pin read
     delayMicroseconds(500);
     pinReadingStorage[i]=analogRead(muxSigPin);
     
    
  }//end pins loop
  
  
}// end readThePins





void loop() {
// read the pins (argument = number of pins to read)
    readThePins(NumberOfAnalogPins);

// condition data and sending the midi
    
    for(int i; i <= NumberOfAnalogPins; i++){
     
      if( pinReadingStorage[i] != pinsAvg[i]){
      pinsAvg[i] = pinsAvg[i] * smoothingCo + pinReadingStorage[i] * 1-smoothingCo;
        sendMIDI(176, i, pinsAvg[i]/4);
        delay(1);     
       }//end if not same
     
     
      
    }//end for pins
    
    
    


  
}


