// Initialize variables for the servos
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
#include <Servo.h>

Servo myservo1;  // Create two servo objects to control the servos
Servo myservo2;

int pos1 = 0;    // Variable to store the position of servo1
int pos2 = 0;    // Variable to store the position of servo2

const int buttonPin1 = 7; // Save button pins as variable
const int buttonPin2 = 8;
const int buttonPin3 = 11;
const int buttonPin4 = 9;

int buttonstate1 = 0; // Buttonstate 1-4 will store whether the buttons are pressed or not
int buttonstate2 = 0;
int buttonstate3 = 0;
int buttonstate4 = 0;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

// Initialize variables for LEDs
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
int redlevel = 255; // Integers to store the values of each color
int bluelevel = 0;
int greenlevel = 255;

const int redpin = 3; // Save pmw voltage pins as variables
const int greenpin = 5;
const int bluepin = 6;

bool lightpower = LOW;  // Set variables to check if the light control buttons are on
bool lightforward = LOW;
bool lightbackward = LOW;
bool lightauto = LOW;

const int lightpin1 = A0; // Save light pins as variable
const int lightpin2 = A1;
const int lightpin3 = A3;
const int lightpin4 = A2;

// Define turnServo() and buttonDebounce() functions
void turnServo();
void buttonDebounce(const int lightpin);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

void setup() {

  // Setup for the servos
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
  myservo1.attach(10);  // Attaches the servo on pin 10 to the servo object
  myservo2.attach(12);  // Attaches the servo on pin 11 to the servo object

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

  // Setup for the LEDs
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
  pinMode(lightpin1, INPUT); // Configure lightpins as inputs
  pinMode(lightpin2, INPUT);
  pinMode(lightpin3, INPUT);
  pinMode(lightpin4, INPUT);

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
}

// Main Loop
void loop() {
  
  // Reads the on/off button
  if (digitalRead(lightpin1) == HIGH) {
    lightpower = !lightpower;
    buttonDebounce(lightpin1);
  }

  // Loop runs until the on/off button is pressed
  while (lightpower == HIGH) {
    analogWrite(redpin, redlevel); // Turn LEDs on
    analogWrite(greenpin, greenlevel);
    analogWrite(bluepin, bluelevel);
  
  
    // Check if the auto cycling button is pressed
    if (digitalRead(lightpin4) == HIGH) {
      lightauto = !lightauto; // If the auto button is pressed, switch the value of lightauto
      buttonDebounce(lightpin4);
    }

    // Update LED variables for auto cycling
    if (lightauto == HIGH) {
      // Blue to red transition
      if (bluelevel == 0 || (bluelevel < 255 && redlevel < 255 )) {
        bluelevel += 1;
        redlevel -= 1;
      }
      // Red to green transition
      else if (redlevel == 0 || (redlevel < 255 && greenlevel < 255 )) {
        redlevel += 1;
        greenlevel -=1;
      }
      // Green to blue transition
      else if (greenlevel == 0 || (greenlevel < 255 && bluelevel < 255 )) {
        greenlevel += 1;
        bluelevel -= 1;
      }
      delay(25);
    }   

    // Manuel cycle from blue to red to green
    if (digitalRead(lightpin2) == HIGH){
      // Blue to red transition
      if (bluelevel == 0 || (bluelevel < 255 && redlevel < 255 )) {
        bluelevel += 1;
        redlevel -= 1;
      }
      // Red to green transition
      else if (redlevel == 0 || (redlevel < 255 && greenlevel < 255 )) {
        redlevel += 1;
        greenlevel -=1;
      }
      // green to blue transition
      else if (greenlevel == 0 || (greenlevel < 255 && bluelevel < 255 )) {
        greenlevel += 1;
        bluelevel -= 1;
      }

      analogWrite(bluepin, bluelevel); // write led levels to bulbs
      analogWrite(redpin, redlevel);
      analogWrite(greenpin, greenlevel);
    }

    // Manuel cycle from blue to green to red
    if (digitalRead(lightpin3) == HIGH) {
      // blue to green transition
      if (bluelevel == 0 || (bluelevel < 255 && greenlevel < 255 )) {
        bluelevel += 1;
        greenlevel -= 1;
      }
      // green to red transition
      else if (greenlevel == 0 || (greenlevel < 255 && redlevel < 255 )) {
        greenlevel += 1;
        redlevel -= 1;
      }
      // red to blue transition
      else if (redlevel == 0 || (redlevel < 255 && bluelevel < 255 )) {
        redlevel += 1;
        bluelevel -=1;
      }

      analogWrite(bluepin, bluelevel); // write led levels to bulbs
      analogWrite(redpin, redlevel);
      analogWrite(greenpin, greenlevel);
    } 
    
    // Call the turnServo function 
    turnServo();

    if (digitalRead(lightpin1) == HIGH) {
      lightpower = !lightpower;
      buttonDebounce(lightpin1);
    }

    delay(25);
  }

  analogWrite(redpin, 255); // if the light was pressed off, turn LEDs off
  analogWrite(greenpin, 255);
  analogWrite(bluepin, 255);

}

// Servo Turning Function
void turnServo(){

  buttonstate1 = digitalRead(buttonPin1); // read if the buttons are on/off
  buttonstate2 = digitalRead(buttonPin2);
  buttonstate3 = digitalRead(buttonPin3);
  buttonstate4 = digitalRead(buttonPin4);

  // SERVO 1
  while (buttonstate1 == HIGH && pos1 <= 180) {
    pos1 += 1; // increases pos variable
    myservo1.write(pos1); // turns the servo
    buttonstate1 = digitalRead(buttonPin1); // check to see if button is pressed 
    delay(5);
  }
  
  while (buttonstate2 == HIGH && pos1 >= 0) {
    pos1 -= 1; // increases pos variable
    myservo1.write(pos1); // turns the servo
    buttonstate2 = digitalRead(buttonPin2); // check to see if button is pressed
    delay(5);
  }

  // SERVO 2
  while (buttonstate3 == HIGH && pos2 <= 180) {
    pos2 += 1; // increases pos variable
    myservo2.write(pos2); // turns the servo
    buttonstate3 = digitalRead(buttonPin3); // check to see if button is pressed 
    delay(5);
  }
  
  while (buttonstate4 == HIGH && pos2 >= 0) {
    pos2 -= 1; // increases pos variable
    myservo2.write(pos2); // turns the servo
    buttonstate4 = digitalRead(buttonPin4); // check to see if button is pressed
    delay(5);
  }
}

// Button Debouncing Function
void buttonDebounce(const int lightpin){
  while (digitalRead(lightpin) == HIGH){
    delay(5); // delay until the user takes their finger off button
  }
}
