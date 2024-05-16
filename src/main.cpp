#include <Arduino.h>

// Pin definitions for buttons
const int buttonPin1 = 0;
const int buttonPin2 = 12;

// Variables to hold button states
int buttonState1 = 0;
int buttonState2 = 0;

// Score digits for Team A and Team B
int A = 0; // Tens digit of Team A's score
int B = 0; // Ones digit of Team A's score
int C = 0; // Tens digit of Team B's score
int D = 0; // Ones digit of Team B's score

// PWM pins for the 7-segment display digits
int digit1 = 6; // Most left display
int digit2 = 9; // Second left display
int digit3 = 10; // Second right display
int digit4 = 11; // Most right display

// Define the states for digit control
#define DIGIT_ON  LOW
#define DIGIT_OFF HIGH
#define DISPLAY_BRIGHTNESS 500

// Segment pin definitions
int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = A0; // Pin 6 is used by display 1 for its PWM function
int segF = 7;
int segG = 8;

void setup() {
  // Initialize button pins as input
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  
  // Initialize segment pins as output
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  
  // Initialize digit control pins as output
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  // Begin serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read button states
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // Increase score for Team A if button 1 is pressed
  if (buttonState1 == HIGH) {
    B++;
    if (B > 9) {
      B = 0; // Reset to 0 if it reaches 10
      A++;
    }
    if (A > 9) {
      A = 0; // Prevent tens digit from exceeding 9
    }
  }

  // Increase score for Team B if button 2 is pressed
  if (buttonState2 == HIGH) {
    D++;
    if (D > 9) {
      D = 0; // Reset to 0 if it reaches 10
      C++;
    }
    if (C > 9) {
      C = 0; // Prevent tens digit from exceeding 9
    }
  }

  // Display scores for Team A and Team B
  displayScore(A, B, C, D);

  // Print scores to serial monitor for debugging
  Serial.print("Team A: ");
  Serial.println(A * 10 + B); // Convert tens and ones to a single number
  Serial.print("Team B: ");
  Serial.println(C * 10 + D); // Convert tens and ones to a single number
}

void displayScore(int scoreA_tens, int scoreA_ones, int scoreB_tens, int scoreB_ones) {
  // Display Team A score on the left side
  displayNumber(scoreA_tens, digit1, digit2);
  B = scoreA_ones;

  // Display Team B score on the right side
  displayNumber(scoreB_tens, digit3, digit4);
  D = scoreB_ones;
}

void displayNumber(int numberToDisplay, int digitLeft, int digitRight) {
  // Extract each digit of the score
  int thousands = numberToDisplay / 1000;
  int hundreds = (numberToDisplay % 1000) / 100;
  int tens = (numberToDisplay % 100) / 10;
  int ones = numberToDisplay % 10;

  // Turn off all digits initially
  digitalWrite(digit1, DIGIT_OFF);
  digitalWrite(digit2, DIGIT_OFF);
  digitalWrite(digit3, DIGIT_OFF);
  digitalWrite(digit4, DIGIT_OFF);

  // Display each digit sequentially
  digitalWrite(digitLeft, DIGIT_ON);
  lightNumber(thousands);
  delayMicroseconds(DISPLAY_BRIGHTNESS);
  digitalWrite(digitLeft, DIGIT_OFF);

  digitalWrite(digitRight, DIGIT_ON);
  lightNumber(hundreds);
  delayMicroseconds(DISPLAY_BRIGHTNESS);
  digitalWrite(digitRight, DIGIT_OFF);

  digitalWrite(digitLeft, DIGIT_ON);
  lightNumber(tens);
  delayMicroseconds(DISPLAY_BRIGHTNESS);
  digitalWrite(digitLeft, DIGIT_OFF);

  digitalWrite(digitRight, DIGIT_ON);
  lightNumber(ones);
  delayMicroseconds(DISPLAY_BRIGHTNESS);
  digitalWrite(digitRight, DIGIT_OFF);
}

void lightNumber(int numberToDisplay) {
  // Define segment states
  #define SEGMENT_ON  HIGH
  #define SEGMENT_OFF LOW

  // Control segments to display the corresponding number
  switch (numberToDisplay) {
    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
  }
}
