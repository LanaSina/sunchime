/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9
int piezoPin = 12; //sound

//Variables
int value;          // Store value from photoresistor (0-1023)

void setup(){
 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)

 Serial.begin(9600);
}

void loop(){
  value = analogRead(pResistor);
  Serial.print("photocell value ");
  Serial.println(value);

  // piezo values between 2,000 and 5,000 
  // light value tends to be 5000>v<1000
  if (value > 800){
    digitalWrite(ledPin, LOW);  //Turn led off
  }
  else if (value > 700){
    tone(piezoPin, 1500, 300);
    delay(300);
  }
  else if (value > 600){
    tone(piezoPin, 4000, 300);
    delay(300);
   }
  else if (value >500){
    
    digitalWrite(ledPin, HIGH); //Turn led on

    /*Tone needs 2 arguments, but can take three
    1) Pin#
    2) Frequency - this is in hertz (cycles per second) which determines the pitch of the noise made
    3) Duration - how long teh tone plays
  */
    tone(piezoPin, 1000, 300);
    delay(300);
  }

  delay(500); //Small delay
}
