#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=106.30768585205078,114.76922416687012
AudioAnalyzeFFT1024      fft1024_1;      //xy=334.0000190734863,222.46152877807617
AudioOutputI2S           i2s2;           //xy=436.30776023864746,123.99999809265137
AudioConnection          patchCord1(waveform1, 0, i2s2, 0);
AudioConnection          patchCord2(waveform1, 0, i2s2, 1);
AudioConnection          patchCord3(waveform1, fft1024_1);
AudioControlSGTL5000     sgtl5000_1;     //xy=272.4615173339844,336.30769443511963
// GUItool: end automatically generated code


void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  waveform1.frequency(440);
  waveform1.amplitude(1.0);
  waveform1.begin(WAVEFORM_SINE);
  
  delay(100);

}

void loop() {

  float knobA2 = (float)analogRead(A2) / 1023.0;

  AudioNoInterrupts();
  waveform1.frequency(100.0 + knobA2 * 900.0); 
  AudioInterrupts();

  if (fft1024_1.available()) {
    
    Serial.print("FFT: ");
    for (int i=0; i<30; i++) {  
      float n = fft1024_1.read(i);
      printNumber(n);
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