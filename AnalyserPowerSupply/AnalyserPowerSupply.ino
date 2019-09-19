#include "AD9850.h"
#include "Encoder.h"
#include "MilliTimer.h"
#include "SerialChecker.h"
#include "MCP4822.h"
#include "AnalyserClass.h"



Analyser Analyser1(1);
Analyser Analyser2(2);

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



//// Serial Settings
SerialChecker sc;  //Defaults the baud rate to 250000

void setup(){

  Analyser1.init();
  Analyser2.init();

  sigGen.setfreq(freq);
  
  // setup serial checker
  sc.init();
  sc.enableACKNAK();
  // sc.enableChecksum();
  

  // init encoders
  encs[0].init(enc0PinA, enc0PinB); // A1RE
  encs[1].init(enc1PinA, enc1PinB); // A1LE
  encs[2].init(enc2PinA, enc2PinB); // A1DX
  encs[3].init(enc3PinA, enc3PinB); // A1DY
  encs[4].init(enc4PinA, enc4PinB); // A2RE
  encs[5].init(enc5PinA, enc5PinB); // A2LE
  encs[6].init(enc6PinA, enc6PinB); // A2DX
  encs[7].init(enc7PinA, enc7PinB); // A2DY
  for(uint8_t i = 0; i < 8; i++){
    encs[i].setReversedDirection(true);
  }
}

void loop(){
  checkEncoders();
  checkSerial();
}


void checkEncoders(){
  for(uint8_t i = 0; i < 8; i++){
    int8_t value = 0;
    switch(encs[i].poll()){
      case NO_CHANGE:
        break;
      case CW_RATE1: 
        // Serial.print(i);
        // Serial.println(": CW_RATE1");
        value = rate1;
        break;
      case CW_RATE2:
        // Serial.print(i);
        // Serial.println(": CW_RATE2");
        value = rate2;
        break;
      case CW_RATE3: 
        // Serial.print(i);
        // Serial.println(": CW_RATE3");        
        value = rate3;
        break;
      case ACW_RATE1: 
        // Serial.print(i);
        // Serial.println(": ACW_RATE1");
        value = -rate1;
        break;
      case ACW_RATE2: 
        // Serial.print(i);
        // Serial.println(": ACW_RATE2");
        value = -rate2;
        break;
      case ACW_RATE3: 
        // Serial.print(i);
        // Serial.println(": ACW_RATE3");
        value = -rate3;
        break;
    }
    if(value != 0){
      switch(i){
        case 0: // A1RE
          Analyser1.nudgeRE(value);
          break;
        case 1: // A1LE
          Analyser1.nudgeLE(value);
          break;
        case 2: // A1DX
          Analyser1.nudgeDX(value);
          break;
        case 3: // A1DY
          Analyser1.nudgeDY(value);
          break;
        case 4: // A2RE
          Analyser2.nudgeRE(value);
          break;
        case 5: // A2LE
          Analyser2.nudgeLE(value);
          break;
        case 6: // A2DX
          Analyser2.nudgeDX(value);
          break;
        case 7: // A2DY
          Analyser2.nudgeDY(value);
          break;
      }
    }
  }
}

void checkSerial(){
  if(sc.check()){
    Analyser *An;
    if(sc.contains("1")){
      An = &Analyser1;
    }
    else if(sc.contains("2"))
    {
      An = &Analyser2;
    }
    if(sc.contains("SV", 1)){
      // Setting a voltage
      if(sc.contains("RE", 3)){
        // Get residual energy voltage
        An->setRE(sc.toInt32(5));
      }
      else if(sc.contains("LE", 3)){
        // Get lens voltage
        An->setLE(sc.toInt16(5));
      }
      else if(sc.contains("DX", 3)){
        // Get deflector X
        An->setDX(sc.toInt16(5));
      }
      else if(sc.contains("DY", 3)){
        // Get deflector Y
        An->setDY(sc.toInt16(5));
      }
      else if(sc.contains("AM", 3)){
        // Get analyser mean
        An->setAM(sc.toInt16(5));
      }
      else if(sc.contains("IH", 3)){
        // Get inner hemisphere
        An->setIH(sc.toInt16(5));
      }
      else if(sc.contains("OH", 3)){
        // Get outer hemisphere
        An->setOH(sc.toInt16(5));
      }
    }
    else if(sc.contains("GV", 1)){
      if(sc.contains("RE", 3)){
        // Get residual energy
        Serial.println(An->getRE());
      }
      else if(sc.contains("LE", 3)){
        // Get lens
        Serial.println(An->getLE());
      }
      else if(sc.contains("DX", 3)){
        //GSet deflector X
        Serial.println(An->getDX());
      }
      else if(sc.contains("DY", 3)){
        // Get deflector Y
        Serial.println(An->getDY());
      }
      else if(sc.contains("AM", 3)){
        // Get analyser mean
        Serial.println(An->getAM());
      }
      else if(sc.contains("IH", 3)){
        // Get inner hemisphere
        Serial.println(An->getIH());
      }
      else if(sc.contains("OH", 3)){
        // Get outer hemisphere
        Serial.println(An->getOH());
      }
      else if(sc.contains("AE", 3)){
        // Get all elements' voltages
        Serial.println(An->getRE());
        Serial.println(An->getLE());
        Serial.println(An->getDX());
        Serial.println(An->getDY());
        Serial.println(An->getAM());
        Serial.println(An->getIH());
        Serial.println(An->getOH());
      }
    }
    else if(sc.contains("ID")){
      // Get the ID for this device which is AN for Analyser.
      Serial.println("AN");
    }
  }
}