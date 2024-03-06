#include "button.h"
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

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


Rs232::Rs232(){
    UCSR0A = (RXC0 << 1)  | (TXC0 << 1 ) ; 
    UCSR0B = (RXEN0 << 1)  | (TXEN0 << 1 );
}

void Rs232::setParityEven(){
    UCSR0C = (UPM01 << 1)  | (UPM00 << 0);
}

void Rs232::setParityOdd(){
    UCSR0C = (UPM01 << 1)  | (UPM00 << 1);
}

void Rs232::setNoParityBit(){
    UCSR0C = (UPM01 << 0)  | (UPM00 << 0);
}

void Rs232:: setStopBit(uint8_t nbBit){
    if (nbBit == 1){
        UCSR0C = (USBS0 << 0); 
    }
    if (nbBit == 2){
        UCSR0C = (USBS0 << 1); 
    }
}

void Rs232::setCharacterSize(uint8_t characterSize){
    if (characterSize == 5){
        UCSR0C = (UCSZ02 << 0)  | (UCSZ01 << 0)  |  (UCSZ00 << 0); 
    }
    if (characterSize == 6){
        UCSR0C = (UCSZ02 << 0)  | (UCSZ01 << 0)  |  (UCSZ00 << 1); 
    }
    if (characterSize == 7){
        UCSR0C = (UCSZ02 << 0)  | (UCSZ01 << 1)  |  (UCSZ00 << 0); 
    }
    if (characterSize == 8){
        UCSR0C = (UCSZ02 << 0)  | (UCSZ01 << 1)  |  (UCSZ00 << 1); 
    }
    if (characterSize == 9){
        UCSR0C = (UCSZ02 << 1)  | (UCSZ01 << 1)  |  (UCSZ00 << 1); 
    }
}

void Rs232::setBaudRate(uint16_t baudRate){
    UBRR0H = 0;
    if (baudRate == 2400){
            UBRR0L = 0xCF;
    }
    if (baudRate == 4800){
            UBRR0L = 0x67;
    }
    if (baudRate == 9600){
            UBRR0L = 0x33;
    }
}

//documentation p.174
void Rs232::transmitUART(uint8_t donneeATransmettre){
       while ( !( UCSR0A & (1<<UDRE0)) ){ 
            UDR0 = donneeATransmettre;
    }
}

void Rs232::transmitStringUART(char tableau[]){
    for (int i = 0; i<strlen(tableau); i++){
        transmitUART(tableau[i]);
    }   
}




Timer0::Timer0(uint16_t valeurDepart=0, uint16_t valeurComparaisonA=0, uint16_t valeurComparaisonB=0){
    TCNT0 = valeurDepart;
    OCR0A = valeurComparaisonA;
    OCR0B = valeurComparaisonB;
    DDRD |= (1 << PB3) | (1 << PB4);
    }

void Timer0::modifyTimer( uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0){
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







Timer1::Timer1( uint16_t valeurDepart=0, uint16_t valeurComparaisonA=0, uint16_t valeurComparaisonB=0){
    TCNT1 = valeurDepart;
    OCR1A = valeurComparaisonA;
    OCR1B = valeurComparaisonB;
    DDRD |= (1 << PD5) | (1 << PD4);
    }

void Timer1::modifyTimer(uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0){
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

void Timer2::modifyTimer(uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0){
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


void Timer2::prescaler(uint16_t prescalerValue){
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




Wheels::Wheels(){
     DDRD |= (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4); //PD3 et PD4 sont les rserve pour OC0B et OC0A
     Timer0 timer0;
     timer0.pwmPhaseCorrect();
}

void Wheels::controlSpeed( uint16_t speedPercentLeft, uint16_t speedPercentRight, uint16_t valeurDepart=0){
     const uint8_t INSTRUCTION_MAX = 255;  //255 = nombres d'instructions maximum (WM, Phase Correct, 8-bit)
     uint16_t valeurComparaisonA = (speedPercentLeft * INSTRUCTION_MAX)/100;
     uint16_t valeurComparaisonB = (speedPercentRight * INSTRUCTION_MAX)/100;
     timer0.modifyTimer(valeurComparaisonA, valeurComparaisonB, valeurDepart);     
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

