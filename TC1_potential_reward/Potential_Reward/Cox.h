//
//  Cox.h
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#ifndef Cox_h
#define Cox_h
#include <iostream>
#include <string>


static int Exit[] = {0,1,2,3,5,6,7,8};

struct Cox {
public:
    int x;
    int y;
    int flag;
    
    Cox(){
        srand((unsigned)time(NULL));
        flag=Exit[rand()%10];
        x=flag/3;
        y=flag%3;
    }
    
    Cox(int no){    //构造函数，参数为flag不可能为的值，防止车辆src/des相同
        srand((unsigned)time(NULL));
        flag=Exit[rand()%10];
        while(flag==no)
        {
            srand((unsigned)time(NULL));
            flag=Exit[rand()%10];
        }
        x=flag/3;
        y=flag%3;
    }
    
    Cox(int a,int b){
        x=a;y=b;
        flag=x*3+y;
    }

    void update_flag(){
        flag=x*3+y;
    }

    bool operator!=(Cox&c2){
        if(flag==c2.flag)
            return 0;
        else return 1;
    }
    void operator=(Cox&c2){
        this->x=c2.x;
        this->y=c2.y;
        this->flag=c2.flag;
    }
};



#endif /* Cox_h */
