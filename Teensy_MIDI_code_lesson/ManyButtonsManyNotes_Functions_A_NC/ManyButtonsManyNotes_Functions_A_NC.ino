int myLED = 13;;
int myButtons[16];
int myOldButtons[16];
                 
int myNotes[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86} ;
int myVelocity = 127;
int myChannel=144;

void readMyButtons(){
 for(int i; i<16; i++){
   myButtons[i] = analogRead(i);
   if(myButtons[i] > 512){
     myButtons[i] = 1;
   }
   else{
     myButtons[i] = 0;
   }  
  delay(1);
 }  
}

void playMyNotes(){
 for(int i; i<16; i++){
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

void setup(){
  pinMode(myLED, OUTPUT);
}

void loop(){
 readMyButtons();
 playMyNotes();
}  
