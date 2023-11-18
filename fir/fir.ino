#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=96.30768966674805,127.07692050933838
AudioFilterFIR           fir1;           //xy=285.53845977783203,84.76922416687012
AudioFilterFIR           fir2; //xy=285.5384635925293,155.5384693145752
AudioOutputI2S           i2s2;           //xy=505.5385437011719,124.76922798156738
AudioConnection          patchCord1(i2s1, 0, fir1, 0);
AudioConnection          patchCord2(i2s1, 0, fir2, 0);
AudioConnection          patchCord3(fir1, 0, i2s2, 0);
AudioConnection          patchCord4(fir2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=280.1538391113281,294.0000162124634
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;

struct fir_filter {
  short *coeffs;
  short num_coeffs;    // num_coeffs must be an even number, 4 or higher
};

struct fir_filter fir_list[] = {
  {low_pass , 100},    // low pass with cutoff at 1kHz and -60dB at 2kHz
  {high_pass, 100},    // bandpass 1200Hz - 1700Hz
  {NULL,      0}
};

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(0.8);

  fir1.begin(fir_list[0].coeffs, fir_list[0].num_coeffs);
  fir2.begin(fir_list[0].coeffs, fir_list[0].num_coeffs);

  Delay(10);
}

int fir_idx = -1;

void loop() {
  int knobA1 = analogRead(A1);
  int knobA2 = analogRead(A2);
  
  AudioNoInterrupt();
  if(knobA1 < 340){
    fir1.begin(fir_list[0].coeffs, fir_list[0].num_coeffs);
    fir2.begin(fir_list[0].coeffs, fir_list[0].num_coeffs);
  }
  else if(knobA1 > 340 && knobA1 < 680){
    fir1.begin(fir_list[1].coeffs, fir_list[1].num_coeffs);
    fir2.begin(fir_list[1].coeffs, fir_list[1].num_coeffs);
  }
  else{
    fir1.begin(fir_list[2].coeffs, fir_list[2].num_coeffs);
    fir2.begin(fir_list[2].coeffs, fir_list[2].num_coeffs);
  }
  AudioInterrupt();

}
