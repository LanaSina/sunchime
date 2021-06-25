#include <Tone.h>

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9
int piezoPin = 12; //sound

//Variables
int value;          // Store value from photoresistor (0-1023)
int previous_value;

// sound in Hz (between 20 and 20K)
// not possible to generate tones lower than 31Hz
// max 65535
// pentatonic scale, C, D, E, G, 
int chime0 = 262; //c4
int chime1 = 294;
int chime2 = 330;
int chime3 = 392;
int chime4 = 523; //c5


Tone notePlayer[4];

void setup(){
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)

 Serial.begin(9600);
 value = analogRead(pResistor);


 notePlayer[0].begin(piezoPin);
 notePlayer[1].begin(piezoPin);
// notePlayer[2].begin(47);
// notePlayer[3].begin(49);


  //notePlayer[0].play(NOTE_C4,1000);
  notePlayer[1].play(NOTE_D4,1000);
}

void energy_chime(int diff){
  int chime_duration = 500;
  int pause_duration = 100;
  int sign = 1;
  if (diff < 0){
    sign = -1;
    diff = -diff;
  }

  //diff = 10*diff;
  int max_tones = 6;

  // more and more time between chimes
  while (diff>1 and max_tones>0){
    max_tones = max_tones-1;
    int actual_value = sign*diff;
    int rand_duration = random(30, chime_duration);
    int rand_pause = random(10, pause_duration*(6-max_tones));

    int energy_lost = random(50);
    diff = diff - energy_lost;
    
//    if (energy_lost>20){
//      tone(piezoPin, chime0, rand_duration);
//    } else if (energy_lost >15){
//      tone(piezoPin, chime1, rand_duration);
//    } else if (energy_lost >10){
//      tone(piezoPin, chime2, rand_duration);
//    } else if (energy_lost > 5){
//      tone(piezoPin, chime3, rand_duration);
//    } else if (energy_lost > 0){
//      tone(piezoPin, chime4, rand_duration);
//    } 
    delay(rand_duration+rand_pause);
  }
  
}

void loop(){
  previous_value = value;
  value = analogRead(pResistor);
  Serial.print("photocell value ");
  Serial.println(value);

  // light value tends to be 500>v<1000
  // probably between -500 and 500
  int difference = value - previous_value;
  Serial.print("difference ");
  Serial.println(difference);
//  if (abs(difference)>5){
//    energy_chime(difference);
//    delay(3000);
//  }



  delay(500); //Small delay
}
