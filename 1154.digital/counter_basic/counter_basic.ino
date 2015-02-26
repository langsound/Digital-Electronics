

/*
  Counting up and down.  this code mimics the behavior of a 4bit counter.
  external clock may be used, or MIDI note 13 can control the clock
  caw, lcc, 
 */
  
// clock stuff
int clk = LOW;
int ctr = 0;
int led = 13;  // also clock pin out
  
// counter stuff
// upper case variables for pin numbers
const int CPU = 15,
          CPD = 14,
          RESET = 16,
          PAUSE = 17,
          Q0 = 12,
          Q1 = 11,
          Q2 = 10,
          Q3 = 9;
  
// lower case variables for input values & triggers
boolean pause, reset, cpu, cpd, up, dn;
  
// maximum counter value
const int MAXCOUNT = 15;
  
void myCount(int mode) {
  static int ct = 0;
  
  switch (mode) {
    case RESET:  // reset
      if (ct == 0)
        return;
      ct = 0;
      break;
    case CPU:  // count up
      if (++ct > MAXCOUNT)
        ct = 0;
      break;
    case CPD:  // count down
      if (--ct < 0)
        ct = MAXCOUNT;
      break;
  }
  
  digitalWrite(Q0, ct & 1 ? HIGH : LOW);
  digitalWrite(Q1, ct & 2 ? HIGH : LOW);
  digitalWrite(Q2, ct & 4 ? HIGH : LOW);
  digitalWrite(Q3, ct & 8 ? HIGH : LOW);
}
  
void setup() {
  
  // initialize output pins
  pinMode(Q0, OUTPUT);
  pinMode(Q1, OUTPUT);
  pinMode(Q2, OUTPUT);
  pinMode(Q3, OUTPUT);
  pinMode(led, OUTPUT);
 // teensy users,  input pins must be initialized
  pinMode(CPU, INPUT);
  pinMode(CPD, INPUT);
  pinMode(RESET, INPUT);
  pinMode(PAUSE, INPUT);
   
  // lightshow now shorter
  for (int k = 40; k > 10; k--) {
    digitalWrite(led, HIGH);
    delay(k);
    digitalWrite(led, LOW);
    delay(k);
  }
  
  cpu = digitalRead(CPU) == HIGH;
  cpd = digitalRead(CPD) == HIGH;
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}
  
void loop() {
  
  // for stability, read inputs first before changing any outputs
  
  // either count up or count down triggers when the clock input goes from
  // low to high and the other clock input was and still is high
  up = cpd && !cpu;  // cpu was low, cpd was high -> up may trigger
  dn = cpu && !cpd;  // cpd was low, cpu was high -> down may trigger
  
  reset = digitalRead(RESET) == LOW;
  cpu   = digitalRead(CPU) == HIGH;
  cpd   = digitalRead(CPD) == HIGH;
  
  if (reset)
    myCount(RESET);
  else if ((up || dn) && cpu && cpd &&
           digitalRead(PAUSE) == HIGH)
    myCount(up ? CPU : CPD);
  
 
 //recieving midi
 usbMIDI.read();
  
}//end loop


// specific actions when MIDI notes are read.
void OnNoteOn(byte channel, byte note, byte velocity)
{
  //contrain is used to prevent other notes from switching LEDs
  digitalWrite(constrain(note,5,13), HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(constrain(note,5,13), LOW);
}




