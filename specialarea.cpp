#include "stdafx.h"
#include "soccerplayer.h"

bool Soccer::specialsituation1()//opp
{
	double right = 37, top = 130, bottom = 50, count = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (plt->ourRobot(i).pos.getX() < right && abs(plt->ourRobot(i).pos.getY() - 90) < 40)count++;

	}
	if (count >= 3)return true && (plt->getBall().pos.getX() < right && abs(plt->getBall().pos.getY() - 90) < 40);
	else return false;
}


bool Soccer::specialsituation2()//our
{
	double left = 183, top = 130, bottom = 50, count = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (plt->ourRobot(i).pos.getX() > left && abs(plt->ourRobot(i).pos.getY() - 90) < 40)count++;

	}
	if (count >= 2)return true && (plt->getBall().pos.getX() > left && abs(plt->getBall().pos.getY() - 90) < 40);
	else return false;
}
bool Soccer::player_in_area1(int id, bool our)//opp
{
	double right = 37, top = 130, bottom = 50, count = 0;
	if (our)
		return (plt->ourRobot(id).pos.getX() < right && abs(plt->ourRobot(id).pos.getY() - 90) < 40);
	else
		return (plt->oppRobot(id).pos.getX() < right && abs(plt->oppRobot(id).pos.getY() - 90) < 40);
}

bool Soccer::player_in_area2(int id, bool our)//our
{
	double left = 183, top = 130, bottom = 50, count = 0;
	if (our)
		return (plt->ourRobot(id).pos.getX() > left && abs(plt->ourRobot(id).pos.getY() - 90) < 40);
	else
		return (plt->oppRobot(id).pos.getX() > left && abs(plt->oppRobot(id).pos.getY() - 90) < 40);
}
bool Soccer::player_in_area4(int id, bool our)
{
	double left = 205, top = 130, bottom = 50, count = 0;
	if (our)
		return (plt->ourRobot(id).pos.getX() > left && abs(plt->ourRobot(id).pos.getY() - 90) < 25);
	else
		return (plt->oppRobot(id).pos.getX() > left && abs(plt->oppRobot(id).pos.getY() - 90) < 25);
}
bool Soccer::player_in_area3(int id, bool our)
{
	double right = 15, top = 130, bottom = 50, count = 0;
	if (our)
		return (plt->ourRobot(id).pos.getX() < right && abs(plt->ourRobot(id).pos.getY() - 90) < 25);
	else
		return (plt->oppRobot(id).pos.getX() < right && abs(plt->oppRobot(id).pos.getY() - 90) < 25);
}

bool Soccer::ball_in_area2()
{
	double left = 183, top = 130, bottom = 50, count = 0;

	return (plt->getBall().pos.getX() > left && abs(plt->getBall().pos.getY() - 90) < 40);
}
bool Soccer::ball_in_area1()
{
	double right = 37, top = 130, bottom = 50, count = 0;
	return (plt->getBall().pos.getX() < right && abs(plt->getBall().pos.getY() - 90) < 40);
}