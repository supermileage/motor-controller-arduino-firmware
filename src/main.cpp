/*  Arduino Motor Controller Firmware */
#include "Arduino.h"

// This must be set to 0 in order to run motor
#define DEBUG_MODE 0
#define HALL_DEBUG_MODE 0
#define HI_LO_DEBUG_MODE 0
#define THROTTLE_DEBUG_MODE 0


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

    GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC); // halt all timers

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

    // set all timers to the same value
    TCNT0 = 0; // set timer0 to 0
    TCNT1H = 0; // set timer1 high byte to 0
    TCNT1L = 0; // set timer1 low byte to 0
    TCNT2 = 0; // set timer2 to 0
    
    GTCCR = 0; // release all timers

    pinMode(PIN_MOSFET_A_LO, OUTPUT);
    pinMode(PIN_MOSFET_A_HI, OUTPUT);

    pinMode(PIN_MOSFET_B_LO, OUTPUT);
    pinMode(PIN_MOSFET_B_HI, OUTPUT);

    pinMode(PIN_MOSFET_C_LO, OUTPUT);
    pinMode(PIN_MOSFET_C_HI, OUTPUT);

    analogWrite(PIN_MOSFET_A_LO, 0);
    analogWrite(PIN_MOSFET_A_HI, 0);

    analogWrite(PIN_MOSFET_B_HI, 0);
    analogWrite(PIN_MOSFET_B_LO, 0);

    analogWrite(PIN_MOSFET_C_LO, 0);
    analogWrite(PIN_MOSFET_C_HI, 0);

    pinMode(PIN_HALL_A, INPUT_PULLUP);
    pinMode(PIN_HALL_B, INPUT_PULLUP);
    pinMode(PIN_HALL_C, INPUT_PULLUP);

    if (DEBUG_MODE) {
        Serial.begin(9600);
    }
    if (HI_LO_DEBUG_MODE) {
        Serial.begin(9600);
    }
}

unsigned long prevTime = 0;
unsigned long currentTime = 0;
bool prevHallA = digitalRead(PIN_HALL_A);

int counter = 0;

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

    int maxDutyCycle = 40;
    // Reading from potentiometer
    int dutyCycle = analogRead(PIN_THROTTLE) / 4;

    if (hallA != prevHallA) {
        currentTime = millis();
        unsigned long elapsedTime = currentTime - prevTime;
        prevTime = currentTime;

        prevHallA = hallA;
        unsigned long rpm = 60000 / (elapsedTime * 18 / 360);

        // Scaling the duty cycle based on RPM
        maxDutyCycle = map(rpm, 0, 8000, 40, 103);
    }

    if (dutyCycle > maxDutyCycle) {
        dutyCycle = maxDutyCycle;

    //int Throttle = analogRead(A4);
    if (DEBUG_MODE){
        counter++;
        if (counter == 100){
            counter = 0;
            if (HALL_DEBUG_MODE) {
                Serial.print("hallA: ");
                Serial.print(hallA);
                Serial.print(" - hallB: ");
                Serial.print(hallB);
                Serial.print(" - hallC: ");
                Serial.println(hallC);
            }
            if (HI_LO_DEBUG_MODE){
                int A_HI = analogRead(PIN_MOSFET_A_HI);
                int A_LO = analogRead(PIN_MOSFET_A_LO);
                int B_HI = analogRead(PIN_MOSFET_B_HI);
                int B_LO = analogRead(PIN_MOSFET_B_LO);
                int C_HI = analogRead(PIN_MOSFET_C_HI);
                int C_LO = analogRead(PIN_MOSFET_C_LO);

                Serial.print("Pin Mosfet A Hi: ");
                Serial.print(A_HI);
                Serial.print("  -  Pin Mosfet A LO: ");
                Serial.print(A_LO);
                Serial.print("  Pin Mosfet B Hi: ");
                Serial.print(B_HI);
                Serial.print("  -  Pin Mosfet B LO: ");
                Serial.print(B_LO);
                Serial.print("  Pin Mosfet C Hi: ");
                Serial.print(C_HI);
                Serial.print("  -  Pin Mosfet C LO: ");
                Serial.println(C_LO);
            }
            if (THROTTLE_DEBUG_MODE){
                Serial.print("Throttle output: ");
                Serial.println(dutyCycle);
            }
        }
    }

    if (hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);

        analogWrite(PIN_MOSFET_B_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
    } else if (hallA && !hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);

        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);

        analogWrite(PIN_MOSFET_A_HI, dutyCycle);
        analogWrite(PIN_MOSFET_B_LO, dutyCycle);
    } else if (hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_HI, 0);

        analogWrite(PIN_MOSFET_A_HI, dutyCycle);
        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
    } else if (!hallA && hallB && !hallC) {
        analogWrite(PIN_MOSFET_A_LO, 0);
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);

        analogWrite(PIN_MOSFET_C_HI, 0);

        analogWrite(PIN_MOSFET_B_HI, dutyCycle);
        analogWrite(PIN_MOSFET_C_LO, dutyCycle);
    } else if (!hallA && hallB && hallC) {
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);
        analogWrite(PIN_MOSFET_C_HI, 0);

        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_B_HI, dutyCycle);
    } else if (!hallA && !hallB && hallC) {
        analogWrite(PIN_MOSFET_A_HI, 0);

        analogWrite(PIN_MOSFET_B_LO, 0);
        analogWrite(PIN_MOSFET_B_HI, 0);

        analogWrite(PIN_MOSFET_C_LO, 0);

        analogWrite(PIN_MOSFET_A_LO, dutyCycle);
        analogWrite(PIN_MOSFET_C_HI, dutyCycle);
    }
}
