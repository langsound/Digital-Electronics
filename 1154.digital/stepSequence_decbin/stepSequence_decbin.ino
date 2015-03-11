
int led = 13; //light it up

// upper case variables for pin numbers
const int S0 = 12,
          S1 = 11,
          S2 = 10,
          S3 = 9,
          oscGate = 8;
// these veriables are also names after the thing they connect to.
//  S0-S3 connect to mux pins of same name
// oscGate connects to pin 4 on the 7555,
// when oscGate is high the 7555 oscilates, when low, silence.




void setup() {
  
  // initialize output pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(oscGate, OUTPUT);
  pinMode(led, OUTPUT);

 // start the oscilator
 digitalWrite(oscGate, HIGH); 
   
  // lightshow fast-to-slow
  for (int k = 10; k < 40; k++) {
    digitalWrite(led, HIGH);
    delay(k);
    digitalWrite(led, LOW);
    delay(k);
  }
  
  // stop the oscilator until something happens later.
   digitalWrite(oscGate, LOW);
 
 
 // set these so something happens when usbMIDI funcitons are called
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}


void loop() {


 //recieving midi
 usbMIDI.read();
  
}//end loop




// specific actions when MIDI notes are read.
void OnNoteOn(byte channel, byte note, byte velocity)
{
  digitalWrite(led, HIGH);
  digitalWrite(oscGate, HIGH);
  digitalWrite(S0, ct & 1);
  digitalWrite(S1, ct & 2 );
  digitalWrite(S2, ct & 4 );
  digitalWrite(S3, ct & 8 );
  
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(oscGate, LOW);
  digitalWrite(led, LOW);
}

  
