/*
serial echo MIDI format test
use this sketch to test your serial connections.


*/

int myBaud = 19200;  //19200 for Serial, 31250 for spec MIDI
int clockOut =13; //LED on board

int incomingByte, midiStatus, note, vel, ccNumber, ccValue;


void setup() {
  //  Set baud 
  Serial.begin(myBaud);
    // blinker starts slow, then goes fast. 
    for (int i = 44; i >0; i--){
    digitalWrite(clockOut, (i % 2));
   delay( (i+i*i)/i); 
  
  }//end for loop (blinker)
}//end set up

void loop(){
  


/*--------------------------------------------------------------------------  */  
 //handel serial 
  if (Serial.available()) {     
    incomingByte = Serial.read();        
      
      if (incomingByte == 144){  // status message for midi note-on channel 1
        midiStatus = 144;
        delay(1);
        note = Serial.read();  
        delay(1);    
        vel =  Serial.read();   
        
      goMidi(midiStatus, note, vel);   //echo the serial input to the output
     }//end if status144
     
     
     if (incomingByte == 176){
        midiStatus = 176;
        delay(1);
        ccNumber = Serial.read();  
        delay(1);    
        ccValue =  Serial.read();   
        
      goMidi(midiStatus, ccNumber, ccValue);  //echo the serial input to the output
     }//end if status176
     
  }//end if serial
  
/*--------------------------------------------------------------------------- */







 delay(1); 
}//end main loop


/*---------------------------------------------------------------------------  */


  // this is a function called in the main loop, but defined down here.
 //  it sends serial data in the byte format of a midi message, 

void goMidi(int cmd, int data1, int data2) {
  Serial.write(cmd);
  Serial.write(data1);
  Serial.write(data2);
  delay(2);
  
} //end void goMidi

/*----------------------------------------------------------------------------*/  

//*/
