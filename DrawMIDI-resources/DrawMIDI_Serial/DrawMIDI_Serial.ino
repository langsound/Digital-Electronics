
// drawMIDI



int myKey[12];
int myOldKey[12];
int myNote[] = {79, 77, 76, 72, 74, 71, 69, 67, 65, 64, 62, 60};
int keyPin[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};


// Pins for MIDI keys


// This is the value required to consider the key 'touched' and trigger a MIDI signal
int touchedCutoff = 36;

// This is the value required for the first part of goMIDI
int midiInfo = 144;


// This is the section that sets up serial communications
void setup(){
  Serial.begin(19200); //if using hardward MIDI or HIDUINO, change to 31250  
  //19200 baud, requires serial to MIDI conversion on your computer
  
}


// This is the section that reads the capacitance and determines what to do, noteOn or noteOff
void loop(){
  
  

// only send MIDI messages when something changes
for (int i; i<12; i++) {
  myKey[i]=readCapacitivePin(keyPin[i]);
  
  if (myKey[i]>touchedCutoff){
    myKey[i]=127;
  }
  else{
    myKey[i]=0;
  }
  
  
  if (myKey[i] != myOldKey[i]) {
    myOldKey[i] = myKey[i];
    goMidi(midiInfo, myNote[i], myKey[i]);
  }
}
}




// The readCapacitivePin function is used to read whether the graphite strip connected to each pin is actually being pressed or not
// this part of the code is based on an open example on the Arduino playground for 'Capacitive Sensing' 

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//          how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher

uint8_t readCapacitivePin(int pinToMeasure){
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  
  *ddr &= ~(bitmask);

  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  
  return cycles;
}


 
 
// This is the section that translates the touches into MIDI signals
 
void goMidi(int cmd, int data1, int data2) {
  Serial.write(cmd); // set value stays the same
  Serial.write(data1);  // note number, 60 or 49 or whatever
  Serial.write(data2); // velocity, keep at 127 for ON or 0 for OFF
  delay(2);
} 
 



