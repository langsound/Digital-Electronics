/*
This sketch allows for control of effects and playing of a 4-note sequence such that the tempo of the
sequence does not interupt the timing of the control change messages.

connect up to 8 pots with the code as is.  connecting them to analog inputs 0-7.



*/

// pots and assignment related variables
int numberOfNotes = 4;
int numberOfPots = 8;

// avereraging and storing of pot reading variables
int myPots[127];
int myOldPots[127];

//note and timing related variables.
int lastTime;
int nextPot;
int myDelay;
int notePlaying;
int myNote;


//set up and such
void setup(){
pinMode(13, OUTPUT);


}//end setup

/// functions we will be calling later

void readThemPots(){
 //read all the pots
     for(int i; i < numberOfPots; i++){
      myPots[i] = analogRead(i); 
     } 
}//end readThemPots

void getNextPot(){
   nextPot++;      
   if(nextPot >= numberOfNotes){
          nextPot = 0;
   } 
}   // end getNextPot     
  
  
  
// the actual loop  

void loop(){
 
 
 
 //send the notes
    
    readThemPots();
    
    myDelay = myPots[4]/10 + 50; 
    // myDelay = 250;
    if (millis() > (lastTime + myDelay)){
      
       lastTime = millis();
       
       
       if(notePlaying==1){
        usbMIDI.sendNoteOn(myNote, 0, 144);
        digitalWrite(13, LOW); 
        notePlaying = 0; 
        delay(2);
       }//if note one
       
       else{
         getNextPot();
          myNote = analogRead(nextPot)/16 + 24;
           
          usbMIDI.sendNoteOn(myNote, 127, 144);
          digitalWrite(13, HIGH);
          notePlaying = 1;
          delay(2);
       }//if note zero
       
      
    }  //if millis
    

    
    
  // send effects
    for(int i = 5; i<7; i++){
      readThemPots();
      
     if(myPots[i] != myOldPots[i]){ 
      myOldPots[i] = myPots[i]; 
     usbMIDI.sendControlChange(i, (myPots[i]/8), 177);
     digitalWrite(13, HIGH);
     delay(3);
     }
     else{digitalWrite(13, LOW); }
    }//end for i
   
    
}//end loop
