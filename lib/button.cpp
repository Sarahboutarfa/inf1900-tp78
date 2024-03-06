#include "button.h"

Button::Button(OptionsPin pinX):_pinX(pinX)
{
    DDRD &= ~(1 << _pinX);
    if (_pinX == PD2){
        _vector= INT0; //potentiel erreur de type
    }
     if (_pinX == PD3){
        _vector= INT1; //potentiel erreur de type
    }
    EIMSK |= (1 << _vector);

};

void Button::interruptPressedAndReleased(){
    EICRA |= (ISC00<<1) | (ISC01<<0); 
}

void Button::interruptPressed(){
    EICRA |= (ISC00<<1) | (ISC01<<1); 
}

void Button::interruptReleased(){
    EICRA |= (ISC00<<0) | (ISC01<<1); 
}


