/* this program reads a bunch of analog sensors and sends serial or midi data 


*/

// declarations of variables and stuff

int myBaud = 19200;  // serial for max patch,  spec MIDI 31250

int sensorCount = 4;

int readings[4];
int readings_old[4];

int statusByte = 176;// 176 is cc status byte for channel 1

void setup(){
  Serial.begin(myBaud);

  
  
}//end setup

void loop(){
  

  //DO something  
for(int i; i< sensorCount; i++){
     readings[i] = analogRead(i)/4; 
     //IF button state changes, do something
     if(readings[i] != readings_old[i]){
       
         readings_old[i] = readings[i];
         
         sendMIDI(statusByte, i, readings[i]);         
         
     }//end if not old
   
  
}//end Do something 
  
  
  
}//end loop


   


void sendMIDI(int statusByte, int Data1, int Data2){
  Serial.write(statusByte);   //midi status byte
  Serial.write(Data1);        //cc number or note number
  Serial.write(Data2);        //cc data or note velocity
  
}//end void sendMIDI
























