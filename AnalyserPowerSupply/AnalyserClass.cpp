#include "AnalyserClass.h"

// DACs are as follows:
// 0A: A1RE coarse
// 0B: A1RE fine
// 1A: A2RE 
// 1B: A2RE 
// 2A: A1OH
// 2B: A1LE
// 3A: A2OH
// 3B: A2LE
// 4A: A1AM
// 4B: A1IH
// 5A: A2AM
// 5B: A2IH
// 6A: A1DX
// 6B: A1DY
// 7A: A2DX
// 7B: A2DY
// 
// For this class, the above translates to:
// DAC: Index:  Element
// 0:   0       RE corase
// 0:   1       RE fine
// 1:   0       OH
// 1:   1       LE
// 2:   0       AM
// 2:   1       IH
// 3:   0       DX
// 3:   1       DY


Analyser::Analyser(uint8_t n){
    this->n = n;
}

void Analyser::init(){
    if(n == 1){
        for(uint8_t i = 0; i < 4; i++){
            dac[i].init(firstCSPin + (2 * i));
        }
    }
    else if(n == 2){
        for(uint8_t i = 0; i < 4; i++){
            dac[i].init(firstCSPin + (2 * i) + 1);
        }
    }
    // set the voltages to their default values (defined in the header)
    updateAllDACs();
}

void Analyser::updateAllDACs(){
    setRE(VRE);
    setLE(VLE);
    setDX(VDX);
    setDY(VDY);
    setAM(VAM);
    setIH(VIH);
    setOH(VOH);
}

void Analyser::setRE(int32_t voltage){
    VRE = constrainVoltage(voltage);
    VREcoarse = voltage / fineSteps;
    VREfine = voltage % fineSteps;
    DEBUG_PRINT("Coarse: ");
    DEBUG_PRINTLN(VREcoarse);
    DEBUG_PRINT("Fine: ");
    DEBUG_PRINTLN(VREfine);
    dac[0].setVoltage(0, VREcoarse);
    dac[0].setVoltage(1, VREfine);
}

void Analyser::setRA(int32_t voltage)
{
    VREcoarse = constrainVoltage(voltage);
    DEBUG_PRINT("Coarse: ");
    DEBUG_PRINTLN(VREcoarse);
    dac[0].setVoltage(0, VREcoarse);
}

void Analyser::setRB(int32_t voltage)
{
    VREfine = constrainVoltage(voltage);
    DEBUG_PRINT("Fine: ");
    DEBUG_PRINTLN(VREfine);
    dac[0].setVoltage(1, VREfine);
}

void Analyser::setLE(int16_t voltage){
    VLE = constrainVoltage(voltage);
    dac[1].setVoltage(1, VLE);
}

void Analyser::setAM(int16_t voltage){
    VAM = constrainVoltage(voltage);
    dac[2].setVoltage(0, VAM);
}

void Analyser::setIH(int16_t voltage){
    VIH = constrainVoltage(voltage);
    dac[2].setVoltage(1, VIH);
}

void Analyser::setOH(int16_t voltage){
    VOH = constrainVoltage(voltage);
    dac[1].setVoltage(0, VOH);
}

void Analyser::setDX(int16_t voltage){
    VDX = constrainVoltage(voltage);
    dac[3].setVoltage(0, VDX);
}

void Analyser::setDY(int16_t voltage){
    VDY = constrainVoltage(voltage);
    dac[3].setVoltage(1, VDY);
}

void Analyser::nudgeRE(int16_t deltaVoltage){
    setRE(VRE + deltaVoltage);
}

void Analyser::nudgeLE(int16_t deltaVoltage){
    setLE(VLE + deltaVoltage);
}

void Analyser::nudgeAM(int16_t deltaVoltage){
    setAM(VAM + deltaVoltage);
}

void Analyser::nudgeIH(int16_t deltaVoltage){
    setIH(VIH + deltaVoltage);
}

void Analyser::nudgeOH(int16_t deltaVoltage){
    setOH(VOH + deltaVoltage);
}

void Analyser::nudgeDX(int16_t deltaVoltage){
    setDX(VDX + deltaVoltage);
}

void Analyser::nudgeDY(int16_t deltaVoltage){
    setDY(VDY + deltaVoltage);
}

uint32_t Analyser::getRE(){
    return VRE;
}

uint16_t Analyser::getRA(){
    //Get dac[0] channel A
    return VREcoarse;
}

uint16_t Analyser::getRB(){
    //Get dac[0] channel B
    return VREfine;
}

uint16_t Analyser::getLE(){
    return VLE;
}
uint16_t Analyser::getAM(){
    return VAM;
}
uint16_t Analyser::getIH(){
    return VIH;
}
uint16_t Analyser::getOH(){
    return VOH;
}
uint16_t Analyser::getDX(){
    return VDX;
}
uint16_t Analyser::getDY(){
    return VDY;
}

int16_t Analyser::constrainVoltage(int16_t voltage){
    // handles the case where a new voltage is outside of a valid DAC voltage 0 -> 4095.
    if(voltage > 4095){
        voltage = 4095;
    }
    else if(voltage < 0){
        voltage = 0;
    }
    return voltage;
}

int32_t Analyser::constrainVoltage(int32_t voltage){
    // constrain a residual energy voltage within a valid range
    if(voltage > (4096 * int32_t(fineSteps) - 1)){
        voltage = 4096 * int32_t(fineSteps) - 1;
    }
    else if(voltage < 0){
        voltage = 0;
    }
    DEBUG_PRINT("Constrained to: ");
    DEBUG_PRINTLN(voltage);
    return voltage;
}