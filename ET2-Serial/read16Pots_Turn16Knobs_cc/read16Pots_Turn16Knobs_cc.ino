/* this program reads a bunch of analog sensors and sends serial or midi data 
// please notice the variable names were selected for a program that used only 
buttons and notes.
With only a few changes, the code now sends continuous controller values.

*/

// declarations of variables and stuff
int notes[] = { 60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 96}
int myBaud = 19200;  // serial for max patch,  spec MIDI 31250

int buttonCount = 16;
int muxS0 = 5; // the arduino digital pin number connected to mux S0...
int muxS1 = 6; // the arduino digital pin number connected to mux S1...
int muxS2 = 7; // the arduino digital pin number connected to mux S2...
int muxS3 = 8; // the arduino digital pin number connected to mux S3...
int sigPin = 0; // the arduino analog pin number connected ot the mux SIG pin
int buttons[buttonCount];
int buttons_old[buttonCount];
int vel = 127;
int statusByte = 176;// 176 is cc status byte for channel 1

void setup(){
  Serial.begin(myBaud);
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  pinMode(sigPin, INPUT);
  
  
}//end setup

void loop(){
  
 // Read if button pressed…
 for(int i; i< buttonCount; i++;){
  // Set mux channel one after the other
  setMuxChannel(i); 
  // measure channel one after the other and store them
  buttons[i] = analogRead(sigPin) / 4; 
  //buttons[i + muxOffSet] = digitalRead(otherSigPin);
 }//end read buttons
  
 
// maybe add analog read, assign to vel? 
 
 
  //DO something  
for(int i; i< buttonCount; i++;){
     //IF button state changes, do something
     if(buttons[i] != buttons_old[i]){
       
         buttons_old[i] = buttons[i];
         
         sendMIDI(statusByte, notes[i], buttons[i]);         
         
     }//end if not old
   
  
}//end Do something 
  
  
  
}//end loop


   


void sendMIDI(int statusByte, int Data1, int Data2){
  Serial.write(statusByte);   //midi status byte
  Serial.write(Data1);        //cc number or note number
  Serial.write(Data2);        //cc data or note velocity
  
}//end void sendMIDI



void setMuxChannel(int channelNumber){
  digitalWrite(muxS0, channelNumber & 1);  // dec to binary conversion for 1s place
  digitalWrite(muxS1, channelNumber & 2);
  digitalWrite(muxS2, channelNumber & 4);
  digitalWrite(muxS3, channelNumber & 8);
  
}//end setMuxChannel






















