/*
    analog read to MIDI continuous controller send.
    One pot is sent via to different midi CC messages.
    the first cc message is just scaled data
    the second cc message is scaled and smoothed data

*/
 


// change pwmSmooth here 
float pwmSmooth = 0.5;
float pwmOut;
 

 
void setup(){

}//endsetup
 
void loop(){
  
  // send analog read data scaled, 
   usbMIDI.sendControlChange(34, map(analogRead(0), 0, 1024, 0, 127), 1);
   
  //read analog pin zero, scale it, smooth it.
  pwmOut = map(analogRead(0), 0, 1024, 0, 127) * (1-pwmSmooth) + pwmOut * pwmSmooth;
 
  // send analog read data scaled and smoothed.
  // may need to convert pwmOut to integer... 
  usbMIDI.sendControlChange(55, pwmOut, 1);
 
 
  delay(10); // you may want to change this to something between 33 and 60...
 
}//endloop
