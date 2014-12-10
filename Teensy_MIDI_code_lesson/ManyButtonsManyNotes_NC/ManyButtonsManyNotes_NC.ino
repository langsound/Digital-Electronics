int myLED = 13;;
int myButtons[16];
int myOldButtons[16];
                 
int myNotes[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86} ;
int myVelocity = 127;
int myChannel=144;

void setup(){
  pinMode(myLED, OUTPUT);
  for(int i; i<16; i++){
  pinMode(i, INPUT);
  }
}

void loop(){
 for(int i; i<16; i++){
   myButtons[i] = digitalRead(i); 
   if(myButtons[i] != myOldButtons[i]){
        myOldButtons[i] = myButtons[i];
        
        if(myButtons[i]){
          usbMIDI.sendNoteOn(myNotes[i], myVelocity, 145);
          digitalWrite(myLED, HIGH);
          delay(1);
        }
        else{
          usbMIDI.sendNoteOn(myNotes[i], 0, 145);
          digitalWrite(myLED, LOW);
        }
    }
 } 
}  
