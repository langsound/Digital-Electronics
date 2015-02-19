/* send switch states as MIDI note messages.
   send midi notes as switch states to LEDs

*/

// decs and vars

int myPins[12];
int myOldPins[12];
int myNotes[] = {24, 31,   36,43,   48, 55,   60, 67,  72, 79, 84, 91, 96, 103};


//setup
void setup(){
  //setinput and output pins
    //inputs pins 13-20
  for(int p=14; p<22; p++){
   pinMode(p, INPUT); 
  } 
  
     //output pins 5-12
  for(int p=5; p<13; p++){
   pinMode(p, OUTPUT); 
  } 
  
  // usb midi stuff
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  
  

  

 //flash the led pins
  for( int i=5; i< 13; i++){
    digitalWrite(i, HIGH);
    delay(50);
    digitalWrite(i, LOW);
    delay(50);     
    }//end flash loop
}//end setup


// loop
void loop(){
    
   for(int p; p<12; p++){
   myPins[p] = digitalRead(p+14);
   
   
   if(myPins[p] != myOldPins[p]){
     
     myOldPins[p]= myPins[p];
     
      if(myPins[p]){
        usbMIDI.sendNoteOn(myNotes[p], 127, 144);
        digitalWrite(13, LOW); 
        delay(2);
       }//if myPins[p]
       
       else{
         
          usbMIDI.sendNoteOn(myNotes[p], 0, 144);
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
  //contrain is used to prevent other notes from switching LEDs
  digitalWrite(constrain(note,5,12), HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(constrain(note,5,12), LOW);
}

