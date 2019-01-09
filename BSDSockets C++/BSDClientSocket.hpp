//
//  BSDClientSocket.hpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#ifndef BSDClientSocket_hpp
#define BSDClientSocket_hpp

#include <stdio.h>
#include "BSDSocket.hpp"

class BSDClientSocket : public BSDSocket {
public:
    void main() override;
    void sendData(const char *data);
    void closeSocket() override;
    
    BSDClientSocket(int port);
    BSDClientSocket(int port, IBSDSocketDelegate *delegate);
    BSDClientSocket(std::string address, int port, IBSDSocketDelegate *delegate);
};

#endif /* BSDClientSocket_hpp */
