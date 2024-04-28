#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdbool.h>

// GPIO pin definition
#define BUTTON_PIN 17 // GPIO pin for main button

// Serial communication settings
#define SERIAL_DEVICE "/dev/ttyAMA0"
#define BAUD_RATE 9600

// Debounce time for button in milliseconds
#define DEBOUNCE_TIME 50

// Main loop delay time in milliseconds
#define LOOP_DELAY_TIME 1000

// Function prototypes
void configureIO(void);
void buttonInterrupt(void);

// Global variables
volatile int counter = 0;
volatile unsigned long lastInterruptTime = 0;

// Setup GPIO pins
void configureIO(void) {
    pinMode(BUTTON_PIN, INPUT);
    pullUpDnControl(BUTTON_PIN, PUD_UP);
}

// Interrupt handler for button press
void buttonInterrupt(void) {
    unsigned long interruptTime = millis();

    // Debounce check
    if (interruptTime - lastInterruptTime > DEBOUNCE_TIME) {
        counter++; // Increment the counter
        lastInterruptTime = interruptTime;
    }
}

int main() {
    int serial_port;

    // Initialize WiringPi library
    if (wiringPiconfigureIO() < 0) {
        fprintf(stderr, "Unable to start WiringPi: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Configuration of interruption function
    if (wiringPiISR(BUTTON_PIN, INT_EDGE_FALLING, &buttonInterrupt) < 0) {
        fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Setup GPIO pins
    configureIO();

    // Open serial port
    if ((serial_port = serialOpen(SERIAL_DEVICE, BAUD_RATE)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Main loop
    while (true) {
        // Example of a main loop action (blink LED, etc.)
        delay(LOOP_DELAY_TIME);
    }

    return EXIT_SUCCESS;
}
