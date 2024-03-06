#pragma once
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


enum class OptionsPin {PIN1 = (1 << PD2), PIN2 = (1<< PD3)};

class Button{
    public:
        Button(OptionsPin pinX);
        ~Button() = default;
        void interruptPressedAndReleased();
        void interruptPressed();
        void interruptReleased();


    private:
        volatile uint8_t* _vector;
        uint8_t _pinX;
};


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



class Timer{
    public:
        virtual void modifyTimer( uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0)
        virtual void ctc();
        virtual void pwmPhaseCorrect();
        virtual void normal();
        virtual void prescaler(uint16_t prescalerValue);
        

};

class Timer0: public Timer{
    public:

        Timer0(uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0);
        virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};


class Timer1: public Timer{
    public:

        Timer1(uint16_t valeurComparaisonA, uint16_t valeurComparaisonB, uint16_t valeurDepart=0);
        virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};


class Timer2: public Timer{
    public:

        Timer2(uint8_t valeurComparaisonA, uint8_t valeurComparaisonB, uint8_t valeurDepart=0);
        virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};



class Wheels{
    public:
    Wheels();
    void controlSpeed(uint16_t speedPercentLeft, uint16_t speedPercentRight, uint16_t valeurDepart=0);
    void moveFoward();
    void moveBackward();
    void stop();

    private:
    volatile uint8_t* _portX;
    uint8_t _pinM;
    uint8_t _pinP;
};
