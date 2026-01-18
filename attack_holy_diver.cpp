#include "stdafx.h"
#include "soccerplayer.h"
void Soccer::attack_holy_diver(int id)
{
	rcsc::Vector2D pos = plt->ourRobot(id).pos;
	rcsc::Vector2D ball = plt->getBall().pos;
	int passid = getourclosest(ball);
	int positionid[3], ids[2];
	rcsc::Vector2D passpos = plt->ourRobot(getourclosest(pos)).pos + plt->ourRobot(passid).vel * 4;
	rcsc::Vector2D goal(50, 90);
	dribble(id, goal, 4.88);
	if (plt->ourRobot(id).pos.dist(goal) < 20)shoot_holy_diver(id);
	rcsc::Vector2D position1, position2, position3, sixty(40, 0);
	position1 = pos + sixty + plt->ourRobot(id).vel * 3;
	position2 = pos + sixty.rotate(120) + plt->ourRobot(id).vel * 3;
	position3 = pos + sixty.rotate(120) + plt->ourRobot(id).vel * 3;
	if (ball.getY() < 90)
	{
		double distance = 1000;
		for (int i = 1; i <= 4; i++)
		{
			if (i == id) continue;
			else
			{
				if (position2.dist(plt->ourRobot(i).pos) <= distance)
				{
					distance = position2.dist(plt->ourRobot(i).pos);
					positionid[1] = i;
				}
			}
		}
		int j = 0;
		for (int i = 1; i <= 4; i++)
		{
			if (i != id && i != positionid[1])
			{
				ids[j] = i;
				j = j + 1;
			}
		}
		if (position3.dist(plt->ourRobot(ids[0]).pos) > position3.dist(plt->ourRobot(ids[1]).pos))
		{
			positionid[2] = ids[1];
			positionid[0] = ids[0];
		}
		else
		{
			positionid[2] = ids[0];
			positionid[0] = ids[1];
		}
	}
	else
	{
		double distance = 1000;
		for (int i = 1; i <= 4; i++)
		{
			if (i == id) continue;
			else
			{
				if (position3.dist(plt->ourRobot(i).pos) <= distance)
				{
					distance = position3.dist(plt->ourRobot(i).pos);
					positionid[2] = i;
				}
			}
		}
		int j = 0;
		for (int i = 1; i <= 4; i++)
		{
			if (i != id && i != positionid[2])
			{
				ids[j] = i;
				j = j + 1;
			}
		}
		if (position2.dist(plt->ourRobot(ids[0]).pos) > position2.dist(plt->ourRobot(ids[1]).pos))
		{
			positionid[1] = ids[1];
			positionid[0] = ids[0];
		}
		else
		{
			positionid[1] = ids[0];
			positionid[0] = ids[1];
		}
	}
	rcsc::Vector2D danger = plt->oppRobot(getoppclosest(ball)).pos;
	if (danger.dist(ball) < 20 && ourcubes[id].dribbleable(ball))kick(id, passpos);
	heading_position(positionid[0], position1, 4.88);
	heading_position(positionid[1], position2, 4.88);
	heading_position(positionid[2], position3, 4.88);



}
