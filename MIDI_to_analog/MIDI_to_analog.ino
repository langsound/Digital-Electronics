// USB MIDI receive to control astable oscilator.
//connect digital pin 3 to pin 5 of your astable oscillator via a lowpass filter
 // example: LPF 220Ω resistor in series,  1.0µF cap to ground
//connect digital pin 4 to pin 4 of our astable oscillator

int notePin = 3;
int gatePin = 4;

void OnNoteOn(byte channel, byte note, byte velocity)
{
  analogWrite(notePin, 255-note);
  digitalWrite(gatePin, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(notePin, LOW);
  digitalWrite(gatePin, LOW);
}

void setup()
{
  pinMode(notePin, OUTPUT);
  pinMode(gatePin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  digitalWrite(notePin, HIGH);
  delay(1000);
  digitalWrite(notePin, LOW);
  delay(1000);
}

void loop()
{
  usbMIDI.read();
}
