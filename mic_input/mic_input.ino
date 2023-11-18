 #include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=226.36000442504883,92.3600025177002
AudioOutputI2S           i2s1;           //xy=479.9635066986084,94.14541435241699
AudioConnection          patchCord1(i2s2, 0, i2s1, 0);
AudioConnection          patchCord2(i2s2, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=341.6909408569336,179.32725715637207
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  digitalWrite(13,LOW);
}

void loop() {
}
