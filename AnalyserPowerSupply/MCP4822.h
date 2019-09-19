#ifndef _MCP4822_SPI_H
#define _MCP4822_SPI_H

#include <Arduino.h>
#include <SPI.h>

// Bit banged class to send updates to MCP4822. Only for High gain (x2) at the moment.
// Pins:
// 1 Vdd    5V
// 2 !CS
// 3 SCK
// 4 SDI
// 5 VoutA
// 6 Vss    0V
// 7 VoutB
// 8 !LDAC  Tie low to update immediately.

class MCP4822
{
    private:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _cs;
        uint8_t _MSByte;
        uint8_t _LSByte;

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        MCP4822();
        MCP4822(uint8_t cs); 
    
        void init();
        void init(uint8_t cs);
        void setVoltage(bool channel, int16_t voltage);
        void setAllVoltages(int16_t voltage);
		void set24bitVoltage(uint32_t dacInput, bool order = true);
};
#endif
