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
#define NUM_LEDS                4   // Number of LEDs in the circuit 
#define BOUNCE_TIME_INTERVAL    200 // Default bounce time in milliseconds
#define DEFAULT_DELAY_TIME      500 // Default delay time in milliseconds for main loop

// Global variables
volatile int currentLed = 0;            // Index of currently lit LED
volatile unsigned long lastInterrupt = 0;// Last interrupt time for main button

// Function prototypes
void configureIO(void);
void btnInterrupt(void);
void turnOnNextLed(void);

// Configure GPIO pins for LEDs and button
void configureIO(void) {
    const int ledPins[NUM_LEDS] = LED_PINS; // Array of LED pins
    
    // Configure LED pins
    for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
        pinMode(ledPins[ledIndex], OUTPUT);
        digitalWrite(ledPins[ledIndex], LOW);
    }
    
    // Configure button pin
    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_UP);
}

// Interrupt handler for the main button
void btnInterrupt(void) {
    unsigned long currentInterrupt = millis();
    
    // Check for debounce
    if ((currentInterrupt - lastInterrupt) > BOUNCE_TIME_INTERVAL) {
        turnOnNextLed();
        lastInterrupt = currentInterrupt;
    }
}

// Activate the next LED in sequence
void turnOnNextLed(void) {
    // Array of LED pins
    const int ledPins[NUM_LEDS] = LED_PINS;
    
    // Light the next LED and keep previous LEDs on
    digitalWrite(ledPins[currentLed], HIGH);
    
    // Turn off all LEDs except the ones before currentLed
    for (int ledIndex = currentLed + 1; ledIndex < NUM_LEDS; ledIndex++) {
        digitalWrite(ledPins[ledIndex], LOW);
    }
    
    // Update currentLed index
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
    
    // Configure interrupt handler for main button
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
