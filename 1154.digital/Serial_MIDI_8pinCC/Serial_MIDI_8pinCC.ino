/*
This program reads the first 8 analog pins and transmits the readings as MIDI
only if the readings have changed.  otherwise it does not send.
This program is build modularly so that it can be easily connected 
to a multiplexor with less than 12 additional lines of code.

*/

// name the pins and declare stuff 


// storage and processing stuff
int NumberOfAnalogPins = 8;
int pinReadingStorage[8];
int pinsAvg[8];
// the above argumnets and variables should match all 8s or all 10s or all 16s,

float smoothingCo = 0.9;// must be between 0.001 and 0.999

//serial stuff
int myBaud = 31250; // MIDI=31250, serial = 9600 or in our class 19200


int LED = 13;//the built in LED

//every sketch needs a setup fuction
void setup(){
  // setting digital pins as inputs or outputs
  pinMode(LED, OUTPUT);
  
  //the serial port needs to be initiated so we can use it later.
  Serial.begin(myBaud);
  
  // maybe blink some lights.
  
  
}//

//Send the MIDI
void sendMIDI(int statusByte, int Data1Byte, int Data2Byte){
  
 //send the three bytes of MIDI in order. 
 Serial.write(statusByte);
 Serial.write(Data1Byte);
 Serial.write(Data2Byte);
 delay(2);
 
 
}//end sendMIDI


/// read the Pins please

void readThePins(int numberOfPins){
  for(int i; i< numberOfPins; i++){
       
      //add mux code here
    
    
     delayMicroseconds(500);
     pinReadingStorage[i]=analogRead(i);
    
  }//end pins loop
  
}// end readThePins





void loop() {
// read the pins (argument = number of pins to read)
    readThePins(NumberOfAnalogPins);

// condition data and sending the midi
    
    for(int i; i <= NumberOfAnalogPins; i++){
     
      //if the sensor connected to the analog pin has changed, send that info
      if( pinReadingStorage[i] != pinsAvg[i]){
        
       //smoothing 
      pinsAvg[i] = pinsAvg[i] * smoothingCo + pinReadingStorage[i] * 1-smoothingCo;
        
        //send midi
        sendMIDI(176, i+1, pinsAvg[i]/4);
        
        // light the LED
        digitalWrite(LED, HIGH);
        
        delay(1);     
        
       }//end if not same
    
    // if no change switch off the LED
     else{ digitalWrite(LED, LOW); 
     }
     
      
    }//end for pins
    
      
}//end loop


