#pragma once
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "timers.h"

#define BUTTON_PIN PD2

using namespace std;



class Wheels{
    public:
    Wheels();
    void controlSpeed(uint16_t valeurDepart=0, uint16_t speedPercentLeft, uint16_t speedPercentRight);
    void moveFoward();
    void moveBackward();
    void stop();

    private:
    volatile uint8_t* _portX;
    uint8_t _pinM;
    uint8_t _pinP;
};

