
int myLED = 13;

int myPots[10];
int myOldPots[10];
int myAveragePots[10];

void setup(){
 pinMode(myLED, OUTPUT);
  //add some flashing lights 
}

void loop(){
 
 for(int i; i<10; i++){
  
   myPots[i] = analogRead(i)/8;
   myAveragePots[i] = (myAveragePots[i] * 0.5) + (myPots[i] * 0.5);
   
   if(myAveragePots[i] != myOldPots[i]){
     myOldPots[i] = myAveragePots[i];
     digitalWrite(myLED, HIGH);
     usbMIDI.sendControlChange( i, myAveragePots[i], 177);  
     delay(3);
     }
    else{
     digitalWrite(myLED, LOW); 
    }
   
 } 
  
  
}


