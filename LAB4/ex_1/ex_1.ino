#include <LiquidCrystal.h>

// Define pin numbers for the push-button and LCD
#define BUTTON_PIN 13       // Counter button PIN
#define SCREEN_WIDTH 16     // Width of the LCD screen
#define SCREEN_HEIGHT 2     // Height of the LCD screen
#define LCD_RS 12           // Register Select pin for the LCD
#define LCD_EN 11           // Enable pin for the LCD
#define LCD_D4 5            // Data pin D4 for the LCD
#define LCD_D5 4            // Data pin D5 for the LCD
#define LCD_D6 3            // Data pin D6 for the LCD
#define LCD_D7 2            // Data pin D7 for the LCD

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS,LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Deboucing variables
volatile unsigned long lastButtonPress = 0;
unsigned long debounceDelay = 50;
// Global counter
unsigned long count = 0;

void setup() {
  // Set the button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Attach an interrupt to the button pin, call buttonPressed function on RISING edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPressed, RISING);

  // Initialize the LCD
  lcd.begin(SCREEN_WIDTH, SCREEN_HEIGHT);
  lcd.clear();
  lcd.print("Counter: ");
}

// Loop function runs continuously after the setup function
void loop() {
  lcd.setCursor(10, 0);
  lcd.print(count);
}

// Interrupt service routine for the button press
void buttonPressed() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastButtonPress > debounceDelay) {
    lastButtonPress = currentMillis;
    count++;
  }
}
