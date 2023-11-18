#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=143.36000061035156,97.36000061035156
AudioOutputI2S           i2s1;           //xy=473.35998916625977,102.35999870300293
AudioConnection          patchCord1(i2s2, 0, i2s1, 0);
AudioConnection          patchCord2(i2s2, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=333.35999298095703,238.35999488830566
// GUItool: end automatically generated code
AudioSynthWaveformSine   sine1;


const int myInput = AUDIO_INPUT_LINEIN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(myInput);
  delay(1000);
}

void loop() {
}
