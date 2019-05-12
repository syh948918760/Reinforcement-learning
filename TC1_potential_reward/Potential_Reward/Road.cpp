//
//  Road.cpp
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#include <stdio.h>
#include "Road.h"

Road::Road(Cox a,Cox b){
        head=a;
        tail=b;
}


Road::Road(){
    Cox c1;
    head=c1;
    Cox c2(c1.flag);   
    tail=c2;
}

Road::Road(int a,int b){
    Cox c1;
    c1.flag=a;
    c1.x=c1.flag/5;
    c1.y=c1.flag%5;
    head=c1;
    Cox c2;
    c2.flag=b;
    c2.x=c2.flag/5;
    c2.y=c2.flag%5;
    tail=c2;
}

Road::Road(int a,int b,int n){
    Cox c1;
    c1.flag=a;
    c1.x=c1.flag/3;
    c1.y=c1.flag%3;
    head=c1;
    Cox c2;
    c2.flag=b;
    c2.x=c2.flag/3;
    c2.y=c2.flag%3;
    tail=c2;
    this->n=n;
}

void Road::operator=(Road &r){
    head=r.head;
    tail=r.tail;
    current_size=r.current_size;
    n=r.n;
}
