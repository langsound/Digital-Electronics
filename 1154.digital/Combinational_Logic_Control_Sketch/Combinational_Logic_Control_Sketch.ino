/* send switch states as MIDI note messages.


*/

// decs and vars

int LED= 13;
int myPins[12];
int myOldPins[12];
int myNotes[] = {24, 31,   36,43,   48, 55,   60, 67,  72, 79, 84, 91, 96, 103};


//setup
void setup(){
  //set LED as source
  pinMode(LED, OUTPUT);
  
  // usb midi stuff
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  
  
  //set pins as drains
  for(int p; p<12; p++){
   pinMode(p, INPUT); 
  }
  

 //flash the led pin
  for( int i; i< 50; i++){
    digitalWrite(LED, HIGH);
    delay( 52 - i);
    digitalWrite(LED, LOW);
    delay( 52 - i);  
    }//end flash loop
}//end setup


// loop
void loop(){
    
   for(int p; p<12; p++){
   myPins[p] = digitalRead(p);
   
   
   if(myPins[p] != myOldPins[p]){
     
     myOldPins[p]= myPins[p];
     
      if(myPins[p]){
        usbMIDI.sendNoteOn(myNotes[p], 0, 144);
        digitalWrite(13, LOW); 
        delay(2);
       }//if myPins[p]
       
       else{
         
          usbMIDI.sendNoteOn(myNotes[p], 127, 144);
          digitalWrite(13, HIGH);
          delay(2);
          
       }//if not myPins[p]
     
  
   }//if !=
  

 }//end for p
 
 
 //recieving midi
 usbMIDI.read();
 
 
}//end loop


// specific actions when MIDI notes are read.
void OnNoteOn(byte channel, byte note, byte velocity)
{
  digitalWrite(LED, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(LED, LOW);
}

