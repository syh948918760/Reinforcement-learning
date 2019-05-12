//
//  tl.hpp
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#ifndef tl_hpp
#define tl_hpp


#define red     1
#define green   0

#include"Road.h"
#include "vector"

class TL {
public:
    int action_left;
    int action_right;
    std::vector<Road> road_list;
    int n;
    
public:
    TL(int n){
        action_left=0;
        action_right=0;
        this->n=n;
    }
};

#include <stdio.h>

#endif /* tl_hpp */
