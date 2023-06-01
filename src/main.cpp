/*  Arduino Motor Controller Firmware */
#include "Arduino.h"

// This must be set to 0 in order to run motor
#define HALL_DEBUG_MODE 0

#define PIN_MOSFET_A_LO 11
#define PIN_MOSFET_A_HI 10

#define PIN_MOSFET_B_LO 9
#define PIN_MOSFET_B_HI 6

#define PIN_MOSFET_C_LO 5
#define PIN_MOSFET_C_HI 3

#define PIN_HALL_A A1
#define PIN_HALL_B A2
#define PIN_HALL_C A3

#define PIN_THROTTLE A4

void setup() {
    // Timer0 controls pins 5, 6
    // Set timer mode to PWM Phase Correct
    TCCR0A = ((TCCR0A & 0b11111100) | 0x01);
    // set prescaler to 1 - 32kHz
    TCCR0B = ((TCCR0B & 0b11110000) | 0x01);

    // Timer1 controls pins 9, 10
    // set prescaler to 1 - 32kHz
    TCCR1B = ((TCCR1B & 0b11110000) | 0x01);

    // Timer2 controls pins 3, 11
    // set prescaler to 1 - 32kHz
    TCCR2B = ((TCCR2B & 0b11110000) | 0x01);

    pinMode(PIN_MOSFET_A_LO, OUTPUT);
    pinMode(PIN_MOSFET_A_HI, OUTPUT);

    pinMode(PIN_MOSFET_B_LO, OUTPUT);
    pinMode(PIN_MOSFET_B_HI, OUTPUT);

    pinMode(PIN_MOSFET_C_LO, OUTPUT);
    pinMode(PIN_MOSFET_C_HI, OUTPUT);

    pinMode(PIN_HALL_A, INPUT_PULLUP);
    pinMode(PIN_HALL_B, INPUT_PULLUP);
    pinMode(PIN_HALL_C, INPUT_PULLUP);

    if (HALL_DEBUG_MODE) {
        Serial.begin(9600);
    }
}

void loop() {
    bool hallA = digitalRead(PIN_HALL_A);
    bool hallB = digitalRead(PIN_HALL_B);
    bool hallC = digitalRead(PIN_HALL_C);

    if (HALL_DEBUG_MODE) {
        Serial.print("hallA: ");
        Serial.print(hallA);
        Serial.print(" - hallB: ");
        Serial.print(hallB);
        Serial.print(" - hallC: ");
        Serial.println(hallC);
    }

    // Reading from potentiometer
    int dutyCycle = analogRead(PIN_THROTTLE) / 4;

    if (hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, dutyCycle);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
    } else if (hallA && !hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, dutyCycle);

        analogWrite(PIN_MOSFET_B_LO, dutyCycle);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);
    } else if (hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, dutyCycle);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, 0);
    } else if (!hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, dutyCycle);

        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, 0);
    } else if (!hallA && hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, dutyCycle);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);
    } else if (!hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
    }
}
