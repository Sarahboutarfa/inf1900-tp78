#include "rs232.h"
#include <cstring>
using namespace std;

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