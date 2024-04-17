#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

// PIN definitions
#define FIRST_BUTTON_PIN    17  //
#define SECOND_BUTTON_PIN   27  //  
#define LED_PIN             23  //

// Debounce and blink time configurations
#define BLINK_TIME_STEP      500  // Blink time step increment in milliseconds
#define DEFAULT_DELAY_TIME   500  // Default delay time in milliseconds for main loop
#define BOUNCE_TIME_INTERVAL 200  // Default bounce time in milliseconds
#define BLINK_TIME_MIN       500  // Minimum blink time in milliseconds
#define BLINK_TIME_MAX       3000 // Maximum blink time in milliseconds

// Global variables
volatile bool ledBlinkActivate = false;             // Flag to control LED blinking activation
volatile unsigned long lastInterruptFirstBtn = 0;   // Last interrupt time for first button
volatile unsigned long lastInterruptSecondBtn = 0;  // Last interrupt time for second button
unsigned long blinkTime = BLINK_TIME_MIN;           // Current blink time

// Function prototypes
void configureIO(void);
void firstBtnInterrupt(void);
void secondBtnInterrupt(void);
void blinkLed(bool ledBlinkActivateState);
void adjustBlinkTime(void);

// Configure GPIO pins
void configureIO(void) {
    pinMode(LED_PIN, OUTPUT);
    pinMode(FIRST_BUTTON_PIN, INPUT);
    pinMode(SECOND_BUTTON_PIN, INPUT);
    pullUpDnControl(FIRST_BUTTON_PIN, PUD_UP);
    pullUpDnControl(SECOND_BUTTON_PIN, PUD_UP);
}

// Interrupt handler for first button
void firstBtnInterrupt(void) {
    unsigned long currentInterrupt = millis();
    
    // Check for debounce
    if((currentInterrupt - lastInterruptFirstBtn) > BOUNCE_TIME_INTERVAL) {
        ledBlinkActivate = !ledBlinkActivate;
        lastInterruptFirstBtn = currentInterrupt;
    }
}

// Interrupt handler for second button
void secondBtnInterrupt(void) {
    unsigned long currentInterrupt = millis()
    
    // Check for debounce
    if((currentInterrupt - lastInterruptSecondBtn) > BOUNCE_TIME_INTERVAL) {
        adjustBlinkTime();                       
        lastInterruptSecondBtn = currentInterrupt;
    }
}

// Blink LED based on activation state
void blinkLed(bool ledBlinkActivateState) {
    if(ledBlinkActivateState) {
        digitalWrite(LED_PIN, HIGH);
        delay(blinkTime);
        digitalWrite(LED_PIN, LOW);
        delay(blinkTime);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}

// Adjust blink time with limits
void adjustBlinkTime(void) {
    blinkTime += BLINK_TIME_STEP;
    
    // Check if blink time exceeds maximum
    if(blinkTime > BLINK_TIME_MAX) {
        blinkTime = BLINK_TIME_MIN;
    }
}

int main() {
    // Initialize WiringPi library
    if(wiringPiSetupGpio() < 0) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // General PINs configuration
    configureIO();
    
    // Configure interrupt handlers
    if(wiringPiISR(FIRST_BUTTON_PIN, INT_EDGE_FALLING, &firstBtnInterrupt) < 0 || 
       wiringPiISR(SECOND_BUTTON_PIN, INT_EDGE_FALLING, &secondBtnInterrupt) < 0) {
        fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // Main loop for LED blinking
    while(true) {
        blinkLed(ledBlinkActivate);
        delay(DEFAULT_DELAY_TIME)
    }
    
    return EXIT_SUCCESS;
}
