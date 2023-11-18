#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


int led = 6;
// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=234,139
AudioAnalyzeFFT1024      fft1024_1;      //xy=423,258
AudioOutputI2S           i2s2;           //xy=652,136
AudioConnection          patchCord1(i2s1, 0, i2s2, 0);
AudioConnection          patchCord2(i2s1, 0, fft1024_1, 0);
AudioConnection          patchCord3(i2s1, 1, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=369,390
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);
  AudioMemory(30);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  pinMode(led, OUTPUT);
}

void loop() {

  if (fft1024_1.available()) {
    
    Serial.print("FFT: ");
    for (int i=0; i<10; i++) {  // 0-10  -->  DC to 390 kHz app
      float n = fft1024_1.read(i);
      printNumber(n);
      if(n > 0.1 && (i >= 1 && i <=8)){
        digitalWrite(led, HIGH);
      }
      else{
        digitalWrite(led, LOW);
      }

    }
    Serial.println();
  }

  delay(10);
}




void printNumber(float n) {
  
  if (n >= 0.004) {
    Serial.print(n, 3);
    Serial.print(" ");
  } else {
    Serial.print("   -  "); // don't print "0.00"
  }
  
}


