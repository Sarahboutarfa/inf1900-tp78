#include "timers.h"

Timer0::Timer0(uint16_t valeurDepart=0, uint16_t valeurComparaisonA=0, uint16_t valeurComparaisonB=0){
    TCNT0 = valeurDepart;
    OCR0A = valeurComparaisonA;
    OCR0B = valeurComparaisonB;
    DDRD |= (1 << PB3) | (1 << PB4);
    }

void Timer0::modifyTimer(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB){
    TCNT0 = valeurDepart;
    OCR0A = valeurComparaisonA;
    OCR0B = valeurComparaisonB;
}

void Timer0::ctc() {

    TCCR0B |= (0 << WGM02);
    TCCR0A |= (1 << WGM01) | (0 << WGM00)| (0 << COM0A1) | (0 << COM0B1);
}

void Timer0::normal() {

    TCCR0B |= (0 << WGM02);
    TCCR0A |= (0 << WGM01) | (0 << WGM00)| (0 << COM0A1) | (0 << COM0B1);
}

void Timer0::pwmPhaseCorrect() {

    TCCR0B |= (0 << WGM02);
    TCCR0A |= (0 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    //Set OC0B on Compare Match when up-counting. Clear OC0B onCompare Match when down-counting
    // Ce mode a ete choisi car cest le seul que on a utilise pendant nos tp
}


void Timer0::prescaler(uint16_t prescalerValue){
    switch (prescalerValue) {
        case 256:
            TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
            break;
        case 64:
            TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
            break;
        case 8:
            TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
            break;
        case 1:
            TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
            break;
        default:
            TCCR0B |= (0 << CS02) | (0 << CS01) | (0 << CS00);
            break;
    }
}







Timer::Timer1( uint16_t valeurDepart=0, uint16_t valeurComparaisonA=0, uint16_t valeurComparaisonB=0){
    TCNT1 = valeurDepart;
    OCR1A = valeurComparaisonA;
    OCR1B = valeurComparaisonB;
    DDRD |= (1 << PD5) | (1 << PD4);
    }

void Timer1::modifyTimer(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB){
    TCNT0 = valeurDepart;
    OCR0A = valeurComparaisonA;
    OCR0B = valeurComparaisonB;
}


void Timer1::ctc() {

    TCCR1B |= (0 << WGM13) | (1 << WGM12);
    TCCR1A |= (0 << WGM11) | (0 << WGM10)| (0 << COM1A1) | ( 0 << COM1B1) ;
}

void Timer1::normal() {

    TCCR1B |= (0 << WGM13) | (0 << WGM12);
    TCCR1A |= (0 << WGM11) | (0 << WGM10)| (0 << COM1A1) | ( 0 << COM1B1);
}

void Timer1::pwmPhaseCorrect() {

    TCCR1B |= (0 << WGM13) | (0 << WGM12);
    TCCR1A |= (0 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); //Set OC0B on Compare Match when up-counting. Clear OC0B onCompare Match when down-counting
                                                                           // Ce mode a ete choisi car cest le seul que on a utilise pendant nos tp
}

void Timer1::prescaler(uint16_t prescalerValue){
    switch (prescalerValue) {
        case 1024:
            TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case 256:
            TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case 64:
            TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        case 8:
            TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case 1:
            TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        default:
            TCCR1B |= (0 << CS12) | (0 << CS11) | (0 << CS10);
            break;
    }
}







Timer2::Timer2(uint8_t valeurDepart=0, uint8_t valeurComparaisonA=0, uint8_t valeurComparaisonB=0){
    TCNT2 = valeurDepart;
    OCR2A = valeurComparaisonA;
    OCR2B = valeurComparaisonB;
    DDRD |= (1 << PB3) | (1 << PB4);
    }

void Timer2::modifyTimer(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB){
    TCNT0 = valeurDepart;
    OCR0A = valeurComparaisonA;
    OCR0B = valeurComparaisonB;
}

void Timer2::ctc() {

    TCCR2B |= (0 << WGM22);
    TCCR2A |= (1 << WGM21) | (0 << WGM20) | (0 << COM2A1) | (0 << COM2B1);
}

void Timer2::normal() {

    TCCR2B |= (0 << WGM22);
    TCCR2A |= (0 << WGM21) | (0 << WGM20) | (0 << COM2A1) | (0 << COM2B1);
}

void Timer2::pwmPhaseCorrect() {

    TCCR2B |= (1 << WGM22);
    TCCR2A |= (0 << WGM21) | (1 << WGM20) | (1 << COM2A1) | (1 << COM2B1);
}


void Timer0::prescaler(uin16_t prescalerValue){
    switch (prescalerValue) {
        case 256:
            TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20);
            break;
        case 64:
            TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20);
            break;
        case 8:
            TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);
            break;
        case 1:
            TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
            break;
        default:
            TCCR2B |= (0 << CS22) | (0 << CS21) | (0 << CS20);
            break;
    }
}