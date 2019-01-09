//
//  BSDSocketDelegate.hpp
//  BSDSocketsC++
//
//  Created by Oleksandr Hordiienko on 1/4/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#ifndef BSDSocketDelegate_hpp
#define BSDSocketDelegate_hpp

#include <string>
#include <stdio.h>

class IBSDSocketDelegate {
    
public:
    virtual void didReceiveMessage(std::string message);
    
};

#endif /* BSDSocketDelegate_hpp */
