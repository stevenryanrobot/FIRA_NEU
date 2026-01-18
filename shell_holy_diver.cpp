#include "stdafx.h"
#include "soccerplayer.h"
void Soccer::shell_holy_diver(int id)//
{
	logg.test1 << "shell holy diver:" << std::endl;
	rcsc::Vector2D pos = plt->ourRobot(id).pos;
	rcsc::Vector2D ball = plt->getBall().pos;
	int passid = getourclosest(ball);
	int positionid[3],ids[2],status[3];

	rcsc::Vector2D goal(0, 90);
	
	rcsc::Vector2D passpos =plt->ourRobot( getourclosest(pos)).pos+plt->ourRobot(passid).vel*2;

	rcsc::Vector2D position1, position2, position3,sixty(-45, 0),deffense= ( ball-Field::oppGoal());
	position1 = ball + deffense.setLength(60) + plt->getBall().vel * 3;
	position2 = ball + sixty.rotate(130) + plt->getBall().vel * 3;
	position3 = ball + sixty.rotate(100) + plt->getBall().vel * 3;
	if (ball.getY() < 90)
	{
		int status[3] = { 3,1,2 };
		double distance=1000;
		for (int i = 1; i <= 4; i++)
		{
			if (i == id) continue;
			else
			{
				if (position2.dist(plt->ourRobot(i).pos) <= distance)
				{
					distance = position2.dist(plt->ourRobot(i).pos);
					positionid[1] = i;
					playerstatus[i] = 2;
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
			playerstatus[ids[1]] = 3;
			positionid[0] = ids[0];
			playerstatus[ids[0]] = 4;
		}
		else
		{
			playerstatus[ids[1]] = 4;
			playerstatus[ids[0]] = 3;
			positionid[2] = ids[0];
			positionid[0] = ids[1];
		}
	}
	else
	{
		int status[3] = { 3,2,1 };
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
					playerstatus[i] = 2;
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
			playerstatus[ids[1]] = 3;
			playerstatus[ids[0]] = 4;
			positionid[1] = ids[1];
			positionid[0] = ids[0];
		}
		else
		{
			playerstatus[ids[1]] = 4;
			playerstatus[ids[0]] = 3;
			positionid[1] = ids[0];
			positionid[0] = ids[1];
		}
	}
	position1=avoidcrash(positionid[0], position1);
	position2 = avoidcrash(positionid[1], position2);
	position3 = avoidcrash(positionid[2], position3);
	rcsc::Vector2D danger = plt->oppRobot(getoppclosest(ball)).pos;
	logg.test1 << "Num1x: " << position1.getX() << std::endl;
	logg.test1 << "Num1y: " << position1.getY() << std::endl;
	logg.test1 << "Num2x: " << position2.getX() << std::endl;
	logg.test1 << "Num2y: " << position2.getY() << std::endl;
	logg.test1 << "Num3x: " << position3.getX() << std::endl;
	logg.test1 << "Num3y: " << position3.getY() << std::endl;
	//logg.test1 << "position1: " << std::endl;
	position1 = posnormalize(positionid[0],status[0],position1);
	//logg.test1 << "position2: "  << std::endl;
	position2 = posnormalize(positionid[1], status[1], position2);
	//logg.test1 << "position3: "<< std::endl;
	position3 = posnormalize(positionid[2], status[2], position3);
	logg.test1 << "num1x: " << position1.getX() << std::endl;
	logg.test1 << "num1y: " << position1.getY() << std::endl;
	logg.test1 << "num2x: " << position2.getX() << std::endl;
	logg.test1 << "num2y: " << position2.getY() << std::endl;
	logg.test1 << "num3x: " << position3.getX() << std::endl;
	logg.test1 << "num3y: " << position3.getY() << std::endl;
	//if (danger.dist(ball) < 15 && ourcubes[id].kickable(ball,ball+plt->getBall().vel,plt->ourRobot(id).vel.length()))kick(id, passpos);
	dribble(id, goal, 4.88);
	if (plt->ourRobot(id).pos.dist(goal) < 20 || (ball.getX() < 35 && abs(ball.getY() - 90) < 40))shoot_holy_diver(id);

	rcsc::AngleDeg a(plt->ourRobot(positionid[0]).th), b(plt->ourRobot(positionid[1]).th), c(plt->ourRobot(positionid[2]).th);
	PositionAndStop(positionid[0], position1,a,1.8,0);
	PositionAndStop(positionid[1], position2, b, 1.8,0);
	PositionAndStop(positionid[2], position3,c, 1.8,0);
	logg.test1 << "id_status:" << "1, 2, 3, 4   " << playerstatus[1] << "  " << playerstatus[2] << "  " << playerstatus[3] << "  " << playerstatus[4] << std::endl;
}
void Soccer::shell_holy_diver_Bound(int id)
{
	logg.test1 << "shell holy diver bound:" << std::endl;
	logg.test1 << "ballpos:" << plt->getBall().pos.getX() << "," << plt->getBall().pos.getY() << std::endl;
	rcsc::Vector2D pos = plt->ourRobot(id).pos;
	rcsc::Vector2D ball = plt->getBall().pos;
	int passid = getourclosest(ball);
	int positionid[3], ids[2];
	rcsc::Vector2D goal = gettarget_Bound();

	rcsc::Vector2D passpos = plt->ourRobot(getourclosest(pos)).pos + plt->ourRobot(passid).vel * 2;

	rcsc::Vector2D position1, position2,position3, sixty(-60, 0), deffense = (ball - gettarget_Bound());
	position1 = ball + deffense.setLength(50);//1,2,3
	position2 = -ball + Field::ourGoal();
	if (ball.getX() > 110)position3 = rcsc::Vector2D(190, 90);//ÖÐÂ·½ØÇò
	else position3 = rcsc::Vector2D(30, 90);

	if (ball.getY() > 90 && ball.getX() > 210) { position2.x = 0; position2.y = -1; position2.rotate(-45).setLength(45); }
	else if (ball.getY() < 90 && ball.getX() > 210){position2.x = 0; position2.y = 1; position2.rotate(45).setLength(45);}
	else if (ball.getY() > 210) { position2.x = 1; position2.y = 0; position2.rotate(-45).setLength(45); }
	else if (ball.getY() < 10){position2.x = 1; position2.y = 0; position2.rotate(45).setLength(45);}
	else if (ball.getX() < 10&&ball.getY() > 90) { position2.x = 0; position2.y = 1; position2.rotate(-90).setLength(45); }
	else if (ball.getX() < 10 && ball.getY() < 90) { position2.x = 0; position2.y = -1; position2.rotate(90).setLength(45); }
	position3 = ball*0.3 + position3*0.7;
	position2 = ball + position2;
	int status[3] = { 2,3,4 };
	double distance = 1000;
	for (int i = 1; i <= 4; i++)
	{
		if (i == id) continue;
		else
		{
			if (position2.dist(plt->ourRobot(i).pos) <= distance)
			{
				distance = position1.dist(plt->ourRobot(i).pos);
				positionid[0] = i;
				playerstatus[i] = 2;
			}
		}
	}
	int j = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (i != id && i != positionid[0])
		{
			ids[j] = i;
			j = j + 1;
		}
	}
	if (position2.dist(plt->ourRobot(ids[0]).pos) > position2.dist(plt->ourRobot(ids[1]).pos))
	{
		positionid[1] = ids[1];
		playerstatus[ids[1]] = 3;
		positionid[2] = ids[0];
		playerstatus[ids[0]] = 4;
	}
	else
	{
		playerstatus[ids[0]] = 3;
		playerstatus[ids[1]] = 4;
		positionid[2] = ids[1];
		positionid[1] = ids[0];
	}

	/*if (ball.getY() < 90)
	{
		int status[3] = { 3,1,2 };
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
					playerstatus[i] = 2;
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
			playerstatus[ids[1]] = 3;
			positionid[0] = ids[0];
			playerstatus[ids[0]] = 4;
		}
		else
		{
			playerstatus[ids[0]] = 3;
			playerstatus[ids[1]] = 4;
			positionid[2] = ids[0];
			positionid[0] = ids[1];
		}
	}
	else
	{
		int status[3] = { 3,2,1 };
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
					playerstatus[i] = 2;
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
			playerstatus[ids[1]] = 3;
			playerstatus[ids[0]] = 4;
			positionid[1] = ids[1];
			positionid[0] = ids[0];
		}
		else
		{
			playerstatus[ids[1]] = 4;
			playerstatus[ids[0]] = 3;
			positionid[1] = ids[0];
			positionid[0] = ids[1];
		}
	}*/
	position1 = avoidcrash(positionid[0], position1);
	position2 = avoidcrash(positionid[1], position2);
	position3 = avoidcrash(positionid[2], position3);
	rcsc::Vector2D danger = plt->oppRobot(getoppclosest(ball)).pos;
	logg.test1 << "Num1x: " << position1.getX() << std::endl;
	logg.test1 << "Num1y: " << position1.getY() << std::endl;
	logg.test1 << "Num2x: " << position2.getX() << std::endl;
	logg.test1 << "Num2y: " << position2.getY() << std::endl;
	logg.test1 << "Num3x: " << position3.getX() << std::endl;
	logg.test1 << "Num3y: " << position3.getY() << std::endl;
	//logg.test1 << "position1: " << positionid[0]<<std::endl;
	position1 = posnormalize(positionid[0], status[0], position1);
	//logg.test1 << "position2: " << positionid[1] << std::endl;
	position2 = posnormalize(positionid[1], status[1], position2);
	//logg.test1 << "position3: " << positionid[2]<< std::endl;
	position3 = posnormalize(positionid[2], status[2], position3);
	logg.test1 << "num1x: " << position1.getX() << std::endl;
	logg.test1 << "num1y: " << position1.getY() << std::endl;
	logg.test1 << "num2x: " << position2.getX() << std::endl;
	logg.test1 << "num2y: " << position2.getY() << std::endl;
	logg.test1 << "num3x: " << position3.getX() << std::endl;
	logg.test1 << "num3y: " << position3.getY() << std::endl;
	//if (danger.dist(ball) < 15 && ourcubes[id].kickable(ball,ball+plt->getBall().vel,plt->ourRobot(id).vel.length()))kick(id, passpos);
	
	//logg.test1 << "goal: " << goal.getX() << std::endl;
	//logg.test1 << "goal: " << goal.getY() << std::endl;
	//logg.test1 << "id: " << id << std::endl;
	dribble(id, goal, 4.88);

	rcsc::AngleDeg a(plt->ourRobot(positionid[0]).th), b(plt->ourRobot(positionid[1]).th), c(plt->ourRobot(positionid[2]).th);
	PositionAndStop(positionid[0], position1, a, 1.8, 0);
	PositionAndStop(positionid[1], position2, b, 1.8, 0);
	PositionAndStop(positionid[2], position3, c, 1.8, 0);
	logg.test1 << "id_status:" << "1, 2, 3, 4   " << playerstatus[1] << "  " << playerstatus[2] << "  " << playerstatus[3] << "  " << playerstatus[4] << std::endl;
}