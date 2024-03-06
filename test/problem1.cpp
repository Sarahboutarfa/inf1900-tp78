#include "led.h"

// Exemple de main pour tester votre class

constexpr uint16_t DELAY_TWO_SECONDS = 2000;
constexpr uint16_t ITERATIONS_TWO_SECONDS = 200;

int main() {
    Led led(&PORTA, &DDRA, PA0, PA1);

    while (true) {
        for (uint8_t i = 0; i < ITERATIONS_TWO_SECONDS; i++) led.turnOnAmber();
        led.turnOff();
        _delay_ms(DELAY_TWO_SECONDS);
    }
};