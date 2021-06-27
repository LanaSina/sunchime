#include <PCM.h>
#include "sounddata.h"

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9
//int piezoPin = 12; //sound

//Variables
int value;          // Store value from photoresistor (0-1023)
int previous_value;


void setup(){
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)

 Serial.begin(9600);
 value = analogRead(pResistor);

  Serial.println(sizeof(chime0));
  Serial.println(sizeof(chime1));
  Serial.println(sizeof(chime2));
}

// chime order could be generated during idle time 
void generate_knock(int energy){
   
  Serial.println("generate ");
  int n_chimes = 3;
  int chime_length = 400; //ms, length of prestored chimes
  
  // random durations between chime knocks
  int knocks = 4;
  int dist[] = {0,0,0,0};
  int chime_seq[] = {-1,-1,-1,-1};
  // can be truncated if same chime hit 2x
  int truncated_durations[] = {chime_length,chime_length,chime_length,chime_length};
  int max_duration = 0;
  int sum_dist = 0;

  // number of knocks
  for (int i=0; i<knocks; i++){
    //1st start will always be 0
    if(i>0){
        //min delay = 100 ms
        int rand_dist = random(i*200) + 100;
        sum_dist = sum_dist + rand_dist;
        dist[i] = sum_dist;
    }

    chime_seq[i] = random(3);
  }

  //interrupt chime if it knocked 2x
  for (int i=0; i<knocks; i++){
    for (int j=i; j<4; j++){
      if (j != i){
        if (chime_seq[j] == chime_seq[i]){
            truncated_durations[i] = min(chime_length, dist[j]-dist[i]);
            //necessary to avoid bad overwrite
            break;
        }
      }
    }
  }

  max_duration = sum_dist+chime_length;

  // now make the sound array
  int sample_rate = 16000;
  int num_samples = max_duration * (sample_rate / 1000.0);
  unsigned char audio_int[num_samples] PROGMEM;
  unsigned char audio_char[num_samples];
  int chime_samples = chime_length*(sample_rate / 1000.0);
  
  int  max_volume = 0;
  for (int x=0; x<num_samples; x++){
      int value = 0;

      for (int chime_n=0; chime_n<knocks; chime_n++){
//        const unsigned char (*chime)[6400];
//        if (chime_n == 0){
//          chime = &chime0;
//        } else if (chime_n == 1) {
//          chime = &chime1;
//        } else if (chime_n ==2){
//          chime = &chime2;
//        }
      
        int chime_start_time = dist[chime_n] * (sample_rate / 1000.0);
        int chime_end_time = (dist[chime_n] + truncated_durations[chime_n]) * (sample_rate / 1000.0);
  
        // if this chime is on, add values to array
        if(x > chime_start_time){
          if (x < chime_end_time){
            value = value + chime0[x]; //*chime[x];
          }
        }
      }

      if (value > max_volume){
        max_volume = value;
      }

      //audio_int[x] = (unsigned char) 0;// value;
  }


  for (int x=0; x<num_samples; x++){
    if (x<6400){
      //chime0[x]; //(value/max_volume);
      //audio_char[x] = chime0[x]; 
      int a = 0;
    }
  }

  startPlayback(chime1, 6400);  
  Serial.println("played ");
}

void generate_knock_2(int energy){
  int n_chimes = 3;
  int knocks = 4;
  int chime_length = 400; //ms, length of prestored chimes
  int durations[] = {chime_length,chime_length,chime_length,chime_length};

  // number of knocks
  int min_delay = 410;
  
  for (int i=0; i<knocks; i++){
    int chime_n = random(n_chimes);
    if (chime_n == 0){
      startPlayback(chime0, 6400);
    } else if (chime_n == 1) {
      startPlayback(chime1, 6400);
    } else if (chime_n ==2){
      startPlayback(chime2, 6400);
    }  

    int rand_dist = random(300) + i*150 ;
    delay(rand_dist);
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
  if (abs(difference)>10){
    generate_knock_2(difference);
    delay(2000);
  }

  delay(500); //Small delay
}
