#include <Servo.h>
#include <LiquidCrystal.h> 

// Define pin constants for servos
#define SERVO_X_PIN 9
#define SERVO_Y_PIN 8
#define SERVO_Z_PIN 7

// Define constants for delay times
#define DELAY_TIME 1000

// Create Servo objects for each axis
Servo servoX;
Servo servoY;
Servo servoZ;

// Create an LCD object (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Attach servos to their respective pins
  servoX.attach(SERVO_X_PIN);
  servoY.attach(SERVO_Y_PIN);
  servoZ.attach(SERVO_Z_PIN);
  
  // Initialize the LCD
  lcd.begin(16, 2);

  // Start serial communication
  Serial.begin(9600);

  // Print initial message on the LCD
  lcd.print("Enter angles");
}

// Function to read angle input for a specific axis
int readAngle(char axis) {
  int angle;
  while (true) {
    // Prompt user for input
    Serial.print("Enter angle for axis ");
    Serial.print(axis);
    Serial.println(" (0-180): ");
    while (Serial.available() == 0) {}
    angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180) {
      return angle;
    } else {
      Serial.println("Invalid angle! Please enter a value between 0 and 180.");
    }
  }
}

// Function to move a servo to a specified position
void move(int pos, Servo &motor, char axis) {
  motor.write(pos);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Axis ");
  lcd.print(axis);
  lcd.print(": ");
  lcd.print(pos);
  lcd.print(" deg");
  delay(DELAY_TIME);
}

void loop() {
  // Read user input for x, y, z angles
  int angleX = readAngle('X');
  int angleY = readAngle('Y');
  int angleZ = readAngle('Z');

  // Move the servos to the specified positions
  move(angleX, servoX, 'X');
  move(angleY, servoY, 'Y');
  move(angleZ, servoZ, 'Z');

  // Display final positions on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Angles: ");
  lcd.setCursor(0, 1);
  lcd.print(angleX);
  lcd.print(",");
  lcd.print(angleY);
  lcd.print(",");
  lcd.print(angleZ);

  // Delay before exiting
  delay(DELAY_TIME);
  exit(0); // Terminate the program
}
