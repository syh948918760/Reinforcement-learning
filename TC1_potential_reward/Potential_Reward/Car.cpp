//
//  Car.cpp
//  Traffiic_TC1
//
//  Created by 沈彦昊 on 2018/11/19.
//  Copyright © 2018年 沈彦昊. All rights reserved.
//

#include "Car.h"
using namespace std;

Car::Car(){
    
    memset(state,0, sizeof(state));        //初始化全部红灯  state 0:红灯
    memset(road_map, 0, sizeof(road_map));
    memset(final_point, 0, sizeof(final_point));
    
    for(int i=0;i<17;i++)
        for(int j=0;j<3;j++)
            car_size[i][j]=0;
    
//    for(int i=1;i<17;i++)
//        for(int j=0;j<2;j++)
//            state[i][j]=1;//state 全部打开
//
    //final_point是每条边对应的终点
    final_point[1]=0;final_point[2]=2;final_point[3]=0;final_point[4]=1;
    final_point[5]=2;final_point[6]=6;final_point[7]=5;final_point[8]=6;
    final_point[9]=7;final_point[10]=8;final_point[11]=6;final_point[12]=8;
    final_point[13]=4;final_point[14]=4;final_point[15]=4;final_point[16]=4;
    
    //road_map是road 关系图 0/1/2   left/straight/right
    road_map[4][0]=1;road_map[4][2]=2;
    road_map[6][0]=8;road_map[6][2]=3;
    road_map[7][0]=5;road_map[7][2]=10;
    road_map[9][0]=12;road_map[12][2]=11;
    road_map[13][0]=7;road_map[13][1]=9;road_map[13][2]=6;
    road_map[14][0]=4;road_map[14][1]=7;road_map[14][2]=9;
    road_map[15][0]=6;road_map[15][1]=4;road_map[15][2]=7;
    road_map[16][0]=9;road_map[16][1]=6;road_map[16][2]=4;
    
    //s表示每条路上的车辆list<element>
    //左转list集合
    //代替0
    vec_1.push_back(s1);
    vec_1.push_back(s1);vec_1.push_back(s2);vec_1.push_back(s3);
    vec_1.push_back(s4);vec_1.push_back(s5);vec_1.push_back(s6);
    vec_1.push_back(s7);vec_1.push_back(s8);vec_1.push_back(s9);
    vec_1.push_back(s10);vec_1.push_back(s11);vec_1.push_back(s12);
    vec_1.push_back(s13);vec_1.push_back(s14);vec_1.push_back(s15);
    vec_1.push_back(s16);
    
    //直行/右转转list集合
    //代替0位
    vec_2.push_back(s1);//填空0位 使得每条road下标与标志匹配
    vec_2.push_back(s1);vec_2.push_back(s2);vec_2.push_back(s3);
    vec_2.push_back(s4);vec_2.push_back(s5);vec_2.push_back(s6);
    vec_2.push_back(s7);vec_2.push_back(s8);vec_2.push_back(s9);
    vec_2.push_back(s10);vec_2.push_back(s11);vec_2.push_back(s12);
    vec_2.push_back(s13);vec_2.push_back(s14);vec_2.push_back(s15);
    vec_2.push_back(s16);
    
    
    for(int i=0;i<17;i++)
        for(int j=0;j<9;j++)
            for(int k=0;k<3;k++)
                Path[i][j][k]=0;
    
    //当前road走到Des_point向左/前右是否可行
    //road->des_point  [left/stright/rigzxht]=1/0
    Path[4][0][0]=1;Path[4][2][2]=1;
    Path[13][3][2]=1;Path[13][5][0]=1;Path[13][7][1]=1;
    Path[13][6][2]=1;Path[13][6][1]=1;
    Path[13][8][0]=1;Path[13][8][1]=1;
    
    Path[6][6][0]=1;Path[6][0][2]=1;
    Path[14][7][2]=1;Path[14][1][0]=1;Path[14][5][1]=1;
    Path[14][8][2]=1;Path[14][8][1]=1;
    Path[14][2][0]=1;Path[14][2][1]=1;
    
    Path[7][2][0]=1;Path[7][8][2]=1;
    Path[16][1][2]=1;Path[16][7][0]=1;Path[16][3][1]=1;
    Path[16][0][2]=1;Path[16][0][1]=1;
    Path[16][6][0]=1;Path[16][6][1]=1;
    
    Path[9][8][0]=1;Path[9][6][2]=1;
    Path[15][5][2]=1;Path[15][3][0]=1;Path[15][1][1]=1;
    Path[15][2][2]=1;Path[15][2][1]=1;
    Path[15][0][0]=1;Path[15][0][1]=1;
}

//num为新增车的数目
void Car::Add(int n=4){
    int road_start[]={13,14,15,16};
    int temp=0;
    int temp_start;         //为Road编号
    int temp_back;          //为出口点
    while(n){
        n--;
        temp=rand()%8;
        temp_back=Exit[temp];
        temp=rand()%4;
        temp_start=road_start[temp];
        //可能进行反向
        switch (temp_start) {
            case 15:
                if(temp_back==6||temp_back==7||temp_back==8)
                    temp_start=9;
                break;
            case 14:
                if(temp_back==0||temp_back==3||temp_back==6)
                    temp_start=6;
                break;
            case 13:
                if(temp_back==0||temp_back==1||temp_back==2)
                    temp_start=4;
                break;
            case 16:
                if(temp_back==2||temp_back==5||temp_back==8)
                    temp_start=7;
                break;
            default:
                break;
        }
        
        //出发路已经通往des,重新生成
        if(final_point[temp_start]==temp_back)
        {
            n++;
            continue;
        }
        COUNT++;
        cout<<"新增第"<<COUNT<<"车辆完成."<<temp_start<<"->"<<temp_back<<endl;
        
        int sum=0;
        int road[2]={-1,-1};    //存放0/1/2/ 转向记录
        for(int i=0;i<3;i++)
        {
            //car_size[temp_start][i]+=Path[temp_start][temp_back][i];
            if(Path[temp_start][temp_back][i]!=0)
                road[sum]=i;
            sum+=Path[temp_start][temp_back][i];   //0/1是否可行
        }
        if(sum>1)
        {   //说明有双向选择
            int num_1=0;
            int num_2=0;
            int num_3=0;
            //计算下一步车道的数目 num_1 num_2
            for(int i=0;i<3;i++)
            {
                num_1+=car_size[road_map[temp_start][0]][i];
                num_2+=car_size[road_map[temp_start][1]][i];
                num_3+=car_size[road_map[temp_start][2]][i];
            }
            if(road[0]==0){//说明左  选择左行
                element e(temp_start,temp_back);
                vec_1[temp_start].push_back(e);
                car_size[temp_start][0]++;//左侧
            }
            else{//加入右车道
                element e(temp_start,temp_back);
                vec_2[temp_start].push_back(e);
                if(num_2<num_3)//选择直行车道
                    car_size[temp_start][1]++;//前侧
                else
                    car_size[temp_start][2]++;//右侧
            }
        }
        else   //只有单一方向可行
        {
            if(road[0]==0)//说明左
            {
                element e(temp_start,temp_back);
                vec_1[temp_start].push_back(e);
                car_size[temp_start][0]++;
            }
            else
            {
                element e(temp_start,temp_back);
                vec_2[temp_start].push_back(e);
                car_size[temp_start][road[0]]++;        //只有单方向,road[0]即为1/2
            }
        }
    }
}


void Car::Sub(){
    //state为 红绿灯状态
    //r 为指定道路的编号
    for(int i=1;i<17;i++)
    {
        for(int j=0;j<2;j++)
        //探测所有state为绿色开放的路口 i为当前道路编号
        {
            //进行vec_1预处理  将已经结束的删除,将flag=1的可能结束
            list<element>::iterator it;
            int debug_num=0;
            for(it=vec_1[i].begin();it!=vec_1[i].end();)
            {
                //如果到达终点,退出list
                if((*it).des==final_point[i]){
                    cout<<it->source<<"->"<<final_point[i]<<"OUT!"<<endl;
                    vec_1[i].erase(it);
                }
                //存在flag=1 且下一条路为
                else if((*it).flag==1)
                {   
                    int next_flag=-1;       //下一步走的方向 0/1/2
                    for(int i=0;i<3;i++)
                    {
                        if(Path[(*it).next][(*it).des][i]==1)
                        {
                            next_flag=i;
                            break;
                        }
                    }
                    if(next_flag==-1)   //没有一个可以走到des
                    {
                        it++;
                        debug_num++;
                        continue;
                    }
                    
                    else{
                        if(next_flag==2)
                            next_flag=1;    //讲右转和前行归为1一条路
                        if(state[(*it).next][next_flag]<=0)
                            //如果下个路口为红灯 停止flag状态    只走一次
                        {
                            (*it).flag=0;
                            //在当前状态绿灯状态转移
                            tuple<int,int,int,int>temp(it->last_road,it->des,green,i);
                            if(TransitionNum.count(temp)==0){
                                TransitionNum[temp]=0;     //新增item
                            }
                           TransitionNum[tuple<int,int,int,int>(it->last_road,it->des,green,i)]++;
                        }
                        else{//如果下个路口仍为绿灯 则将lasr_road-i的次数减少,增加last_road-next
                            tuple<int,int,int,int>temp(it->last_road,it->des,green,it->next);
                            if(TransitionNum.count(temp)==0){
                                TransitionNum[temp]=0;     //新增item
                            }
                            //当前点到最新点转移次数++
                            TransitionNum[tuple<int,int,int,int>(it->last_road,it->des,green,it->next)]++;
                        }
                        it++;
                        debug_num++;
                    }
                    
                }
                else
                {
                    it++;
                    debug_num++;
                }
                
            }
            debug_num=0;
            for(it=vec_2[i].begin();it!=vec_2[i].end();)
            {
                //如果到达终点,退出list
                if((*it).des==final_point[i]){
                    cout<<it->source<<"->"<<final_point[i]<<"  OUT!"<<endl;
                    it=vec_2[i].erase(it);
                }
                
                //存在flag=1 且下一条路为
                else if((*it).flag==1)
                {
                    int next_flag=-1;
                    for(int i=0;i<3;i++)
                    {
                        //cout<<(*it).next<<" "<<(*it).des<<" "<<i<<endl;
                        if(Path[(*it).next][(*it).des][i]==1)
                        {
                            next_flag=i;
                            break;
                        }
                    }
                    if(next_flag==-1)
                    {
                        it++; 
                        debug_num++;
                        continue;
                    }
                    else{
                        if(state[(*it).next][next_flag]<=0)
                            //如果下个路口为红灯 停止flag状态    只走一次
                        {
                            (*it).flag=0;
                            //在当前状态绿灯状态转移
                            cout<<it->last_road<<"->"<<i<<endl;
                            tuple<int,int,int,int>temp(it->last_road,it->des,green,i);
                            if(TransitionNum.count(temp)==0){
                                TransitionNum[temp]=0;     //新增item
                            }
                            TransitionNum[tuple<int,int,int,int>(it->last_road,it->des,green,i)]++;
                        }
                        else{//如果下个路口仍为绿灯 则将lasr_road-i的次数减少,增加last_road-next
                            cout<<it->last_road<<"->"<<it->next<<endl;
                            tuple<int,int,int,int>temp(it->last_road,it->des,green,it->next);
                            if(TransitionNum.count(temp)==0){
                                TransitionNum[temp]=0;     //新增item
                            }
                            //当前点到最新点转移次数++
                            TransitionNum[tuple<int,int,int,int>(it->last_road,it->des,green,it->next)]++;
                        }
                        it++;
                        debug_num++;
                    }
                }
                else{
                    it++;
                    debug_num++;
                }
            }
            

            //如果存在vec_2中list的element的flag=1   直行
            //则置=0;
            //且将p_r[element.last_road][i]++
            //last_road=i;
            
            if(state[i][j]>0&&j==0)     //左开放 i为1-16
            {
                int current=car_size[i][0];
                int sub=0;      //减少的汽车数=汽车行驶速度=1/路上汽车总数
                if(current==0)
                    continue;
                sub=3/current;
                if(sub==0)
                    sub=1;       //至少走1辆
                if(sub>current)
                    sub=current;   //最多走current
                car_size[i][0]-=sub;
                
                Sub_list(i,current,sub,0);
                //随机从i左转挑选sub辆车从排队车辆中离开
                
                //考虑如何在一秒内多次进入的
            
            }
            if(state[i][j]>0&&j==1)     //右\直走开放
            {
                int current_straight=car_size[i][1];
                int current_right=car_size[i][2];
                int sub_straight=0;
                int sub_right=0;
                if(current_straight!=0)
                    sub_straight=3*current_straight/(current_straight+current_right);
                if(current_right!=0)
                    sub_right=3*current_right/(current_straight+current_right);
                if(sub_straight==0)
                    sub_straight=1;
                if(sub_right==0)
                    sub_right=1;
                if(sub_straight>current_straight)
                    sub_straight=current_straight;
                if(sub_right>current_right)
                    sub_right=current_right;
                //求完straigh和right的减少的车辆数
                car_size[i][1]-=sub_straight;
                car_size[i][2]-=sub_right;
                
                Sub_list(i,current_straight,sub_straight,1);
                Sub_list(i,current_right,sub_right,2);
                
            }
        }
    }
}

void Car::Sub_list(int r,int max,int num,int flag)
    //在Road r上共有max辆车,在flag方向减少num辆车
    //flag=0 左转删除 flag=1 直行删除  flag=2 右行删除
{
        while (num)
    {
        int state_new=0;
        int state_old=0;
        if(flag==0){
            state_new=road_map[vec_1[r].back().last_road][0];   //下一个路口
            state_old=vec_1[r].back().last_road;                //上一个road
            if(Path[state_old][vec_1[r].back().des][0]==1)//存在左转
                //加入到左转车道
            {
                element e(state_old,vec_1[r].back().des);
                e.next=state_new;
                e.flag=1;
                vec_1[state_new].push_back(e);
                tuple<int,int,int,int>temp(e.last_road,e.des,green,state_new);
                if(TransitionNum.count(temp)==0){
                    TransitionNum[temp]=0;     //新增item
                }
                TransitionNum[temp]++;
            }//加入到右转/直行车道
            else{
                element e(state_old,vec_1[r].back().des);
                e.next=state_new;
                e.flag=1;//行驶状态
                vec_2[state_new].push_back(e);
                tuple<int,int,int,int>temp(e.last_road,e.des,green,state_new);
                if(TransitionNum.count(temp)==0){
                    TransitionNum[temp]=0;     //新增item
                }
                TransitionNum[temp]++;
            }
//            ??
//            if(state_new==0||state_old==0)
//            {
//                num--;
//                continue;
//            }
            cout<<state_old<<"->"<<state_new<<endl;
           // cout<<vec_1[r].size()<<endl;
            vec_1[r].pop_back();
            num--;
        
        }
        else{   //flag=1/2
            state_new=road_map[vec_2[r].back().last_road][flag];   //下一个状态
            state_old=vec_2[r].back().last_road;
            if(!vec_2[r].empty()&&Path[state_old][vec_2[r].back().des][0]==1)
                //存在左转
                //加入到左转车道
            {
                element e(state_old,vec_2[r].back().des);
                e.next=state_new;
                e.flag=1;
                vec_1[state_new].push_back(e);
                tuple<int,int,int,int>temp(e.last_road,e.des,green,state_new);
                if(TransitionNum.count(temp)==0){
                    TransitionNum[temp]=0;     //新增item
                }
                TransitionNum[temp]++;
            }
            else{
                element e(state_old,vec_2[r].back().des);
                e.next=state_new;
                e.flag=1;
                vec_2[state_new].push_back(e);
                tuple<int,int,int,int>temp(e.last_road,e.des,green,state_new);
                if(TransitionNum.count(temp)==0){
                    TransitionNum[temp]=0;     //新增item
                }
                TransitionNum[temp]++;
            }
            

//            if(state_new==0||state_old==0)
//            {
//                num--;
//                continue;
//            }
            cout<<state_old<<"->"<<state_new<<endl;
            //cout<<vec_2[r].size()<<endl;
            vec_2[r].pop_back();
            num--;
        }
        
    }       //在r中随意删除num辆车
}



void Car::Normal_Setting(int n){
    //int state[17][2];
    //记录当前红绿灯状态 正为绿灯秒数,负为红灯秒数  第二个是左右边
    //4 6 7 9
    int tl[]={4,6,7,9};
    //如果n 偶数为作左走
    if(n%2==0){
        for(int i=1;i<17;i++)
        {
            state[i][0]=1;      //左行
            state[i][1]=0;
        }
    }
    else{
        for(int i=1;i<17;i++)
        {
            state[i][0]=0;
            state[i][1]=1;
        }
    }
    cout<<"\n当前state "<<state[1][0]<<endl;
}


void Car::RL_Setting(int n){
    //根据当前P/Q/V表计算最优开关方式
}

int Car::getCar_size(){
    int sum=0;
    for(int i=1;i<17;i++)
    {
        for(int j=0;j<3;j++)
            sum+=car_size[i][j];
    }
    return sum;
}
