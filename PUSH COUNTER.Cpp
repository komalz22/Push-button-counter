#include <LiquidCrystal.h>

// LCD pin connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int buttonPin = 2;    // Pin connected to the push button
volatile int buttonCount = 0; // Counter for button presses
bool lastButtonState = LOW; // Stores last button state
unsigned long lastDebounceTime = 0; // Debouncing
const int debounceDelay = 50; // 50ms debounce delay

void setup() {
  lcd.begin(16, 2); // Initialize LCD with 16x2 size
  lcd.print("Button Counter");
  lcd.setCursor(0, 1); // Move to the second line
  lcd.print("Count: 0");

  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up
  attachInterrupt(digitalPinToInterrupt(buttonPin), countButton, FALLING); // Interrupt on button press
}

void loop() {
  // Update LCD with current count
  lcd.setCursor(7, 1); // Move to display count
  lcd.print(buttonCount);
  delay(100); // Small delay to avoid flickering
}

void countButton() {
  // Debounce logic
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    buttonCount++; // Increment the counter
  }
}
