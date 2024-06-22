#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "defs.h"
#include "echoserver.h"

void echo(int socket_handle) {
    char buff[MAX];
    socklen_t len;
    ssize_t comm_len;
    SockAddrIn client_address;

    len = sizeof(client_address);

    while(true) {
        // Clear buffer
        memset (&buff , 0, sizeof(buff));
        memset (&client_address , 0, sizeof(client_address));

        // Read message from client and copy it to the buffer
        comm_len = recvfrom(socket_handle , (char *) &buff , sizeof(buff), 0, (SockAddr *) &client_address , &len);
        if (comm_len < 0) {
            fprintf(stderr , "Error in receiving message: %s\n", strerror(errno));
        } else {
            fprintf(stdout , "Received message: %s\n", buff);
            sendto(socket_handle , (char *) &buff , sizeof(buff), 0, (SockAddr *) &client_address , len);
        }
    }
}
