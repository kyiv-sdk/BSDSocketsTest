//
//  BSDServerSocket.hpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#ifndef BSDServerSocket_hpp
#define BSDServerSocket_hpp

#include <stdio.h>
#include "BSDSocket.hpp"

class BSDServerSocket : public BSDSocket {
    
public:
    void main() override;
    void send(const char *data, int descriptor);
    
    BSDServerSocket(int port);
    BSDServerSocket(int port, IBSDSocketDelegate *delegate);
    BSDServerSocket(std::string address, int port, IBSDSocketDelegate *delegate);
    
};

#endif /* BSDServerSocket_hpp */
