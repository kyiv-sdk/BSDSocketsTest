//
//  BSDSocket.cpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include "BSDSocket.hpp"


int getLength(std::string data) {
    std::string clearDataLength;
    for (int i = 0; i<data.length(); i++) {
        if (data[i] >= '0' && data[i] <= '9') {
            clearDataLength += data[i];
        }
    }
    return std::stoi(clearDataLength);
}



void BSDSocket::start() {
    std::thread t(&BSDSocket::main, this);
    t.detach();
}

void BSDSocket::main() {
    // TODO: Override in inherited classes
}


void BSDSocket::closeSocket() {
    isRunning = false;
    close(socketDescriptor);
}


void BSDSocket::handle(int socketDescriptor) {
    while (isRunning) {
        char buf[1];
        int bytes = (int)read(socketDescriptor, &buf, 1);
        
        // Received Message
        if (bytes > 0) {
            if ((int)*buf==2) {
                char *receivedData = readData(socketDescriptor);
                std::string receivedMessage(receivedData);
                receivedInfo.push_back(receivedMessage);
                printf("Received message ->%s<-\n", receivedMessage.c_str());
                if (delegate) delegate->didReceiveMessage(receivedMessage);
            }
        }
        
        // Disconnected
        else if (bytes == 0) {
            if (close(socketDescriptor) == -1) {
                perror("Close failed");
            }
            break;
        }
    }
    
    
    shutdown(socketDescriptor, SHUT_RDWR);
    close(socketDescriptor);
}


void BSDSocket::protectedSend(const char *data, int socket) {
    int initialize[1]={2};
    int separator[1]={4};
    int data_length=(int)strlen(data);
    int target_length=snprintf(NULL, 0, "%d", data_length);
    char *data_length_char = (char *)malloc(target_length+1);
    snprintf(data_length_char, target_length+1, "%d", data_length);
    
    int ele_count=(int)strlen(data_length_char);
    int *size_buff=(int*)malloc(ele_count*sizeof(int));
    for (int counter=0; counter<ele_count; counter++) {
        size_buff[counter]=(int)data_length_char[counter];
    }
    
    int packet_length= 1+1+ele_count+(int)strlen(data);
    uint8_t *packet=(uint8_t *)malloc(packet_length * sizeof(uint8_t));
    
    memcpy(&packet[0], initialize, 1);
    for (int counter=0; counter<ele_count; counter++) {
        memcpy(&packet[counter+1], &size_buff[counter], 1);
    }
    
    memcpy(&packet[0+1+ele_count], separator, 1);
    memcpy(&packet[0+1+ele_count+1], data, strlen(data));
    if (write(socketDescriptor, packet, packet_length) == -1) {
        perror("Write error");
    }
    free(packet);
    free(size_buff);
    free(data_length_char);
}


char *BSDSocket::readData(int descriptor) {
    char *data_buff;
    
    //NSMutableString *buff_length=[[NSMutableString alloc]init];
    std::string buff_length;
    char buf[1];
    read(descriptor, &buf, 1);
    while ((int)*buf!=4) {
        buff_length.append(1, (char)(int)*buf);
        read(descriptor, &buf, 1);
    }
    
    int data_length = getLength(buff_length);
    data_buff=(char *)malloc(data_length*sizeof(char));
    ssize_t byte_read=0;
    ssize_t byte_offset=0;
    while (byte_offset<data_length) {
        byte_read=read(descriptor, data_buff+byte_offset, 50);
        byte_offset+=byte_read;
    }
    
    return data_buff;
}


BSDSocket::BSDSocket(int port) : BSDSocket("127.0.0.1", port, NULL) { }
BSDSocket::BSDSocket(int port, IBSDSocketDelegate *delegate) : BSDSocket("127.0.0.1", port, delegate) { }
BSDSocket::BSDSocket(std::string address, int port, IBSDSocketDelegate *delegate) {
    isRunning = true;
    this->address = address;
    this->port = port;
    this->delegate = delegate;
}



