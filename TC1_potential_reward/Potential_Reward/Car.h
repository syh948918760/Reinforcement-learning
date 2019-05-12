//
//  Car.hpp
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#ifndef Car_hpp
#define Car_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include<vector>
#include<list>
#include<map>
#include<ctime>
#include"Road.h"

using namespace std;

#define red     1
#define green   0

//描述Q/V/红灯次数
//<Road,destination,Red>-<Q/V/p>
//红灯概率=红/(红+绿)
inline std::map<tuple<int,int,int>,tuple<double,double,int>> QVP;

//描述转移次数
//<Road,destination,Red,Road'> -probability
//转移概率=ab/a*
inline std::map<tuple<int,int,int,int>,int> TransitionNum;

struct element{
public:
    int last_road=0;  //上次红灯的时候
    int next=-1;    //下个road
    int source=0;   //从哪条road出发
    int des=0;
    int flag=0;     //上次是否通过   1-在行驶状态
    element(int sou,int d){
        source=sou;
        last_road=sou;
        des=d;
    }
};

class Car{
public:
    int state[17][2];
    //记录当前红绿灯状态 正为绿灯秒数,负为红灯秒数  第二个是左右边
    int Path[17][9][3];
    int current_num=0;
    int car_size[17][3];
    //记录当前所有道路中前中后车辆数
    int road_map[17][3];
    //记录每个路口不同方向的下一个Road
    int final_point[17];
    //记录road前中后到的point
    
    vector<list <element> > vec_1; //存储左转list集合
    vector<list <element> > vec_2; //存储右转/直行转list集合
    //s表示每条路上的车辆list
    list<element> s1;list<element> s2;list<element> s3;list<element> s4;
    list<element> s5;list<element> s6;list<element> s7;list<element> s8;
    list<element> s9;list<element> s10;list<element> s11;list<element> s12;
    list<element> s13;list<element> s14;list<element> s15;list<element> s16;
    
   
    int COUNT=0;     //全局变量对每辆车唯一标示
    
//    p_g/p_r  在green/red下点状态转移次数
//    double p_g[17][17]; //1-16  状态转移次数
//    double Q_g_20[17][17];
//    double Q_g_40[17][17];
//    double Q_g_60[17][17];
//    double Q_r_20[17][17];
//    double Q_r_40[17][17];
//    double Q_r_60[17][17];
//
    Car();
    void Add(int n);
    
    void Sub();
    void Sub_list(int r,int max,int n,int f);    //r为指定开放道路的编号
    void Normal_Setting(int n);
    void RL_Setting(int n);
    //每条道路上的汽车总数计算
    int getCar_size();
    
};



#endif /* Car_hpp */
