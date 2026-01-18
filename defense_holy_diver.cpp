#include "stdafx.h"
#include "soccerplayer.h"
void Soccer::defense_holy_diver()
{
	rcsc::Vector2D ball=plt->getBall().pos,ballvel=plt->getBall().vel;
	double dist=1000;
	int deffense[4];//0 主要 ，2、3协防，4 保守
	int opp[4],oppcost[5];
	double oppx = 0;
	for (int i = 0; i <= 4; i++)
	{
		opp[i] = i;
		oppcost[i] = Takeballfast(i, 0);
		if (plt->oppRobot(i).pos.getX() > oppx)//离球门最近
		{
			oppx = plt->oppRobot(i).pos.getX();
		}
		
	}
	double cost ;
	
	int numb;
	for (int j = 0; j <= 3; j++)//对方球员排序
	{
		if (oppcost[j] > oppcost[j + 1])
		{
			numb = opp[j];
			opp[j] = opp[j + 1];
			opp[j + 1] = numb;
			cost = oppcost[j];
			oppcost[j] = oppcost[j + 1];
			oppcost[j + 1] = cost;
		}
		
	}
	for (int i = 1; i <= 4; i++)
	{
		if (dist > Takeballfast(i, 1))//找到主要
		{
			deffense[0] = i;
			dist = Takeballfast(i, 1);
		}
	}
	dist = 1000;
	for (int i = 1; i <= 4; i++)//找到协防2
	{
		if (i == deffense[0])continue;
		if ( plt->ourRobot(i).pos.dist(plt->oppRobot(opp[1]).pos) < dist)
		{
			deffense[1] = i;
			dist = plt->ourRobot(i).pos.dist(plt->oppRobot(opp[1]).pos);
		}
		
	}
	dist = 1000;
	for (int i = 1; i <= 4; i++)//找到协防3
	{
		if (i == deffense[0]||i==deffense[1])continue;
		if (plt->ourRobot(i).pos.dist(plt->oppRobot(opp[1]).pos) < dist)
		{
			deffense[2] = i;
			dist = plt->ourRobot(i).pos.dist(plt->oppRobot(opp[2]).pos);
		}
		
	}
	for (int i = 1; i <= 4; i++)//找到保守4
	{
		if (i == deffense[0] || i == deffense[1] || deffense[2] == i)continue;
		else deffense[3] = i;

	}
	rcsc::Vector2D deffensepos1, deffensepos2;
	deffensepos1 = ball- plt->oppRobot(opp[1]).pos-plt->oppRobot(opp[1]).vel*3;
	deffensepos1.setLength(13);
	deffensepos2 = ball - plt->oppRobot(opp[2]).pos - plt->oppRobot(opp[2]).vel * 3;
	deffensepos2.setLength(13);
	
	rcsc::Vector2D deffensepos3(oppx, (deffensepos1 + deffensepos2 + ball).getY());
	
	heading_position(deffense[0], ball, 4.88);
	heading_position(deffense[1], deffensepos1, 4.88);
	logg.test2 << "step7" << std::endl;
	heading_position(deffense[2], deffensepos2, 4.88);
	heading_position(deffense[3], deffensepos3, 4.88);
}

