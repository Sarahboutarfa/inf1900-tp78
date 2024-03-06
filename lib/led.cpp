#include "led.h"

Led::Led(volatile uint8_t* portX,
        volatile uint8_t* ddrX,
        uint8_t pinM,
        uint8_t pinP) : // Liste d'initialisation
    _portX(portX),
    _pinM(pinM),
    _pinP(pinP)
{
    *ddrX |= (1 << _pinP);
    *ddrX |= (1 << _pinM);
}

void Led::turnOnRed()
{
    *_portX |= (1 << _pinM);
    *_portX &= ~(1 << _pinP);
}

void Led::turnOnGreen()
{
    *_portX |= (1 << _pinP);
    *_portX &= ~(1 << _pinM);
}

void Led::turnOnAmber()
{
    turnOnGreen();
    _delay_ms(DELAY_AMBER_GREEN);
    turnOnRed();
    _delay_ms(DELAY_AMBER_RED);
}

void Led::turnOff()
{
    *_portX &= ~(1 << _pinM);
    *_portX &= ~(1 << _pinP);
}