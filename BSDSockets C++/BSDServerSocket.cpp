//
//  BSDServerSocket.cpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#include <thread>
#include "unistd.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "BSDServerSocket.hpp"

void BSDServerSocket::main() {
    while (isRunning) {
        int acceptedSocket = accept(socketDescriptor, NULL, NULL);
        if (acceptedSocket >= 0) {
            printf("Accepted with descriptor ->%d<-\n", acceptedSocket);
            std::thread t(&BSDServerSocket::handle, this, acceptedSocket);
            t.detach();
        } else {
            perror("Cannont accept socket");
        }
    }
}


void BSDServerSocket::send(const char *data, int descriptor) {
    protectedSend(data, descriptor);
}



BSDServerSocket::BSDServerSocket(int port) : BSDServerSocket("127.0.0.1", port, NULL) { }
BSDServerSocket::BSDServerSocket(int port, IBSDSocketDelegate *delegate) : BSDServerSocket("127.0.0.1", port, delegate) { }
BSDServerSocket::BSDServerSocket(std::string address, int port, IBSDSocketDelegate *delegate) : BSDSocket(address, port, delegate) {
    bool flag = true;
    socketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketDescriptor == -1) {
        perror("Socket create failed");
        flag = false;
    }
    
    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    //sock_addr.sin_len = sizeof(sock_addr);
    sock_addr.sin_family = PF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(socketDescriptor, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1) {
        perror("Bind failed");
        flag = false;
    }
    
    if (listen(socketDescriptor, 10) == -1) {
        perror("Listen failed");
        flag = false;
    }
    
    if (!flag) {
        close(socketDescriptor);
        isRunning = false;
    } else {
        printf("ServerSocket successfully created\n");
    }
}
