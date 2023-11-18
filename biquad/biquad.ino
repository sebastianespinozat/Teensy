#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=96.30768966674805,127.07692050933838
AudioFilterBiquad        biquad1;        //xy=279.3845977783203,127.07691669464111
AudioOutputI2S           i2s2;           //xy=505.5385437011719,124.76922798156738
AudioConnection          patchCord1(i2s1, 0, biquad1, 0);
AudioConnection          patchCord2(biquad1, 0, i2s2, 0);
AudioConnection          patchCord3(biquad1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=280.1538391113281,294.0000162124634
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;

void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();  // Enable the audio shield
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);

  biquad1.setLowpass(0, 800, 0.707);
}

void loop() {
  int knobA1 = analogRead(A1);
  int knobA2 = analogRead(A2);

  AudioNoInterrupts();
  if (knobA1 > 510){
    biquad1.setLowpass(0, 800, 0.707);
  }
  else if(knobA1 < 510) {
    biquad1.setLowpass(0, 800, 0.54);
    biquad1.setLowpass(1, 800, 1.3);
    biquad1.setLowpass(2, 800, 0.54);
  }

  if (knobA2 > 510){
    biquad1.setHighpass(0, 800, 0.707);
  }
  else if(knobA2 < 510) {
    biquad1.setHighpass(0, 800, 0.54);
    biquad1.setHighpass(1, 800, 1.3);
    biquad1.setHighpass(2, 800, 0.54);
  }
  AudioInterrupts();
}
