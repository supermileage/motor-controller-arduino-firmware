/*  Arduino Motor Controller Firmware */
#include "Arduino.h"

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
    // configure complementary pwm on low side
    TCCR0A = 0b10110000 | (TCCR0A & 0b00001111);
    // set prescaler to 1 - 32kHz
    TCCR0B = ((TCCR0B & 0b11110000) | 0x01); 

    // Timer1 controls pins 9, 10
    // set prescaler to 1 - 32kHz
    TCCR1B = ((TCCR1B & 0b11110000) | 0x01); 
    // configure complementary pwm on low side
    TCCR1A = 0b11100000 | (TCCR1A & 0b00001111);

    // Timer2 controls pins 3, 11
    // set prescaler to 1 - 32kHz
    TCCR2B = ((TCCR2B & 0b11110000) | 0x01); 
    // configure complementary pwm on low side
    TCCR2A = 0b11100000 | (TCCR2A & 0b00001111);

    pinMode(PIN_MOSFET_A_LO, OUTPUT);
    pinMode(PIN_MOSFET_A_HI, OUTPUT);

    pinMode(PIN_MOSFET_B_LO, OUTPUT);
    pinMode(PIN_MOSFET_B_HI, OUTPUT);

    pinMode(PIN_MOSFET_C_LO, OUTPUT);
    pinMode(PIN_MOSFET_C_HI, OUTPUT);

    pinMode(PIN_HALL_A, INPUT_PULLUP);
    pinMode(PIN_HALL_B, INPUT_PULLUP);
    pinMode(PIN_HALL_C, INPUT_PULLUP);

    // Serial.begin(9600);

}

void loop() {
    // Reading from potentiometer
    int throttle = analogRead(PIN_THROTTLE);

    // Serial.println(throttle);

    // Mapping the Values between 0 to 255 because we can give output
    // from 0 -255 using the analogwrite funtion
    int dutyCycle = map(throttle, 0, 1023, 0, 255);

    bool hallA = digitalRead(PIN_HALL_A);
    bool hallB = digitalRead(PIN_HALL_B);
    bool hallC = digitalRead(PIN_HALL_C);

    // Serial.print("hallA: ");
    // Serial.print(hallA);
    // Serial.print(" - hallB: ");
    // Serial.print(hallB);
    // Serial.print(" - hallC: ");
    // Serial.println(hallC);

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
