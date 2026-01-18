#include "stdafx.h"
#include "soccerplayer.h"
#include "field.h"

double Soccer::cost_man_on_the_silver_mountain(int id)
{

	int fast = 1, ang = 1;
	rcsc::Vector2D pos = plt->ourRobot(id).pos, ballvel = plt->getBall().vel, ball = plt->getBall().pos;
	rcsc::AngleDeg deg = (ball - pos).dir() - (-ball + Field::oppGoal()).dir();//球与球员的距离减去球与球门的距离
	rcsc::Segment2D kickball(ball, ball + (ball - pos) * 100), ballline(ball, ballvel * 100);
	if (Field::OppGoalinterexist(kickball))ang = 0.8;
	if (Field::OppGoalinterexist(ballline))fast = 0.5;
	return pos.dist(ball) * fast / ballvel.length() + deg.degree() * ang / 12;
}

void Soccer::man_on_the_silver_mountain()//进攻
{
	logg.test1 << "man on the silver mountain" << std::endl;
	double yball;
	rcsc::Vector2D ball = plt->getBall().pos, ballvel = plt->getBall().vel, position1, position2, position3, position4;
	int id_in_area[3], count, s, id_out_area;
	for (int i = 1; i <= 4; i++)//找到禁区内的三个队员主要队员
	{
		if (playerstatus[i] == 1)id_in_area[0] = i;
		else if (playerstatus[i] == 2)id_in_area[1] = i;
		else if (playerstatus[i] == 3)id_in_area[2] = i;
	}
	for (int j = 0; j <= 1; j++)//主攻队员排序
	{
		for (int i = 0; i <= 1; i++)
		{
			if (cost_man_on_the_silver_mountain(id_in_area[i]) > cost_man_on_the_silver_mountain(id_in_area[i + 1]))
			{
				s = id_in_area[i];
				id_in_area[i] = id_in_area[i + 1];
				id_in_area[i + 1] = s;
			}
		}
	}
	playerstatus[id_in_area[0]] = 1;
	playerstatus[id_in_area[1]] = 2;
	playerstatus[id_in_area[2]] = 3;
	for (int i = 1; i <= 4; i++)//禁区外球员

	{
		if (i == id_in_area[0] || i == id_in_area[1] || i == id_in_area[2])continue;
		else
		{
			id_out_area = i;
		}
	}

	playerstatus[id_out_area] = 4;
	rcsc::Vector2D pos1 = plt->ourRobot(id_in_area[0]).pos;
	rcsc::Segment2D kick(ball, ball + (ball - pos1) * 20);
	if (ourcubes[id_in_area[0]].kickable(ball, ball + ballvel, plt->ourRobot(id_in_area[0]).vel.length()) && ourcubes[id_in_area[0]].kickable_target(Field::oppGoal(), ball))
	{
		shoot_holy_diver(id_in_area[0]);
	}
	else dribble(id_in_area[0], Field::oppGoal(), 4.88);
	//if (Field::OurGoalinterexist(kick))//position1
	//{
	//	if (ballvel.getX() > 0 || (ballvel.getY() > 0 && ball.getY() < 90) || (ballvel.getY() < 0 && ball.getY() > 90))
	//	{
	//		rcsc::AngleDeg a(plt->ourRobot(id_in_area[0]).th);
	//		position1 = ball + ballvel * 2;
	//		position1 = posnormalize(id_in_area[0], 1, position1);
	//		PositionAndStop(id_in_area[0], position1, a, 1.8, 0);
	//	}
	//	else position1 = Field::oppGoal();
	//	dribble(id_in_area[0], position1, 4.88);
	//}
	//else
	//{
	//	position1 = Field::oppGoal();
	//	dribble(id_in_area[0], position1, 4.88);
	//}
	if (ball.getY() > 90)
	{
		position2 = (-Field::oppGoal() + ball);
		position3 = (-Field::oppGoal() + ball);
		position2 = position2.rotate(30) + ball;
		position3 = position3.rotate(-30) + ball;
		if (plt->ourRobot(id_in_area[1]).pos.dist(position2) > plt->ourRobot(id_in_area[2]).pos.dist(position2))
		{
			s = id_in_area[1];
			id_in_area[1] = id_in_area[1 + 1];
			id_in_area[1 + 1] = s;
		}
		//logg.test1 << "pos2:" << position2.getX() << "," << position2.getY() << std::endl;
		position2 = avoidcrash(id_in_area[1], position2);
		position3 = avoidcrash(id_in_area[2], position3);
		position2 = posnormalize(id_in_area[1], 2, position2);
		position3 = posnormalize(id_in_area[2], 3, position3);
		//logg.test1 << "pos2N:" << position2.getX() << "," << position2.getY() << std::endl;
	}
	else
	{
		position2 = (-Field::oppGoal() + ball);
		position3 = (-Field::oppGoal() + ball);
		position2 = position2.rotate(-30) + ball;
		position3 = position3.rotate(30) + ball;
		if (plt->ourRobot(id_in_area[1]).pos.dist(position2) > plt->ourRobot(id_in_area[2]).pos.dist(position2))
		{
			s = id_in_area[1];
			id_in_area[1] = id_in_area[1 + 1];
			id_in_area[1 + 1] = s;
		}
		//logg.test1 << "pos2:" << position2.getX() << "," << position2.getY() << std::endl;
		position2 = avoidcrash(id_in_area[1], position2);
		position3 = avoidcrash(id_in_area[2], position3);
		position2 = posnormalize(id_in_area[1], 2, position2);
		position3 = posnormalize(id_in_area[2], 3, position3);
		//logg.test1 << "pos2N:" << position2.getX() << "," << position2.getY() << std::endl;
	}/////////////////////////////////////////////
	position4.x = 60;
	position4.y = ball.getY();
	rcsc::AngleDeg a(plt->ourRobot(id_in_area[1]).th), b(plt->ourRobot(id_in_area[2]).th), c(plt->ourRobot(id_out_area).th);
	//position3.y = ymin;
	//position4.y = ymax;
	position4 = avoidcrash(id_out_area, position4);
	position4 = posnormalize(id_out_area, 4, position4);
	logg.test1 << "num2x: " << position2.getX() << std::endl;
	logg.test1 << "num2y: " << position2.getY() << std::endl;
	logg.test1 << "num3x: " << position3.getX() << std::endl;
	logg.test1 << "num3y: " << position3.getY() << std::endl;
	logg.test1 << "num4x: " << position4.getX() << std::endl;
	logg.test1 << "num4y: " << position4.getY() << std::endl;
	PositionAndStop(id_in_area[1], position2, a, 1.8, 0);
	PositionAndStop(id_in_area[2], position3, b, 1.8, 0);
	PositionAndStop(id_out_area, position4, c, 1.8, 0);
	if (Field::InFobidenBound(ball))Goalie_holy_diver_care(0);
	else Goalie_holy_diver(0);
	logg.test1 << "id_status:" << "1, 2, 3, 4   " << playerstatus[1] << "  " << playerstatus[2] << "  " << playerstatus[3] << "  " << playerstatus[4] << std::endl;
}