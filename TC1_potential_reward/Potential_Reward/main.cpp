//
//  main.cpp
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#include <iostream>
#include <string>
#include"Road.h"
#include "Cox.h"
#include "TL.h"
#include "Car.h"
#include<set>
#include<vector>
using namespace std;

#define red     1
#define green   0

int main(int argc, const char * argv[]) {

    void init();//初始化出所有Road/TL
    void add_car(int n);
    
    init();
    srand(time(0));
  
    Car c;
    int minute=0;
    while(minute<1000)
    {
        cout<<"\nNo."<<minute<<endl;
        c.Add(20);
        c.Normal_Setting(minute);
        c.Sub();
        minute++;
        
        //
    }
    while(c.getCar_size())
    {
        c.Normal_Setting(minute);
        c.Sub();
        minute++;
    }
    cout<<c.COUNT<<"辆车。 "<<minute<<"mins"<<endl;
    
    cout<<"每个路口节点的等待车辆数"<<endl;
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<3;j++)
            cout<<c.car_size[i][j];
        cout<<endl;
    }
    
    system("pause");
    return 0;
}

void init(){
    Road r1(1,0,1);Road r2(0,2,2);
    Road r3(3,0,3);Road r4(4,1,4);Road r5(5,2,5);
    Road r6(4,3,6);Road r7(4,5,7);
    
    Road r8(3,6,8);Road r9(4,7,9);Road r10(5,8,10);
    Road r11(7,6,11);Road r12(7,8,12);
    
    Road r13(1,4,13);Road r14(3,4,14);
    Road r15(7,4,15);Road r16(5,4,16);
    
    TL t1(1);
    t1.road_list.push_back(r4);
    TL t2(2);
    t2.road_list.push_back(r6);
    TL t3(3);
    t3.road_list.push_back(r7);
    TL t4(4);
    t4.road_list.push_back(r9);
    TL t5(5);
    t5.road_list.push_back(r13);
    t5.road_list.push_back(r14);
    t5.road_list.push_back(r15);
    t5.road_list.push_back(r16);
    cout<<"初始化完毕!"<<endl;
}

