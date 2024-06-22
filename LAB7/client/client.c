#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "messageclient.h"
#include "config.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s SERVER_IP SERVER_PORT [--file <filename>] [--interval <ms>] [--duration <s>] [--protocol <TCP|UDP>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    char *filename = NULL;
    int interval = DEFAULT_INTERVAL;
    int duration = DEFAULT_DURATION;
    char *protocol = DEFAULT_PROTOCOL;

    // Parse command line arguments
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "--interval") == 0 && i + 1 < argc) {
            interval = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--duration") == 0 && i + 1 < argc) {
            duration = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--protocol") == 0 && i + 1 < argc) {
            protocol = argv[++i];
        }
    }

    printf("Server IP: %s\n", server_ip);
    printf("Server Port: %d\n", server_port);
    printf("Interval: %d ms\n", interval);
    printf("Duration: %d s\n", duration);
    printf("Protocol: %s\n", protocol);

    msg_client(server_ip, server_port, filename, interval, duration, protocol);
    
    return 0;
}
