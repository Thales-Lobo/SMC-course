#include <Servo.h>        // Include the Servo library
#include <LiquidCrystal.h> // Include the LiquidCrystal library

#define DISPLAY_DELAY 150 // Delay to avoid noise effect

Servo myServo;            // Create a Servo object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Create an LCD object (RS, E, D4, D5, D6, D7)

const int potPin = A0;    // Define the pin for the potentiometer
const int servoPin = 9;   // Define the pin for the servo motor

void setup() {
  myServo.attach(servoPin);  // Attach the servo to the specified pin
  lcd.begin(16, 2);          // Initialize the LCD with 16 columns and 2 rows
  Serial.begin(9600);        // Start serial communication for monitoring
}

void loop() {
  // Read the potentiometer value (0 to 1023)
  int potValue = analogRead(potPin);  

  // Map the potentiometer value to a servo angle (-90 to 90 degrees)
  int angle = map(potValue, 0, 1023, -90, 90); 

  // Set the servo position (0 to 180 degrees, adjusted from -90 to 90)
  myServo.write(angle + 90);  

  // Print potentiometer value and corresponding servo angle for monitoring
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Servo Angle: ");
  Serial.println(angle);

  // Clear the LCD screen
  lcd.clear();

  // Set the cursor to the first column, first row
  lcd.setCursor(0, 0);
  // Print a message to the LCD
  lcd.print("Servo Angle:");

  // Set the cursor to the first column, second row
  lcd.setCursor(0, 1);
  // Print the angle to the LCD
  lcd.print(angle);

  // Small delay to smooth the servo movement
  delay(DISPLAY_DELAY);  
}
