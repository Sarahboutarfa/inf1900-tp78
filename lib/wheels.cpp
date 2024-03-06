#include "wheels.h"


Wheels::Wheels(){
     DDRD |= (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4); //PD3 et PD4 sont les rserve pour OC0B et OC0A
     Timer0 timer0;
     timer0.pwmPhaseCorrect();
}

void Wheels::controlSpeed(uint16_t valeurDepart=0, uint16_t speedPercentLeft, uint16_t speedPercentRight ){
     const uint8_t INSTRUCTION_MAX = 255;  //255 = nombres d'instructions maximum (WM, Phase Correct, 8-bit)
     uint16_t valeurComparaisonA = (speedPercentLeft * INSTRUCTION_MAX)/100;
     uint16_t valeurComparaisonB = (speedPercentRight * INSTRUCTION_MAX)/100;
     timer0.modifyTimer(valeurDepart,valeurComparaisonA,valeurComparaisonB);     
}

void Wheels::moveFoward(){
     PORTD |= (0 << PD1) | (0 << PD2)| (1 << PD3) | (1 << PD4); 
}

void Wheels::moveBackward(){
     PORTD |= (1 << PD1) | (1 << PD2)| (1 << PD3) | (1 << PD4); 
}

void Wheels::stop(){
      PORTD &= ~( (1 << PD1) | (1 << PD2)| (1 << PD3) | (1 << PD4)); 
}

