package treasure_on_right;

import java.awt.print.Printable;
import java.util.Random;

/**
* @author Yanhao Shen
* @version 创建时间：2018年9月11日 下午12:24:10
* 类说明
*/
public class demo {
	
	int N_STATES=6;
	String ACTIONS[]= {"l","r"};
	double Epsilon=0.6;			//折扣因子
	double Gamma=0.9;			//探索随机率
	int Max_Episodes=10;		//最大周期
	double Fresh_time=0.1;		//刷新时间
	double ALPHA=0.6;			//学习率
	Random r = new Random(2);
	Boolean Is_intermain=false;
	
	
	double[][] q_table=new double[6][2];
	
	
	void show(double[][] a,int row,int col)
	{
		for(Integer i=0;i<row;i++) {
			System.out.print("s:"+i+'\t');
			for(int j=0;j<col;j++)
				System.out.print(a[i][j]+"   ");
			System.out.println();
		}
	}
	
	
	double[][] buile_q_table(int n_state,int action) {
		
		q_table=new double[n_state][action];
		System.out.println("BUILE Q_TABLE!");
		//show(q_table, n_state,action);
		return q_table;
	}
	

	double Get_max(double[] a) {
		double max=-1000;
		for(int i=0;i<a.length;i++)
		{
			max=(max>a[i])?max:a[i];
		}
	
		return max;
	}
	
	int choose_action(int state,double[][]q_table) {
		double[] actions=new double[2];
		actions[0]=q_table[state][0];
		actions[1]=q_table[state][1];
		int action=0;		//0--l, 1---r
		if(actions[0]==0&&actions[1]==0)
		{
			action=r.nextInt(2);	//如果一样 随机选择
		}
		else {
			action=(actions[0]>actions[1])?0:1;	//取大的

		}
		
		return action;
	}
	
	int[] get_env_feedback(int state,int action)
	{
		int next[]=new int[2];
		int s_,reward;
		if(action==1) {
			if (state==N_STATES-2)
			{
				s_=5;	//到达T
				Is_intermain=true;
				reward=1;
			}
			else {
				s_=state+1;
				reward=0;
			}	
		}
		else {
			if (state==0)
			{
				s_=0;	
				reward=0;
			}
			else {
				s_=state-1;
				reward=0;
			}	
		}
		
		next[0]=s_;
		next[1]=reward;
		return next;
	}
	
	void Update_env(int state,int episode,int step_counter)
	{
		String env= "-----T";	//共5+1
		if (Is_intermain==true)
		{
			StringBuilder sb=new StringBuilder(env);
			sb.setCharAt(state, '0');
			env=sb.toString();
			
			try {
			       Thread.sleep (20) ; 
			 } catch (InterruptedException ie){
			 }
			
			System.out.println(episode+" END!   "+"step:"+step_counter);
		}
		
		else {
			StringBuilder sb=new StringBuilder(env);
			sb.setCharAt(state, '0');
			env=sb.toString();	
		}	
		System.out.println(env);
	}

	double[][] rl(){
		
		//q_table=buile_q_table(N_STATES,2);	//新建Q_table
		for(int episode=0;episode<Max_Episodes;episode++)
		{
			int step_counter=0;
			int s=0;		//当前状态
			int s_=0;		//下一步状态
			int action;		//选择动作
			int	reward=0;	//reward
			double q_prediction=0;
			double q_target;
			Is_intermain=false;
			
			Update_env(s, episode, step_counter);
			while(!Is_intermain) {
				action=choose_action(s,q_table);
				s_=get_env_feedback(s, action)[0];
				reward=get_env_feedback(s, action)[1];
				q_prediction=q_table[s][action];
				
				if(s_!=5) {
					q_target=(reward+Gamma*Get_max(q_table[s_]));			
				}
				
				else
				{
					q_target=reward;
					Is_intermain=true;
					//show(q_table, 6, 2);
				}
				
				//q_table[s][action]+=ALPHA*(q_target-q_prediction);
				q_table[s][action]=q_target;
				
				s=s_;
				Update_env(s, episode, step_counter+1);
				step_counter+=1;
			}	
		}
		
		return q_table;
	}
	
	public static void main(String[] args) {
		
		demo d=new demo();
		double[][]a=d.rl();
	
	}

}


