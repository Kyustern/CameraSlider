#include <Arduino.h>
// Assign output variable to GPIO pin
const int output = 8;

void setup() {
    Serial.begin(115200);
    // setup output on-board LED
    pinMode(output, OUTPUT);
}
void loop() {
    Serial.println("Hello World");
    digitalWrite(output, HIGH);  // Flash built-in LED
    delay(200);
    digitalWrite(output, LOW);
    delay(200);
}