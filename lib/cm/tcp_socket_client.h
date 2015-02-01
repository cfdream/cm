#ifndef TCP_SOCKET_CLIENT_H
#define TCP_SOCKET_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "global_data.h"
#include "debug_output.h"

int sockfd;

void init_socket_client(void);
void write_data_to_server(void* buffer, int len);
void close_socket(void);

void init_socket_client(void)
{
    struct sockaddr_in serv_addr;

    //initialize the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        ERROR("ERROR opening socket");
        exit(0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0)
    {
        ERROR("inet_pton error occured");
        exit(0);
    }

    //connect the server socket
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        ERROR("ERROR connecting");
        exit(0);
    }
}

void write_data_to_server(void* buffer, int len) {
    //send buffer to sockfd
    int n = write(sockfd, buffer, len);
    if (n < 0) {
        ERROR("ERROR writing to socket");
        exit(0);
    }
}

void close_socket(void) {
    //close the socket
    close(sockfd);
}

#endif
