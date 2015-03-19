/*     Digital Analog Conversion
       Bin to MIDI, DEC to PWM.

*/
// decs and vars

int myPins[12];
int myOldPins[12];
int myNotes[] = {24, 31,   36,43,   48, 55,   60, 67,  72, 79, 84, 91, 96, 103};
int led = 13;
int myGate = 9;  
int myPWM =  10;
// pwm capable pins: 3, 4, 5, 6, 9, 10, 20, 21, 22, 23, 25, 32



void setup() {
  // initialize input pins (14-21)
  for(int i=14; i<22; i++){
  pinMode(i, INPUT);
  }
  
  
  // initialize output pins
  pinMode(myPWM, OUTPUT);
  pinMode(myGate, OUTPUT);
  pinMode(led, OUTPUT);


 digitalWrite(myGate, HIGH); 
   
  // lightshow fast-to-slow
  for (int j = 2; j < 32; j++) {
    digitalWrite(led, HIGH);
    delay(2*j*2);
    analogWrite(myPWM, j*8);
    digitalWrite(led, LOW);
    delay(j*4);
  }//end lightshow
  
  
   digitalWrite(myGate, LOW);
   analogWrite(myPWM, 0);
 
 // set these so something happens when usbMIDI funcitons are called
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}//end setup




// loop
void loop(){
    
  //read 12 pins starting from pin 14
   for(int p; p<12; p++){
   myPins[p] = digitalRead(p+14);
   
   //if the state of the pin (button pressed, etc) has changed, do something
   // note, you could use rising/falling edge for buttons...
   // this code is reusible, it works for both discrete and continuous inputs
   if(myPins[p] != myOldPins[p]){
     
     myOldPins[p]= myPins[p];
     digitalWrite(led, HIGH); 
     
      if(myPins[p]){
        // if the pin has changed to high, set the note on
        usbMIDI.sendNoteOn(myNotes[p], 127, 144);
        delay(2);
       }//if myPins[p]
       
       else{
         // otherwise, set the note off (velocity zero)
          usbMIDI.sendNoteOn(myNotes[p], 0, 144);
          delay(2);
          
       }//if not myPins[p]
     
  
   }//if !=
   
   //else (if the pin state has not changed) do some other thing.
   else{
     digitalWrite(led, LOW); 
   }

 }//end for p
 
 
 //recieving midi
 usbMIDI.read();
 
 
}//end loop


// specific actions when MIDI notes are read.
void OnNoteOn(byte channel, byte note, byte velocity)
{
  // mapping will likely be needed to produce satisfactory results
  // format, replace "note * 2" with the following: "(map(note, 60, 240))" ommiting the quotes
  // change the mapped min "60" and mapped max "240" as needed
  analogWrite(myPWM, note * 2);
  digitalWrite(myGate, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(myGate, LOW);
}

