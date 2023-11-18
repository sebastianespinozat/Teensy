#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=137.07692072941703,96.30768996018628
AudioSynthNoiseWhite     noise1;         //xy=162.4615361140324,179.38461303710935
AudioMixer4              mixer1;         //xy=313.2307662963867,113.2308120727539
AudioAnalyzeFFT256       fft256_1;       //xy=440.9230745755708,673.9999976524939
AudioAnalyzeFFT1024      fft1024_1;      //xy=460.9230745755708,769.3846130371093
AudioOutputI2S           i2s2;           //xy=621.6155281066895,119
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(noise1, 0, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, i2s2, 0);
AudioConnection          patchCord4(mixer1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=400.3077087402344,269.6153841018677
// GUItool: end automatically generated code




void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(1.0);
  noise1.amplitude(0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 0.0);
  mixer1.gain(2, 0);
  mixer1.gain(3, 0);


}

void loop() {

  float knobA2 = (float)analogRead(A2) / 1023.0;
  float knobA1 = (float)analogRead(A1) / 1023.0;

  AudioNoInterrupts();
  waveform1.frequency(100.0 + knobA2 * 900.0); 
  mixer1.gain(1, knobA1);
  AudioInterrupts();

}
