#ifndef ANALYSERCLASS_H
#define ANALYSERCLASS_H

#include <Arduino.h>
#include <SPI.h>
#include "MCP4822.h"

//// Analyser Voltage Class
class Analyser{
public:
  Analyser(uint8_t n);
  void init();
  
  // The following commands are used to set the DAC voltages. All have 4096 levels except RSE which uses 
  // two DACs to provide 4096 * 100 steps for finer control.
  void setRE(int32_t voltage);
  void setLE(int16_t voltage);
  void setAM(int16_t voltage);
  void setIH(int16_t voltage);
  void setOH(int16_t voltage);
  void setDX(int16_t voltage);
  void setDY(int16_t voltage);

  // The following commands add or subtract a delta voltage. Handy for use with front panel rotary encoders etc  
  void nudgeRE(int16_t deltaVoltage);
  void nudgeLE(int16_t deltaVoltage);
  void nudgeAM(int16_t deltaVoltage);
  void nudgeIH(int16_t deltaVoltage);
  void nudgeOH(int16_t deltaVoltage);
  void nudgeDX(int16_t deltaVoltage);
  void nudgeDY(int16_t deltaVoltage);

  // Returns the stored set values.
  uint32_t getRE();
  uint16_t getLE();
  uint16_t getAM();
  uint16_t getIH();
  uint16_t getOH();
  uint16_t getDX();
  uint16_t getDY();
private:
  // These constrain the input voltages to valid values.
  uint16_t constrainVoltage(int16_t voltage);
  uint32_t constrainResidualEnergyVoltage(int32_t voltage);
  uint8_t n;
  MCP4822 dac[4];
  const uint8_t firstCSPin = 42; // The four DACs' chip select pins start here and run sequentially
  const uint8_t fineSteps = 100; // The number of fine steps for every coarse step on the RSE voltage
  // Initial values used to set the DACs so that all supplies output 0V to the experiment on startup.
  uint32_t VRE = 0; 
  uint16_t VLE = 0;
  uint16_t VDX = 2048;
  uint16_t VDY = 2048;
  uint16_t VAM = 0;
  uint16_t VIH = 0;
  uint16_t VOH = 0;
};

#endif