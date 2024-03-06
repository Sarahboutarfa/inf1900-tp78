#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

enum class OptionsPin{
    PIN1 = (1 << PD2),
    PIN2 = (1<< PD3)
}

class Button{
    public:
        Button(OptionsPin::pinX);
        ~Button() = default;
        
        void interruptPressedAndReleased();
        void interruptPressed();
        void interruptReleased();


    private:
        volatile uint8_t* _vector;
        uint8_t _pinX;
};