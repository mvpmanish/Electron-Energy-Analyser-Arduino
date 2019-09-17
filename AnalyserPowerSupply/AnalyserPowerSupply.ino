#include "AD9850.h"
#include "Encoder.h"
#include "MilliTimer.h"
#include "SerialChecker.h"

//// AD9850 Signal Generator Settings
const uint8_t w_clk = 39;
const uint8_t fq_ud = 38;
const uint8_t dataPin = 41;
const float freq = 14000;
AD9850 sigGen(w_clk, fq_ud, dataPin);

//// Rotary Encoder Settings
Encoder encs[8];
// rates - how many dac bits to increment or decrement the DAC voltages by
const uint8_t rate1 = 1;
const uint8_t rate2 = 10;
const uint8_t rate3 = 100;
// pins
const uint8_t enc0PinA = 21;
const uint8_t enc0PinB = 20;
const uint8_t enc1PinA = 19;
const uint8_t enc1PinB = 18;
const uint8_t enc2PinA = 17;
const uint8_t enc2PinB = 16;
const uint8_t enc3PinA = 14;
const uint8_t enc3PinB = 15;
const uint8_t enc4PinA = 11;
const uint8_t enc4PinB = 10;
const uint8_t enc5PinA = 9;
const uint8_t enc5PinB = 8;
const uint8_t enc6PinA = 7;
const uint8_t enc6PinB = 6;
const uint8_t enc7PinA = 5;
const uint8_t enc7PinB = 4;

//// DAC Settings and Voltages
uint16_t volts[14] = 0; // Initialise all voltages to zero. 

//// Serial Settings
SerialChecker sc;  //Defaults the baud rate to 250000

void setup(){
  sigGen.setfreq(freq);
  
  // setup serial checker
  sc.init();
  sc.enableACKNAK();
  sc.enableChecksum();
  
  // init encoders
  encs[0].init(enc0PinA, enc0PinB);
  encs[1].init(enc1PinA, enc1PinB);
  encs[2].init(enc2PinA, enc2PinB);
  encs[3].init(enc3PinA, enc3PinB);
  encs[4].init(enc4PinA, enc4PinB);
  encs[5].init(enc5PinA, enc5PinB);
  encs[6].init(enc6PinA, enc6PinB);
  encs[7].init(enc7PinA, enc7PinB);
}

void loop(){
  checkEncoders();
  checkSerial();
}

void checkEncoders(){
  for(uint8_t i = 0; i < 8; i++){
    switch(enc.poll()){
      case NO_CHANGE:
        break;
      case CW_RATE1: 
        
        break;
      case CW_RATE2:
        
        break;
      case CW_RATE3: 
        
        break;
      case ACW_RATE1: 
        
        break;
      case ACW_RATE2: 
        
        break;
      case ACW_RATE3: 
        
        break;
    }
  }
}

void checkSerial(){
  if(sc.check()){
    if(sc.contains("SV")){
      // Setting a voltage
      if(sc.contains("RE", 2)){
        // Set residual energy

      }
      else if(sc.contains("LE", 2)){
        // Set lens
        
      }
      else if(sc.contains("DX", 2)){
        // Set deflector X
        
      }
      else if(sc.contains("DY", 2)){
        // Set deflector Y
        
      }
      else if(sc.contains("AM", 2)){
        // Set analyser mean
        
      }
      else if(sc.contains("IH", 2)){
        // Set inner hemisphere
        
      }
      else if(sc.contains("OH", 2)){
        // Set outer hemisphere
        
      }

    }
  }
}

void resetCalibration(){

}