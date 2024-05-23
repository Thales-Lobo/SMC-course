#include <LiquidCrystal.h>

// Define pin numbers for the potentiometer and LCD
#define POTENTIOMETER_PIN A0    // Pin for the potentiometer (analog input A0)
#define SCREEN_WIDTH 16     // Width of the LCD screen
#define SCREEN_HEIGHT 2     // Height of the LCD screen
#define UPDATE_DELAY 100    // Time (in milliseconds) of screen update
#define LCD_RS 12           // Register Select pin for the LCD
#define LCD_EN 11           // Enable pin for the LCD
#define LCD_D4 5            // Data pin D4 for the LCD
#define LCD_D5 4            // Data pin D5 for the LCD
#define LCD_D6 3            // Data pin D6 for the LCD
#define LCD_D7 2            // Data pin D7 for the LCD

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // Initialize the LCD
  lcd.begin(SCREEN_WIDTH, SCREEN_HEIGHT);
  lcd.clear();
  lcd.print("Potentiometer Value: ");
}

void loop() {
  // Read the value from the potentiometer
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  
  // Set the cursor to the position where the potentiometer value will be displayed
  lcd.setCursor(10, 0);
  
  // Clear the previous value before printing the new value
  lcd.print("    ");
  lcd.setCursor(10, 0);
  
  // Print the potentiometer value
  lcd.print(potentiometerValue);
  
  // LCD delay constant
  delay(UPDATE_DELAY);
}
