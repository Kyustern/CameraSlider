#include <Arduino.h>

// Constants
const int STEPPER_DELAY_µs = 100;
const int STEPS_RANGE = 1000; // The number of steps for a full cycle (can be adjusted)
const int moveDelay = 10;      // Delay in milliseconds between steps for motor control

// pins
const int buttonPin = D8;       // Button pin, normally open (LOW)
const int limitSwitchPin = D7;  // Limit switch pin, normally closed (HIGH)
const int dirPin = D4;           // DIR pin for A4988
const int stepPin = D3;          // STEP pin for A4988

// Variables
volatile bool motorMoving = false;  // Flag to check if the motor is moving
bool isForward = false;  // Flag to keep track of the motor direction
int stepsToEnd = 0;        // Number of steps to reach the limit switch
int currentPosition = 0;      // Keeps track of the current number of steps


//Lib
bool isInRange(int value, int min, int max) {
    if (min > max) {
        Serial.print("Invalid range check, min cannot be greater than max");
    }
    return (value >= min) && (value <= max);
}


void stepMotor(int delay) {
  //Check whether the next pos if physically possible
  int nextPos = currentPosition;
  if (isForward) nextPos =+ 1;
  else nextPos =+ -1;
  if (isInRange(nextPos, 0, STEPS_RANGE)){
    currentPosition = nextPos;
    //else we cancel stepMotor
  } else return;
  
  //The stepper driver expect a certain delay inbetween level changes
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(STEPPER_DELAY_µs); 
  digitalWrite(stepPin, LOW);
  delayMicroseconds(STEPPER_DELAY_µs);
}

void setStepperDirection(boolean forward) {
  isForward = forward;
  if (isForward) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
}

//Homing the cariage
//Shortly after the start of the program, we need to initiate a calibration phase where we directly set motorDirection to true, and run the motor until it hits a switch that is normally closed
//Controling the carriage position using PID on the stepMotor delay parameter
//If we are far from the desired position the delay is the shortest possible (TO BE DETERMINED) for the fastest speed, and when close to the position the speed of the stepper shall slow down.
//The required position would be set following an interrupt on one of the MCU pins.
//The actual position would be kept as a global variable. Each time we call stepDir we either increment or decrement the position variable, depending on the current motorDirection value.
//Each time loop() runs the program runs a PID computation to figure out what the delay of stepDir should be, repspective to a maximum and minimum value, and then calls stepDir.


int home () {
  Serial.println("HOMING...");
  int homeSteps = 0;
  motorMoving = true;
  while (digitalRead(limitSwitchPin) == HIGH) {
    //Reading debounce (necessary ??)
    delayMicroseconds(STEPPER_DELAY_µs/2);
    stepMotor(100);
    homeSteps ++;
    yield();
  }
  motorMoving = false;
  Serial.println("HOMING OVER");
    Serial.print("Range steps : "); Serial.println(homeSteps);
  return homeSteps;
}

// void IRAM_ATTR registerButtonPress() {
//   motorMoving = true;
//   setStepperDirection(true);
//   for (size_t i = 0; i < stepsToEnd; i++) {
//     stepMotor(100);
//   }
//   motorMoving = false;
// }

void setup() {
  Serial.begin(9600);

  // Initialize pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button with internal pull-up
  pinMode(limitSwitchPin, INPUT_PULLUP); // Limit switch with internal pull-up
  
  // Start with the motor in the "at rest" position
  setStepperDirection(true);
  stepsToEnd = home();
  delay(1000);

  // attachInterrupt(digitalPinToInterrupt(buttonPin), registerButtonPress, RISING);
}

void loop() {
  int reading = digitalRead(limitSwitchPin);
  Serial.print("reading : "); Serial.println(reading);
  delay(50);
}
