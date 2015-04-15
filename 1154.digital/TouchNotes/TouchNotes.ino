/* this program reads touch pins with generic code that could easily be modified
to work with traditional buttons, or even "analog" buttons souch as FSRs
works only on Teensy and other TouchRead capapble microcontrollers
requires no special libaries like the button bounce lib.

output is usb midi,  plays notes.  will work with most midi software.

*/
int myLED = 13;;
int myButtons[16];
int myOldButtons[16];
  
  
 // this is an array, its like a list, hashtable, vector, etc.
// its a named collection of number in this specic order. 
// change the numbers here to play different scales and such
int myNotes[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86} ;

// ThreshHold might need to change
int myTouchThreshold = 1000;

// there are only so many trouch pins
int numberOfButtons = 9;

// these are the touch pins (see the cheat sheet for confirmation)
int myTouchPins[] = { 0, 1, 15, 16,17,18,19,22,23};

// for now velosity is fixed
int myVelocity = 127;
// 144 = midi channel 1, might need to change this to 1.
int myChannel=144;


// this is a funtion,  we will define it here, the call it (ask it to do its thing later)
void readMyButtons(){
   //for loop
  for(int i; i<10; i++){
    
    // read all the touch pins into a array for use later
   myButtons[i] = touchRead(myTouchPins[i]);
   
   // lets decide if we want to say the pin is touched or not touched
   //  compair the capasitance valued read to the threshhold
  //  if its above the thresh hold,  we say 1, its touched
   if(myButtons[i] > myTouchThreshold){
     myButtons[i] = 1;
   }
   
   // esle, we say its zero, or not touched
   else{
     myButtons[i] = 0;
   }  
   
   // delays are important.  might talk about this later.
  delay(1);
 }  
}


// here is another function
void playMyNotes(){
  
  // for loops are sooo coool.  
  
 for(int i; i<9; i++){
  
  // if the button has changed, do something
   if(myButtons[i] != myOldButtons[i]){
        myOldButtons[i] = myButtons[i];
        
        // if the button is pressed,  play note on
        if(myButtons[i] ){
          usbMIDI.sendNoteOn(myNotes[i], myVelocity, myChannel);
          
          // light the LED
          digitalWrite(myLED, HIGH);
          //delay(1);
        }
        
        // if the note is not pressed, play note off
        else{
          usbMIDI.sendNoteOn(myNotes[i], 0, myChannel);
          
          // un-light the LED
          digitalWrite(myLED, LOW);
        }
    }
  }
}


// we may need to add some things here
void setup(){
  pinMode(myLED, OUTPUT);
  for(int i; i < 10; i++){
   digitalWrite(myLED, i%2);
   usbMIDI.sendNoteOn(48, 127, 145);
  delay(250); 
   usbMIDI.sendNoteOn(48, 0, 145);
  }
  digitalWrite(myLED, 0);
}


//  look at this loop.  two lines of code...
void loop(){
 readMyButtons();
 playMyNotes();
}  
