
#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

class Led {
public:
    Led(volatile uint8_t* portX,
        volatile uint8_t* ddrX,
        uint8_t pinM,
        uint8_t pinP);

    void turnOnRed();
    void turnOnGreen();
    void turnOnAmber();
    void turnOff();
    ~Led() = default;
private:
    volatile uint8_t* _portX;
    uint8_t _pinM;
    uint8_t _pinP;
    static constexpr uint8_t DELAY_AMBER_RED = 5;
    static constexpr uint8_t DELAY_AMBER_GREEN = 10;
};

