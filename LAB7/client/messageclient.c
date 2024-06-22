#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "messageclient.h"
#include "config.h"

/**
 * Gets the current time in microseconds.
 *
 * @return The current time in microseconds.
 */
long get_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

/**
 * Ensures that the specified directory exists and opens a file in that directory.
 *
 * @param directory The directory to check/create.
 * @param filename The name of the file to open.
 * @param mode The mode in which to open the file (e.g., "w" for writing).
 * @return A pointer to the opened file, or NULL if the file could not be opened.
 */
FILE *open_file_in_directory(const char *directory, const char *filename, const char *mode) {
    struct stat st = {0};

    // Check if directory exists, create if it doesn't
    if (stat(directory, &st) == -1) {
        if (mkdir(directory, 0700) == -1) {
            perror("Error creating directory");
            return NULL;
        }
    }

    // Construct the full file path
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file
    FILE *file = fopen(filepath, mode);
    if (!file) {
        perror("Error opening file");
    }

    return file;
}

/**
 * Sends messages to a server at regular intervals and measures the response times.
 *
 * @param server_ip The IP address of the server.
 * @param server_port The port number of the server.
 * @param filename The name of the file to save the results.
 * @param interval The interval between messages in milliseconds.
 * @param duration The duration of the test in seconds.
 * @param protocol The communication protocol to use ("TCP" or "UDP").
 */
void msg_client(const char *server_ip, int server_port, const char *filename, int interval, int duration, const char *protocol) {
    FILE *file = NULL;
    if (filename) {
        file = open_file_in_directory(RESULT_DIRECTORY, filename, "w");
        if (!file) {
            return;
        }
    }

    int sock;
    struct sockaddr_in server_addr;

    // Create socket
    if (strcmp(protocol, "TCP") == 0) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation error");
            return;
        }
    } else { // Default to UDP
        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Socket creation error");
            return;
        }
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return;
    }

    // Connect for TCP
    if (strcmp(protocol, "TCP") == 0) {
        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connection failed");
            return;
        }
    }

    char buffer[1024] = {0};
    struct timeval start, end;
    long tstart, treq, tres, delta_t, total_t;
    int num_messages = duration * 1000 / interval;

    // Record the start time
    tstart = get_time_in_microseconds();

    for (int i = 0; i < num_messages; i++) {
        // Create a dynamic message
        char message[256];
        snprintf(message, sizeof(message), "Request number %d from client", i + 1);

        // Send message
        gettimeofday(&start, NULL);
        treq = get_time_in_microseconds();

        if (strcmp(protocol, "TCP") == 0) {
            send(sock, message, strlen(message), 0);
        } else {
            sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        }

        // Receive response
        if (strcmp(protocol, "TCP") == 0) {
            read(sock, buffer, sizeof(buffer));
        } else {
            recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        }

        gettimeofday(&end, NULL);
        tres = get_time_in_microseconds();
        delta_t = tres - treq;
        total_t = tres - tstart;

        // Print and save results
        printf("Total Time: %ld microseconds | Delta: %ld microseconds\n", total_t, delta_t);

        if (file) {
            fprintf(file, "Total Time: %ld microseconds | Delta: %ld microseconds\n", total_t, delta_t);
        }

        // Wait for the next interval
        usleep(interval * 1000);
    }

    if (file) {
        fclose(file);
    }

    close(sock);
}
