//
//  Road.h
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#ifndef Road_h
#define Road_h
#include"Cox.h"

class Road {
public:
    Cox head;
    Cox tail;
    int current_size=0;
    int left_size=0;
    int stright_size=0;
    int right_size=0;
    int n;
    
public:
    Road(Cox a,Cox b);          //根据结点构造Road
    Road();
    void operator=(Road &r);
    Road(int a,int b);
    Road(int a,int b,int n);    
};


#endif /* Road_h */
