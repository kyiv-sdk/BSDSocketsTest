//
//  BSDClientSocket.cpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#include "unistd.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "BSDClientSocket.hpp"

void BSDClientSocket::main() {
    while (isRunning) {
        handle(socketDescriptor);
    }
}


void BSDClientSocket::sendData(const char *data) {
    protectedSend(data, socketDescriptor);
}


void BSDClientSocket::closeSocket() {
    shutdown(socketDescriptor, SHUT_RDWR);
    BSDSocket::closeSocket();
}


BSDClientSocket::BSDClientSocket(int port) : BSDClientSocket("127.0.0.1", port, NULL) { }
BSDClientSocket::BSDClientSocket(int port, IBSDSocketDelegate *delegate) : BSDClientSocket("127.0.0.1", port, delegate) { }
BSDClientSocket::BSDClientSocket(std::string address, int port, IBSDSocketDelegate *delegate) : BSDSocket(address, port, delegate) {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketDescriptor == -1) {
        perror("Cannot create ClientSocket");
        isRunning = false;
    }
    
    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_len = sizeof(sock_addr);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    isRunning = (bool)inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr);
    
    if (connect(socketDescriptor, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
        perror("Cannot connect to ClientSocket");
        close(socketDescriptor);
        isRunning = false;
    } else {
        printf("ClientSocket successfully connected\n");
    }
}
