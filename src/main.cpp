#include <SevSeg.h>
SevSeg sevseg;

const int buttonPin1 = A3;
const int buttonPin2 = A4;

int buttonState1 = 0;
int buttonState2 = 0;

int TeamAScore = 0;
int TeamBScore = 0;

int A = 0; // Tens digit of Team A's score
int B = 0; // Ones digit of Team A's score
int C = 0; // Tens digit of Team B's score
int D = 0; // Ones digit of Team B's score

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
  // Serial.begin(9600);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  if (buttonState1 == HIGH) {
    TeamAScore++;
    delay(250); // Simple debounce
  }
  
  if (buttonState2 == HIGH) {
    TeamBScore++;
    delay(250); // Simple debounce
  }

  // Calculate tens and ones digits for both scores
  A = TeamAScore / 10;
  B = TeamAScore % 10;
  C = TeamBScore / 10;
  D = TeamBScore % 10;
  
  // Combine the digits into a single number for display
  int displayNumber = A * 1000 + B * 100 + C * 10 + D;
  sevseg.setNumber(displayNumber,5);

  // Print scores to serial monitor
  Serial.print(displayNumber);
  Serial.print(",");
  Serial.print(TeamAScore);
  Serial.print(",");
  Serial.println(TeamBScore);

  // Update display
  sevseg.refreshDisplay();
}