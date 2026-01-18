#include "stdafx.h"
#include "soccerplayer.h"
#include <string>
void Soccer::playon_holy_diver()
{

	int playstrategy = 1;
	int goalie_id = 0;
	rcsc::Vector2D ball = plt->getBall().pos;
	static int lastplaymake = 3;
	int playmake = -1;
	double pm_cost[5] = { 999999,9999999,99999999,9999999,9999999 },
		opp_cost[5] = { 999999,9999999,99999999,9999999,9999999 },
		pm_fast[5] = { 999999,9999999,99999999,9999999,9999999 };
	int idlist[5] = { 0,1,2,3,4 }, oppidlist[5] = { 0,1,2,3,4 }, idfastlist[5] = { 0,1,2,3,4 };
	if (ball_in_area2())
	{
		catch_the_rainbow();//防守
	}
	else if (ball_in_area1())
	{
		man_on_the_silver_mountain();//进攻
	}
	else if (Field::InFobidenBound(ball))//边界策略
	{
		for (int i = 0; i < 5; i++)//敌我接球的cost评价
		{
			if (i == goalie_id)	continue;
			pm_cost[i] = Takeballcost1(i, ball);
			if (i == lastplaymake)
			{
				pm_fast[i] -= 5;
				pm_cost[i] -= 5;
			}
		}
		for (int i = 0; i < 4; i++)//排序, 按cost由小到大
		{
			for (int j = 0; j < 4; j++)
			{
				if (pm_cost[j] > pm_cost[j + 1])
				{
					double costpara = pm_cost[j];
					pm_cost[j] = pm_cost[j + 1];
					pm_cost[j + 1] = costpara;
					int idlistpara = idlist[j];
					idlist[j] = idlist[j + 1];
					idlist[j + 1] = idlistpara;
				}
			}
		}
		playmake = idlist[0];
		playerstatus[playmake] = 1;
		shell_holy_diver_Bound(playmake);
		Goalie_holy_diver_care(0);
	}
	else//常规策略
	{
		for (int i = 0; i < 5; i++)//敌我接球的cost评价
		{
			if (i == goalie_id)	continue;
			pm_cost[i] = Takeballcost(i, 1);
			//logg.test2 << "cost" << i <<" :"<< pm_cost[i]<<std::endl;
			opp_cost[i] = Takeballfast(i, 0);
			pm_fast[i] = Takeballfast(i, 1);
			//logg.test2 << "cost_fast" << i <<" :"<< pm_fast[i]<<std::endl;
			if (i == lastplaymake)
			{
				pm_fast[i] -= 5;
				pm_cost[i] -= 5;
			}
		}
		for (int i = 0; i < 4; i++)//排序, 按cost由小到大
		{
			for (int j = 0; j < 4; j++)
			{
				if (pm_cost[j] > pm_cost[j + 1])
				{
					double costpara = pm_cost[j];
					pm_cost[j] = pm_cost[j + 1];
					pm_cost[j + 1] = costpara;
					int idlistpara = idlist[j];
					idlist[j] = idlist[j + 1];
					idlist[j + 1] = idlistpara;
				}
				if (pm_fast[j] > pm_fast[j + 1])
				{
					double fastcost = pm_fast[j];
					pm_fast[j] = pm_fast[j + 1];
					pm_fast[j + 1] = fastcost;
					int fastidlist = idfastlist[j];
					idfastlist[j] = idfastlist[j + 1];
					idfastlist[j + 1] = fastidlist;
				}
				if (opp_cost[j] > opp_cost[j + 1])
				{
					double oppcostpara = opp_cost[j];
					opp_cost[j] = opp_cost[j + 1];
					opp_cost[j + 1] = oppcostpara;
					int oppidlistpara = oppidlist[j];
					oppidlist[j] = oppidlist[j + 1];
					oppidlist[j + 1] = oppidlistpara;
				}

			}
		}
		//logg.test1 << "idlist[0]:" << idlist[0] << std::endl;
		//logg.test1 << "idfastlist[0]:" << idfastlist[0] << std::endl;



			playmake = idlist[0];
			lastplaymake = playmake;
			playstrategy = 3;//进攻模式

		playerstatus[playmake] = 1;

			shell_holy_diver(playmake);

		Goalie_holy_diver(0);
	}
	
}






/**决策算法实现**/
void Soccer::playon()
{
	//守门员决策
	int goalie_id = 0;
	Goalie(goalie_id);

	//场上球员决策
	int playmake = -1;
	double pm_cost = 1000000000.0;
	
	for (int i = 0; i < 5; i++)
	{
		if (i == goalie_id)	continue;
		double t_cost = plt->ourRobot(i).pos.dist(plt->getBall().pos + plt->getBall().vel + rcsc::Vector2D(-20, 0));
		if (i == last_pm) t_cost -= 10;
		if (plt->ourRobot(i).pos.x > plt->getBall().pos.x + 10) t_cost += 10000;
		if (t_cost < pm_cost) {
			pm_cost = t_cost;
			playmake = i;
		}
	}
	last_pm = playmake;

	PlayMake(playmake);
	
	int defenseNum = -1;
	if (plt->getBall().pos.x < -30) defenseNum = 2;
	else if (plt->getBall().pos.x > 30) defenseNum = 2;
	else defenseNum = 1;

	int defense[3] = { -1, -1, -1 };
	rcsc::Vector2D poses[3] = { Field::ourGoal(), Field::ourGoalB(), Field::ourGoalT() };
	for (int d = 0; d < defenseNum; d++) {
		int bestID = -1;
		int best = 100000000;
		for (int i = 0; i < 5; i++) {
			if (i == playmake || i == goalie_id) continue;
			bool same = false;
			for (int j = 0; j < 3; j++) if (defense[j] == i) same = true;
			if (same) continue;
			
			double t = plt->ourRobot(i).pos.dist(poses[d]);
			if (t < best) {
				best = t;
				bestID = i;
			}
		}
		defense[d] = bestID;
	}

	Defense(defense, defenseNum);
	int other[2] = { -1, -1 };
	for (int o = 0; o < 2; o++) {
		for (int i = 1; i < 5; i++) {
			if (i == playmake) continue;
			bool same = false;
			for (int j = 0; j < 3; j++) if (defense[j] == i) same = true;
			for (int j = 0; j < 2; j++) if (other[j] == i) same = true;
			if (same) continue;
			other[o] = i;
		}
	}
	Pos(other, 3 - defenseNum);
	//kick(playmake, Field::oppGoal());
}