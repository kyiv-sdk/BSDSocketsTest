//
//  BSDSocket.hpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#ifndef BSDSocket_hpp
#define BSDSocket_hpp

#include <vector>
#include <stdio.h>
#include "IBSDSocketDelegate.hpp"

class BSDSocket {
public:
    int port;
    bool isRunning;
    std::string address;
    std::vector<std::string> receivedInfo;
    int socketDescriptor;
    IBSDSocketDelegate *delegate;
    
    void start();
    virtual void closeSocket();
    
    BSDSocket(int port);
    BSDSocket(int port, IBSDSocketDelegate *delegate);
    BSDSocket(std::string address, int port, IBSDSocketDelegate *delegate);

protected:
    virtual void main();
    void handle(int socketDescriptor);
    void protectedSend(const char *data, int socket);
    
private:
    char *readData(int descriptor);
};


#endif /* BSDSocket_hpp */
