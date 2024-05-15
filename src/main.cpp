#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin1 = 8;    // Player 1 button
const int buttonPin2 = 9;    // Player 2 button

int score1 = 0;
int score2 = 0;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Print the initial scores
  lcd.setCursor(0, 0);
  lcd.print("Player 1: 0");
  lcd.setCursor(0, 1);
  lcd.print("Player 2: 0");

  // Set up the button pins as inputs with pull-up resistors
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
  // Check if Player 1's button is pressed
  if (digitalRead(buttonPin1) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(buttonPin1) == LOW) {
      score1++;
      updateScore(1, score1);
      while (digitalRead(buttonPin1) == LOW); // Wait for button release
    }
  }

  // Check if Player 2's button is pressed
  if (digitalRead(buttonPin2) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(buttonPin2) == LOW) {
      score2++;
      updateScore(2, score2);
      while (digitalRead(buttonPin2) == LOW); // Wait for button release
    }
  }
}

void updateScore(int player, int score) {
  if (player == 1) {
    lcd.setCursor(10, 0);
    lcd.print(score);
  } else if (player == 2) {
    lcd.setCursor(10, 1);
    lcd.print(score);
  }
}
