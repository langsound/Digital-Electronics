/* 


*/
int myLED = 13;;
int myButtons[16];
float myNewButtons[16];
int myOldButtons[16];
  
  
 // this is an array, its like a list, hashtable, vector, etc.
// its a named collection of number in this specic order. 
// change the numbers here to play different scales and such
int myNotes[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86} ;

// ThreshHolds might need to change
int myTouchThreshold_min = 775;
int myTouchThreshold_max = 900;

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
   myNewButtons[i] = touchRead(myTouchPins[i]);
  
    // map and constrain the range of values to 0-127
   myNewButtons[i]= constrain(map( myNewButtons[i], myTouchThreshold_min, myTouchThreshold_max, 0, 127), 0, 127);
   
   // smooth changes in sensor readings over several samples
   myButtons[i] =  myNewButtons[i] * 0.1 + myButtons[i] * 0.9;
  
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
        
         usbMIDI.sendControlChange(i+1, myButtons[i], 1);
        
       
    }    
        // if the note is not pressed, play note off
        else{
        
          
          // un-light the LED
          digitalWrite(myLED, LOW);
        }
    
  }
}


// we may need to add some things here
void setup(){
  pinMode(myLED, OUTPUT);
  for(int i; i < 10; i++){
   digitalWrite(myLED, i%2);
   usbMIDI.sendNoteOn(48, 127, 145);
  delay(125); 
   usbMIDI.sendNoteOn(48, 0, 145);
  }
  digitalWrite(myLED, 0);
  delay(5); 
}


//  look at this loop.  two lines of code...
void loop(){
 readMyButtons();
 playMyNotes();
}  
