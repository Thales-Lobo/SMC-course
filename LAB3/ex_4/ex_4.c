#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define SERIAL_SETUP_TIME	100
#define DEFAULT_SCAPE_CHARACTER	's'	

void sendCharToArduino(int fd, char c);
void readAndProcessInput(int fd);

void sendCharToArduino(int fd, char character){
	serialPutchar(fd, character);
}

void readAndProcessInput(int fd){
	char character;
	
	while(character !=  DEFAULT_SCAPE_CHARACTER) {
		character = getchar();
		delay(SERIAL_SETUP_TIME);
	}
}

int main() {	
	int serial_port = serialOpen("/dev/ttyAMA0", 9600);
	
	if (serial_port < 0) {
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	if (wiringPiSetup() < 0) {
		fprintf(stdout, "Unable to start WiringPi: %s", strerror(errno));
		return EXIT_FAILURE;
	}
	
	printf("Type a character: \n");
	readAndProcessInput(serial_port);
	
	return EXIT_SUCCESS;
}
