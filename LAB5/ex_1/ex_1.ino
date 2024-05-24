#include <Servo.h>

// Create a Servo object
Servo myServo;

const int potPin = A0;
const int servoPin = 9;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
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

  // Small delay to smooth the servo movement
  delay(15);  
}
