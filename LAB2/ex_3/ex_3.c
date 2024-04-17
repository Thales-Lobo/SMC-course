#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>

// PIN definitions
#define BUTTON_PIN              17                  // Main button associated PIN
#define LED_PINS                {23, 24, 25, 26}    // Array of LED pins

// Constants
#define NUM_LEDS                4   // Number of leds in the circuit 
#define BOUNCE_TIME_INTERVAL    200 // Default bounce time in milliseconds
#define DEFAULT_DELAY_TIME      500 // Default delay time in milliseconds for main loop


// Global variables
volatile int currentLed = 0; // Index of currently lit LED
volatile unsigned long lastInterrupt = 0; // Last interrupt time for main button

// Function prototypes
void configureIO(void);
void btnInterrupt(void);
void turnOnNextLed(void);

// PIN definitions
void configureIO(void) {
    // Configure LED pins as outputs and initialize them as LOW
    const int ledPins[NUM_LEDS] = LED_PINS;
    for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
        pinMode(ledPins[ledIndex], OUTPUT);
        digitalWrite(ledPins[ledIndex], LOW);
    }
    
    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_UP);
}

// Interrupt handler for first button
void btnInterrupt(void) {
    unsigned long currentInterrupt = millis();
    
    // Check for debounce
    if ((currentInterrupt - lastInterrupt) > BOUNCE_TIME_INTERVAL) {
        turnOnNextLed();
        lastInterrupt = currentInterrupt;
    }
}

void turnOnNextLed(void) {
    // Main array of leds
    const int ledPins[NUM_LEDS] = LED_PINS;
    
    // Turn off all LEDs
    for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
        digitalWrite(ledPins[ledIndex], LOW);
    }
    
    // Light the next LED
    digitalWrite(ledPins[currentLed], HIGH);
    
    // Update currentLed index for the next LED
    currentLed = (currentLed + 1) % NUM_LEDS;
}

int main() {
    // Initialize WiringPi library
    if (wiringPiSetupGpio() < 0) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // General PINs configuration
    configureIO();
    
    // Configure interrupt handler for button
    if (wiringPiISR(BUTTON_PIN, INT_EDGE_FALLING, &btnInterrupt) < 0) {
        fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    // Main loop
    while (true) {
        delay(DEFAULT_DELAY_TIME);
    }
    
    return EXIT_SUCCESS;
}
