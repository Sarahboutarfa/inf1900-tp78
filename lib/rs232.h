#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL


class Rs232{
    public:
    Rs232();
    void setBaudRate(uint16_t baudRate);
    void setParityEven();
    void setParityOdd();
    void setNoParityBit();
    void setStopBit(uint8_t nbBit);
    void transmitUART(uint8_t donneeATransmettre);
    void setCharacterSize(uint8_t characterSize);
    void transmitStringUART(char tableau[]);

};