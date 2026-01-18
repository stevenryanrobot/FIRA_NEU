#include "stdafx.h"
#include "soccerplayer.h"
void Soccer::Goalie_holy_diver(int id)
{
	rcsc::Vector2D ball = plt->getBall().pos;
	rcsc::Line2D DefenseLine(rcsc::Vector2D(212.85, 0), rcsc::Vector2D(212.85, 30));
	rcsc::Vector2D pos = plt->ourRobot(id).pos, predicted = ball+plt->getBall().vel*100;
	rcsc::Segment2D goalline(Field::ourGoalB(), Field::ourGoalT());
	rcsc::Line2D balltrackline(ball, predicted);
	rcsc::Segment2D balltrack(ball, predicted);
	rcsc::AngleDeg standard(90);
	if (ourcubes[id].kickable(ball, plt->getBall().vel + ball, 1) && ball.getX() < pos.getX() - 6 && plt->oppRobot(getoppclosest(ball)).pos.dist(ball) > 40&& plt->getBall().vel.length()<1)
	{
		kick_holy_diver(id, Field::oppGoal());
		return;
	}
	if(goalline.existIntersection(balltrack))
	{
		double x;
		if (abs(pos.x - 215) < 2)x = pos.x;
		else x = 215;
		rcsc::Vector2D defense_y = DefenseLine.intersection(balltrackline);
		rcsc::Vector2D defensepoint(x, defense_y.getY());
		rcsc::Vector2D deepdefense(x, ball.getY());//进入球门，不一定会用

		if (ball.getX() < 212.85)
		{
			PositionAndStop(id, defensepoint, standard, 3, 1);
			//heading_position(id, defensepoint, 4.8);

			/*PositionAndStop(id, defensepoint, standard, 1.8,0);*/
		}
		else if (ball.getX() > 212.85 && abs(ball.getY() - 90) < 35)
		{
			PositionAndStop(id, deepdefense, standard, 3, 1);
			//heading_position(id, ball, 4.8);
		/*	PositionAndStop(id, deepdefense, standard, 1.8,0);*/
		}
		else PositionAndStop(id, defensepoint, standard, 3, 1);
		
	}
	else
	{
		double x;
		if (abs(pos.x - 215) < 2)x = pos.x;
		else x = 215;
		rcsc::Vector2D L1 = Field::ourGoalB() - ball;
		rcsc::Vector2D L2 = Field::ourGoalT() - ball;
		rcsc::AngleDeg bisec(L1.th().degree() / 2 + L2.th().degree() / 2);
		rcsc::Line2D L3(ball,bisec);
		rcsc::Vector2D predefense(x, goalline.intersection(L3).getY());
		
		PositionAndStop(id, predefense, standard, 3,1);
		////heading_position(id, predefense, 4.8);
		//logg.test1 << "positiongoallie:" << predefense.getX() << std::endl;
		//logg.test1 << "positiongoallie:" << predefense.getY() << std::endl;
		//logg.test1 << "positiongoallie:" << bisec.degree() << std::endl;
	}
}

void Soccer::Goalie_holy_diver_care(int id)
{
	rcsc::Vector2D ball = plt->getBall().pos;
	rcsc::Line2D DefenseLine(rcsc::Vector2D(212.85, 0), rcsc::Vector2D(212.85, 30));
	rcsc::Vector2D pos = plt->ourRobot(id).pos, predicted = ball + plt->getBall().vel * 100;
	rcsc::Segment2D goalline(Field::ourGoalB(), Field::ourGoalT());
	rcsc::Line2D balltrackline(ball, predicted);
	rcsc::Segment2D balltrack(ball, predicted);
	rcsc::AngleDeg standard(90);
	if (ourcubes[id].kickable(ball, plt->getBall().vel + ball, 1)&&ball.getX()<pos.getX()-6&& plt->oppRobot(getoppclosest(ball)).pos.dist(ball)>40 && plt->getBall().vel.length() < 1)
	{
		kick_holy_diver(id, Field::oppGoal());
		return;
	}
	if (goalline.existIntersection(balltrack))
	{
		double x;
		if (abs(pos.x - 215) < 2)x = pos.x;
		else x = 215;
		rcsc::Vector2D defense_y = DefenseLine.intersection(balltrackline);
		rcsc::Vector2D defensepoint(x, defense_y.getY());
		rcsc::Vector2D deepdefense(x, ball.getY());//进入球门，不一定会用

		if (ball.getX() < 212.85)
		{
			PositionAndStop(id, defensepoint, standard, 3, 1);
			//heading_position(id, defensepoint, 4.8);

			/*PositionAndStop(id, defensepoint, standard, 1.8,0);*/
		}
		else if (ball.getX() > 212.85 && abs(ball.getY() - 90) < 35)
		{
			PositionAndStop(id, deepdefense, standard, 3, 1);
			//heading_position(id, ball, 4.8);
		/*	PositionAndStop(id, deepdefense, standard, 1.8,0);*/
		}
		else PositionAndStop(id, defensepoint, standard, 3, 1);

	}
	else
	{
		double x;
		if (abs(pos.x - 215) < 2)x = pos.x;
		else x = 215;
		rcsc::Vector2D L1 = Field::ourGoalB() - ball;
		rcsc::Vector2D L2 = Field::ourGoalT() - ball;
		rcsc::AngleDeg bisec(L1.th().degree() / 2 + L2.th().degree() / 2);
		rcsc::Line2D L3(ball, bisec);

		rcsc::Vector2D predefense(x, goalline.intersection(L3).getY());
		if (goalline.intersection(L3).getY() - 90 > 15.5&&plt->ourRobot(getourclosest(ball) && plt->ourRobot(getourclosest(ball)).pos.getY() < 90).pos.getX()>210)
			predefense.y = 108.5;
		else if(goalline.intersection(L3).getY() - 90 < -15.5&& plt->ourRobot(getourclosest(ball)).pos.getX() > 210 && plt->ourRobot(getourclosest(ball)).pos.getY() < 90)predefense.y = 71.5;
		PositionAndStop(id, predefense, standard, 3, 1);
		////heading_position(id, predefense, 4.8);
		//logg.test1 << "positiongoallie:" << predefense.getX() << std::endl;
		//logg.test1 << "positiongoallie:" << predefense.getY() << std::endl;
		//logg.test1 << "positiongoallie:" << bisec.degree() << std::endl;
	}
}