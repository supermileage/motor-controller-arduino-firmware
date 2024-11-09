#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define HALL_SENSOR_PIN 3

// OLED display TWI address
#define OLED_ADDR   0x3C

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  Serial.begin(9600);              // Start serial communication
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);   // Set hall sensor pin as input
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING); // Trigger on rising edge

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,30);
  display.print("Setup Complete");

  // update display with all of the above graphics
  display.display();
}

// Define pin for hall sensor
volatile int pulseCount = 0;   // Variable to store pulse count
unsigned long lastMillis = 0;  // Time in milliseconds at the last RPM calculation

// Time interval to calculate RPM (in milliseconds)
const unsigned long interval = 3000; // 100 ms interval

// Number of pulses per revolution based on the motor's design
// Adjust this value based on the number of hall sensor pulses per revolution
const int pulsesPerRevolution = 5; // Pin has a falling edge 5 times per revolution

void countPulse() {
  pulseCount++; // Increment pulse count on each hall sensor pulse
}

/*
void setup() {
  Serial.begin(9600);              // Start serial communication
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);   // Set hall sensor pin as input
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING); // Trigger on rising edge
}*/

void loop() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - lastMillis >= interval) {
    // Calculate RPM
    int rpm = (pulseCount / (float)pulsesPerRevolution) * (60000.0 / interval);

    // Print RPM to the serial monitor
    Serial.print("RPM: ");
    Serial.println(rpm);


    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10,30);
    display.print("RPM:");
    display.print(rpm);
    display.display();

    // Reset pulse count and lastMillis for the next interval
    pulseCount = 0;
    lastMillis = currentMillis;
  }
}
