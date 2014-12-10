/* twelve tone synth  by Ranjit @ moonmilk
 * output 12 tones of scale (+ high C) to digital outs 1-13
 
 Modified for Teensy, added pins, changed notes to be somewhat pentatonic
 
 */



const int num = 25;        
int increment = 30;

// divisors for just intonation scale on 2, 3, and 5 <http://en.wikipedia.org/wiki/Just_intonation#The_twelve_tone_scale>
//              C       E      G        A      CC     E     F     G      A      C     E     F       G     A      CC     E     F     G      A      CC
 int tones[] = {23040, 36864,  15360,  11520,  9216, 7680, 1920,  6912,  5760, 4608, 4320,  3840,  3456,  2880,  2304, 2160, 1920,  1728,  1440, 1152, 1080, 960,864, 720, 576, 540, 480,432, 320};


//              C     Db    D     Eb    E     F     Gb     G     Ab   A     Bb     B,   CC
//int tones[] = {5760, 5400, 5120, 4800, 4608, 4320, 4050, 3840, 3600, 3456, 3240, 3072, 2880, 2700, 2560, 2400, 2304, 2160, 2025, 1920, 1800, 1728, 1620, 1536, 1440};
//              C     Db    D     Eb    E     F     F#     G     Ab   A     Bb     B,   CC
//int tones[] = {2880, 2700, 2560, 2400, 2304, 2160, 2048, 1920, 1800, 1728, 1620, 1536, 1440};
int pins[] = {1, 2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

int counters[num];
int states[num];

int analogSkip = 0;


void setup() {
  int i;
  for (i=0; i<num; i++) {
    pinMode(pins[i], OUTPUT);
    counters[i] = 0;
    states[i] = 0;
  } 
}

void loop() {
  int i, j;
  int t;
  /*
  if (++analogSkip > 5000) {
    i = analogRead(3);
    increment = 30 + (i-500)/50;
    
    //j = analogRead(4);
    
    analogSkip=0;
  }
  */
  
  for (i=0; i<num; i++) {
     if ((counters[i]+=increment) > tones[i]) {
       counters[i] -= tones[i];
       states[i] = !states[i];
       digitalWrite(pins[i], states[i]);
     }
  }
}
