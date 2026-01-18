#include "stdafx.h"
#include "soccerplayer.h"
double Soccer::Takeballcost1(int id,rcsc::Vector2D ball)//边界评价函数
{
	rcsc::Vector2D pos, vel, ballvel, goal;
	double cost = 0;
	ballvel = plt->getBall().vel;
	if (ball.getX()>210&&ball.getY()<65)//右下
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal=rcsc::Vector2D(215.5,8);
	}
	else if (ball.getX() > 210 && ball.getY() > 115)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(215.5, 172);
	}
	else if (ball.getX() < 10 && ball.getY() < 65)//看情况可以骚一手
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(30, 90);
	}
	else if (ball.getX() <10 && ball.getY() > 115)//
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(30 ,90);
	}
	else if ( ball.getY() > 170)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(8, 175.5);
	}
	else if (ball.getY() < 10)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(8, 4.5);
	}
	else if(ball.getX() + ball.getY() < 19)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(4.5, 11.5);
	}
	else if (ball.getX() + ball.getY() < 19|| ball.getY() - ball.getX() < -201)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(4.5, 11.5);
	}
	else if (ball.getY() - ball.getX() > 161|| ball.getX() + ball.getY() > 381)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
		goal = rcsc::Vector2D(4.5, 168.5);
	}

	cost += ball.dist(pos) / (ballvel - vel.setLength(4.8)).length() * 2;
	cost += ((goal - ball).dir() - (ball - pos).dir()).abs() / 7;
	if (((goal - ball).dir() - (ball - pos).dir()).abs() - 90 < 0) cost -= 100;
	logg.test2 << "cost:" << cost << std::endl;
	return cost;
}

rcsc::Vector2D Soccer::gettarget_Bound()//边界目标点选取
{
	rcsc::Vector2D ball = plt->getBall().pos,goal;
	if (ball.getX() > 210 && ball.getY() < 65)//右下
	{
		goal = rcsc::Vector2D(215.5, 8);
	}
	else if (ball.getX() > 210 && ball.getY() > 115)
	{
\
		goal = rcsc::Vector2D(215.5, 172);
	}
	else if (ball.getX() < 10 && ball.getY() < 65)//看情况可以骚一手
	{
		goal = rcsc::Vector2D(30, 90);
	}
	else if (ball.getX() < 10 && ball.getY() > 115)//
	{
		goal = rcsc::Vector2D(30, 90);
	}
	else if (ball.getY() > 170)
	{
		goal = rcsc::Vector2D(8, 175.5);
	}
	else if (ball.getY() < 10)
	{
		goal = rcsc::Vector2D(8, 4.5);
	}
	else if (ball.getX() + ball.getY() < 19)
	{
		goal = rcsc::Vector2D(4.5, 11.5);
	}
	else if (ball.getX() + ball.getY() < 19 || ball.getY() - ball.getX() < -201)
	{
		goal = rcsc::Vector2D(4.5, 11.5);
	}
	else if (ball.getY() - ball.getX() > 161 || ball.getX() + ball.getY() > 381)
	{
		goal = rcsc::Vector2D(4.5, 175.5);
	}
	return goal;
}

double Soccer::Takeballcost(int id,bool our)//
{
	rcsc::Vector2D pos, vel, ball, ballvel, goal;
	double cost=0,min=1000;
	ball = plt->getBall().pos;
	ballvel = plt->getBall().vel;
	for (int i = 0; i <= 3; i++)
	{
		cost = 0;
		if (our)
		{
			vel = plt->ourRobot(id).vel;
			pos = plt->ourRobot(id).pos;
			pos = pos + vel * i;
			goal = Field::oppGoal();
		}
		else
		{
			vel = plt->oppRobot(id).vel;
			pos = plt->oppRobot(id).pos;
			pos = pos + vel * i;
			goal = Field::ourGoal();
		}
		cost += ball.dist(pos) / (ballvel - vel.setLength(4.8)).length() * 2;
		cost += ((goal - ball).dir() - (ball - pos).dir()).abs() / 6;
		if (((Field::ourGoal() - ball).dir() - (ball - pos).dir()).abs() < 60)cost += 20;
		if (((Field::ourGoal() - ball).dir() - (ball - pos).dir()).abs() < 30)cost += 50;
		if (cost < min)min = cost;
	}
	logg.test2 <<id<< "cost:" << cost << std::endl;
	return min;
}
double Soccer::Takeballfast(int id,bool our)
{
	rcsc::Vector2D pos, vel, ball, ballvel;
	double cost = 0;
	ball = plt->getBall().pos;
	ballvel = plt->getBall().vel;
	if (our)
	{
		pos = plt->ourRobot(id).pos;
		vel = plt->ourRobot(id).vel;
	}
	else
	{
		pos = plt->oppRobot(id).pos;
		vel = plt->oppRobot(id).vel;
	}
	cost += ball.dist(pos) / (ballvel - vel.setLength(4.8)).length()*100;
	logg.test2 << "fast:" << cost << std::endl;
	return cost;
}