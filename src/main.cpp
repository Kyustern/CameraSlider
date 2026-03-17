// #include <Arduino.h>

// // Constants
// const int STEPPER_DELAY_µs = 100;
// const int STEPS_RANGE = 1000;

// // Define pins
// const int buttonPin = D8;       // Button pin, normally open (LOW)
// const int limitSwitchPin = D7;  // Limit switch pin, normally closed (HIGH)
// const int dirPin = D4;           // DIR pin for A4988
// const int stepPin = D3;          // STEP pin for A4988

// // Variables
// volatile bool motorMoving = false;  // Flag to check if the motor is moving
// bool motorDirection = false;  // Flag to check if the motor is moving
// int stepsToEnd = 0;        // Number of steps to reach the limit switch
// int currentSteps = 0;      // Keeps track of the current number of steps

// // Constants
// const int stepsPerMove = 1000; // The number of steps for a full cycle (can be adjusted)
// const int moveDelay = 10;      // Delay in milliseconds between steps for motor control

// void stepMotor() {
//   // Make one step (pulse the STEP pin)
//   digitalWrite(stepPin, HIGH);
//   delayMicroseconds(STEPPER_DELAY_µs); // Pulse width (adjust for stepper motor speed)
//   digitalWrite(stepPin, LOW);
//   delayMicroseconds(STEPPER_DELAY_µs); // Pulse width (adjust for stepper motor speed)
// }

// void setDir(boolean forward) {
//   motorDirection = forward;
//   if (forward) {
//     digitalWrite(dirPin, HIGH);
//   } else {
//     digitalWrite(dirPin, LOW);
//   }
// }

// int home () {
//   Serial.println("HOMING...");
//   int homeSteps = 0;
//   motorMoving = true;
//   while (digitalRead(limitSwitchPin) == HIGH) {
//     //Reading debounce (necessary ??)
//     delayMicroseconds(STEPPER_DELAY_µs/2);
//     stepMotor();
//     homeSteps ++;
//   }
//   motorMoving = false;
//   Serial.println("HOMING OVER");
//   return homeSteps;
// }

// void IRAM_ATTR registerButtonPress() {
//   motorMoving = true;
//   setDir(true);
//   for (size_t i = 0; i < stepsToEnd; i++) {
//     stepMotor();
//   }
//   motorMoving = false;
// }

// void setup() {
//   Serial.begin(9600);
//   Serial.println(stepPin);
//   Serial.println(dirPin);

//   // Initialize pins
//   pinMode(stepPin, OUTPUT);
//   pinMode(dirPin, OUTPUT);
//   pinMode(buttonPin, INPUT_PULLUP); // Button with internal pull-up
//   pinMode(limitSwitchPin, INPUT_PULLUP); // Limit switch with internal pull-up
  
//   // Start with the motor in the "at rest" position
//   setDir(true);
//   stepsToEnd = home();

//   attachInterrupt(digitalPinToInterrupt(buttonPin), registerButtonPress, RISING);
// }

// void loop() {
//   int reading = digitalRead(limitSwitchPin);
//   Serial.print("reading : "); Serial.println(reading);
//   delay(50);
// }
