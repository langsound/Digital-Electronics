int myLED = 13;
int myButton;
int myOldButton;

int myNote = 60;
int myVelocity = 127;
int myChannel=144;

void setup(){
  pinMode(myLED, OUTPUT);
  pinMode(myLED, INPUT);
  
}

void loop(){
 myButton = digitalRead(0); 
 if(myButton != myOldButton){
      myOldButton = myButton;
      
      if(myButton){
        usbMIDI.sendNoteOn(myNote, myVelocity, 145);
        digitalWrite(myLED, HIGH);
        delay(1);
      }
      else{
        usbMIDI.sendNoteOn(myNote, 0, 145);
        digitalWrite(myLED, LOW);
      }
  }
}  
