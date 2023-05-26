/*  Arduino Motor Controller Firmware */
#include "Arduino.h"

#define POST_COMMUTATION_DELAY_MS 10

#define PIN_MOSFET_A_HI 10
#define PIN_MOSFET_A_LO 11
#define PIN_MOSFET_B_HI 6
#define PIN_MOSFET_B_LO 9
#define PIN_MOSFET_C_HI 3
#define PIN_MOSFET_C_LO 5

#define PIN_HALL_A A1
#define PIN_HALL_B A2
#define PIN_HALL_C A3

#define PIN_THROTTLE A4

void setup() {
    pinMode(PIN_MOSFET_A_HI, OUTPUT);
    pinMode(PIN_MOSFET_A_LO, OUTPUT);
    pinMode(PIN_MOSFET_B_HI, OUTPUT);
    pinMode(PIN_MOSFET_B_LO, OUTPUT);
    pinMode(PIN_MOSFET_C_HI, OUTPUT);
    pinMode(PIN_MOSFET_C_LO, OUTPUT);

    pinMode(PIN_HALL_A, INPUT_PULLUP);
    pinMode(PIN_HALL_B, INPUT_PULLUP);
    pinMode(PIN_HALL_C, INPUT_PULLUP);
}

void loop() {
    // Reading from potentiometer
    int throttle = analogRead(PIN_THROTTLE);

    // Mapping the Values between 0 to 255 because we can give output
    // from 0 -255 using the analogwrite funtion
    int dutyCycle = map(throttle, 0, 1023, 0, 255);

    bool hallA = digitalRead(PIN_HALL_A);
    bool hallB = digitalRead(PIN_HALL_B);
    bool hallC = digitalRead(PIN_HALL_C);

    if (hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_HI, 0);
        analogWrite(PIN_MOSFET_B_LO, dutyCycle);

        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
        analogWrite(PIN_MOSFET_C_LO, 0);

        delay(POST_COMMUTATION_DELAY_MS);
    } else if (hallA && !hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, dutyCycle);

        analogWrite(PIN_MOSFET_B_LO, dutyCycle);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);
        delay(POST_COMMUTATION_DELAY_MS);
    } else if (hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, dutyCycle);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, 0);
        delay(POST_COMMUTATION_DELAY_MS);
    } else if (!hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, dutyCycle);

        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, 0);
        delay(POST_COMMUTATION_DELAY_MS);
    } else if (!hallA && hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, dutyCycle);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);
        delay(POST_COMMUTATION_DELAY_MS);
    } else if (!hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
        delay(POST_COMMUTATION_DELAY_MS);
    }
}
