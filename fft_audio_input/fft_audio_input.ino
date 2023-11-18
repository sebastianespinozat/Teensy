#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=96.30768966674805,127.07692050933838
AudioFilterStateVariable filter1;        //xy=239.38458251953125,132.4615879058838
AudioMixer4              mixer1;         //xy=382.4615478515625,137.84613800048828
AudioOutputI2S           i2s2;           //xy=534.0001068115234,135.53846740722656
AudioAnalyzeFFT1024      fft1024_1;      //xy=550.9231033325195,198.6154327392578
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, mixer1, 0);
AudioConnection          patchCord3(filter1, 1, mixer1, 1);
AudioConnection          patchCord4(filter1, 2, mixer1, 2);
AudioConnection          patchCord5(mixer1, 0, i2s2, 0);
AudioConnection          patchCord6(mixer1, 0, i2s2, 1);
AudioConnection          patchCord7(mixer1, fft1024_1);
AudioControlSGTL5000     sgtl5000_1;     //xy=280.1538391113281,294.0000162124634
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;
int led1 = 4;
int led2 = 5;
int led3 = 6;
void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  sgtl5000_1.inputSelect(myInput);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 0);
  mixer1.gain(2, 0.0);
  mixer1.gain(3, 0.0);

  Delay(100);
}

void loop() {

  int knobA2 = analogRead(A2);
  int knobA1 = analogRead(A1);

  
  AudioNoInterrupts();
  if (knobA1 <= 341){
    mixer1.gain(0, 1.0);
    mixer1.gain(1, 0);
    mixer1.gain(2, 0.0);
    mixer1.gain(3, 0.0);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  else if (knobA1 > 341 && knobA1 < 682){
    mixer1.gain(0, 0);
    mixer1.gain(1, 1.0);
    mixer1.gain(2, 0.0);
    mixer1.gain(3, 0.0);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  else {
    mixer1.gain(0, 0);
    mixer1.gain(1, 0);
    mixer1.gain(2, 1.0);
    mixer1.gain(3, 0.0);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  AudioInterrupts();
  
  if (fft1024_1.available()) {
    
    Serial.print("FFT: ");
    for (int i=0; i<30; i++) {  
      float n = fft1024_1.read(i);
      printNumber(n);
    }
    Serial.println();
  }

}

void printNumber(float n) {
  
  if (n >= 0.004) {
    Serial.print(n, 3);
    Serial.print(" ");
  } else {
    Serial.print("   -  "); // don't print "0.00"
  }
  
}