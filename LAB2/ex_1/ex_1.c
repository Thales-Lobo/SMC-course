#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>


#define LED_PIN		23                                                                               
#define BUTTON_PIN	17

#define BOUNCE_TIME_INTERVAL	200
#define BLINK_TIME_CONSTANT		1000
#define DEFAULT_DELAY_TIME		500

volatile bool ledBlinkActivate = false;
volatile unsigned long lastInterrupt = 0;

void configureIO(void);
void btnInterrupt(void);
void blinkLed(bool ledBlinkActivateState);

void configureIO(void) {
	pinMode(LED_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
	pullUpDnControl(BUTTON_PIN, PUD_UP);
}

void btnInterrupt(void) {
	unsigned long currentInterrupt = millis();
	
	if((currentInterrupt - lastInterrupt) > BOUNCE_TIME_INTERVAL) {
		ledBlinkActivate = !ledBlinkActivate;
		lastInterrupt = currentInterrupt;
	}
}

void blinkLed(bool ledBlinkActivateState) {
	printf("ledBlinkActivateState: %d\n", ledBlinkActivateState);
	if(ledBlinkActivateState) {
		digitalWrite(LED_PIN, HIGH);
		delay(BLINK_TIME_CONSTANT);
		digitalWrite(LED_PIN, LOW);
		delay(BLINK_TIME_CONSTANT);
	} else {
		digitalWrite(LED_PIN, LOW);
	}
}

int main() {
	// Initializes and verifies WiringPi library
	if(wiringPiSetupGpio() < 0) {
		fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	// General PINs configuration
	configureIO();
	
	// Configuration of interruption function
	if(wiringPiISR(BUTTON_PIN, INT_EDGE_FALLING, &btnInterrupt) < 0) {
		fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	// Executes main loop for led blinking
	while(true) {
		blinkLed(ledBlinkActivate);
		delay(DEFAULT_DELAY_TIME);
	}
	
	return EXIT_SUCCESS;
}	
