#include "stdafx.h"
#include "soccerplayer.h"
#include "field.h"

double Soccer::cost_rainbow(int id)
{

	int fast = 1, ang = 1;
	rcsc::Vector2D pos = plt->ourRobot(id).pos, ballvel = plt->getBall().vel, ball = plt->getBall().pos;
	rcsc::AngleDeg deg = (ball - pos).dir() - (ball - Field::ourGoal()).dir();
	rcsc::Segment2D kickball(ball, ball + (ball - pos) * 100), ballline(ball, ballvel * 100);
	if (Field::OurGoalinterexist(kickball))ang = 1.2;
	if (Field::OurGoalinterexist(ballline))fast = 0.9;
	return pos.dist(ball) * fast / ballvel.length() + deg.degree() * ang / 10;
}

void Soccer::catch_the_rainbow()
{
	logg.test1 << "catch the rainbow:" << std::endl;
	double ymin = 180, ymax = 0;
	rcsc::Vector2D ball = plt->getBall().pos, ballvel = plt->getBall().vel, position1, position2, position3, position4;
	int id_in_area[2], count, s, id_out_area[2];
	for (int i = 1; i <= 4; i++)//找到禁区内的两个队员主要队员
	{
		if (playerstatus[i] == 1)id_in_area[0] = i;
		else if (playerstatus[i] == 2)id_in_area[1] = i;

	}
	if (cost_rainbow(id_in_area[0]) > cost_rainbow(id_in_area[1]))
	{
		s = id_in_area[0];
		id_in_area[0] = id_in_area[1];
		id_in_area[1] = s;
	}
	playerstatus[id_in_area[0]] = 1;
	playerstatus[id_in_area[1]] = 2;
	count = 3;
	s = 0;
	for (int i = 1; i <= 4; i++)//禁区外球员

	{
		if (i == id_in_area[0] || i == id_in_area[1])continue;
		else
		{
			id_out_area[s] = i;
			s++;
		}
	}
	if (plt->ourRobot(id_out_area[0]).pos.getX() < plt->ourRobot(id_out_area[1]).pos.getX());
	else
	{
		s = id_out_area[0];
		id_out_area[0] = id_out_area[1];
		id_out_area[1] = s;
	}
	playerstatus[id_out_area[0]] = 3;
	playerstatus[id_out_area[1]] = 4;
	rcsc::Vector2D pos1 = plt->ourRobot(id_in_area[0]).pos;
	rcsc::Segment2D kick(ball, ball + (ball - pos1) * 20);
	if (Field::OurGoalinterexist(kick))//position1
	{
		if (ballvel.getX() > 0 || (ballvel.getY() > 0 && ball.getY() < 90) || (ballvel.getY() < 0 && ball.getY() > 90))
		{
			rcsc::AngleDeg a(plt->ourRobot(id_in_area[0]).th);
			position1 = ball + ballvel * 2;
			position1 = posnormalize(id_in_area[0], 1, position1);
			PositionAndStop(id_in_area[0], position1, a, 1.8, 0);
		}
		else position1 = Field::oppGoal();
		dribble(id_in_area[0], position1, 4.88);
	}
	else
	{
		position1 = Field::oppGoal();
		dribble(id_in_area[0], position1, 4.88);
	}
	if (ball.getY() > 90)
	{
		position2 = (-Field::ourGoal() + ball);
		position2 = position2.rotate(-30) + ball;
		logg.test1 << "pos2:" << position2.getX() << "," << position2.getY() << std::endl;
		position2 = avoidcrash(id_in_area[1], position2);

		position2 = posnormalize(id_in_area[1], 2, position2);
		logg.test1 << "pos2N:" << position2.getX() << "," << position2.getY() << std::endl;
	}
	else
	{
		position2 = (-Field::ourGoal() + ball);

		position2 = position2.rotate(30) + ball;
		logg.test1 << "pos2:" << position2.getX() << "," << position2.getY() << std::endl;
		position2 = avoidcrash(id_in_area[1], position2);
		position2 = posnormalize(id_in_area[1], 2, position2);
		logg.test1 << "pos2N:" << position2.getX() << "," << position2.getY() << std::endl;
	}
	position3.x = 170;
	position4.x = 160;
	for (int i = 0; i <= 4; i++)
	{
		if (ymin > plt->oppRobot(i).pos.getY())ymin = plt->oppRobot(i).pos.getY();
		if (ymax < plt->oppRobot(i).pos.getY())ymax = plt->oppRobot(i).pos.getY();
	}
	rcsc::AngleDeg a(plt->ourRobot(id_in_area[1]).th), b(plt->ourRobot(id_out_area[0]).th), c(plt->ourRobot(id_out_area[1]).th);
	position3.y = ymin;
	position4.y = ymax;
	position3 = avoidcrash(id_out_area[0], position3);
	position4 = avoidcrash(id_out_area[1], position4);
	position3 = posnormalize(id_out_area[0], 3, position3);
	position4 = posnormalize(id_out_area[1], 4, position4);
	logg.test1 << "num2x: " << position2.getX() << std::endl;
	logg.test1 << "num2y: " << position2.getY() << std::endl;
	logg.test1 << "num3x: " << position3.getX() << std::endl;
	logg.test1 << "num3y: " << position3.getY() << std::endl;
	logg.test1 << "num4x: " << position4.getX() << std::endl;
	logg.test1 << "num4y: " << position4.getY() << std::endl;
	PositionAndStop(id_in_area[1], position2, a, 1.8, 0);
	PositionAndStop(id_out_area[0], position3, a, 1.8, 0);
	PositionAndStop(id_out_area[1], position4, a, 1.8, 0);
	if (Field::InFobidenBound(ball))Goalie_holy_diver_care(0);
	else Goalie_holy_diver(0);
	logg.test1 << "id_status:" << "1, 2, 3, 4   " << playerstatus[1] << "  " << playerstatus[2] << "  " << playerstatus[3] << "  " << playerstatus[4] << std::endl;
}
