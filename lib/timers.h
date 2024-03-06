#pragma once
#include <avr/io.h>
#define F_CPU 8000000UL

class Timer{
    public:
        virtual void modifyTimer(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB)
        virtual void ctc();
        virtual void pwmPhaseCorrect();
        virtual void normal();
        virtual void prescaler(uint16_t prescalerValue);
        

};

class Timer0: public Timer{
    public:

        Timer0(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB);
        virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};


class Timer1: public Timer{
    public:

        Timer1(uint16_t valeurDepart=0, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB);
         virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};


class Timer2: public Timer{
    public:

        Timer2(uint8_t valeurDepart=0, uint8_t valeurComparaisonA, uint8_t valeurComparaisonB);
        virtual void modifyTimer(uint16_t valeurDepart, uint16_t valeurComparaisonA, uint16_t valeurComparaisonB) override;
        void ctc() override;
        void pwmPhaseCorrect() override;
        void normal() override;
        void prescaler(uint16_t prescalerValue)override;

};