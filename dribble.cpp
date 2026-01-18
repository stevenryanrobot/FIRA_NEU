#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"
rcsc::Vector2D Catchingballplace(rcsc::Vector2D target,rcsc::Vector2D ball)
{
	rcsc::Vector2D ready,o(10,0);
	ready = ball + (ball - target).setLengthVector(13);
	rcsc::Segment2D R(ball,ready);
	if (ball.x>217||ball.x<3||ball.y>177||ball.y<3)
	{


		if (ball.getY() > 168)
		{

			return Field::L_Topforball().projection(R.terminal());
		}
		else if (ball.getY() < 12)
		{
			return Field::L_Bottomforball().projection(R.terminal());
		}
		else if (ball.getX() < 12)
		{
			return Field::L_Leftforball().projection(R.terminal());
		}
		else 
		{
			return Field::L_Rightforball().projection(R.terminal());
		}
	}
	else return ready;
}

void Soccer::dribble(int id, rcsc::Vector2D target, double v)
{
	

	double distancenow,predistance;
	rcsc::Vector2D ball,predribble,catchplace,readypos,dribblepos,ball_robot,target_robot,robotpos,danger;
	ball = plt->getBall().pos;
	ball_robot = ball - plt->ourRobot(id).pos;
	robotpos = plt->ourRobot(id).pos;
	danger = plt->oppRobot(getoppclosest(ball)).pos;

	if(robotpos.getX()>212)
	rcsc::Segment2D movingball(ball,ball+plt->getBall().vel);
	int t;
	distancenow = plt->ourRobot(id).pos.dist(ball);
	t = distancenow / 8.2;
	rcsc::AngleDeg  robotth(plt->ourRobot(id).th);
	rcsc::Line2D robotline(plt->ourRobot(id).pos, robotth);
	
	target_robot = target - ball;
	rcsc::AngleDeg theta_T_B(target_robot.th()), theta_R_B(ball_robot.th());
	test = (theta_T_B - theta_R_B).abs();
	logg.test1 << "id:" << id << std::endl;
	logg.test1 << "test:" << test << std::endl;
	logg.test1 << "T_balltheta:" << theta_T_B.degree() << std::endl;
	logg.test1 << "B_Rtheta:" << theta_R_B.degree() << std::endl;
	if (t >= 5)
	{
		t = 5;
	}
	double mindistance = 1000;
	for (int i = 0; i < t; i++)
	{
		predribble = predictball(i);
		catchplace = Catchingballplace(target, ball);
		catchplace=posnormalize(id, 0, catchplace);//////////////////////
		predistance = (predribble - plt->ourRobot(id).pos).length() - (i + 1) * 3;
		if (predistance <= mindistance)
		{
			mindistance = predistance;
			readypos = catchplace;

		}
	}
	if ((1||distancenow>20)&&plt->ourRobot(id).pos.dist(catchplace)>=15&& test>45)
	{

		//PositionAndStop(id, readypos, (ball - readypos).th().degree(), plt->getBall().vel.length()*1.3+1.8,0);
		catchplace = avoidcrash(id, catchplace);
		catchplace = posnormalize(id, 1, catchplace);
		heading_position(id, catchplace, v);

		/*if (plt->ourRobot(id).pos.dist(readypos) < 5)
		{
				heading_position(id, ball, 4.8);

		}*/
	}
	else
	{

	/*	logg.test1 << "dist1:  " <<ourcubes[id].distl(ball) << std::endl;
		logg.test1 << "dist2:  " << ourcubes[id].dist2(ball) << std::endl;
		logg.test1 << "TF: " << ourcubes[id].kickable(ball, ball + plt->getBall().vel, plt->ourRobot(id).vel.length()) << std::endl;
		*/

		if (plt->getBall().vel.length() > v)
		{
			ball = ball + plt->getBall().vel*t;
			ball = avoidcrash(id, ball);
			ball = posnormalize(id, 1, ball);
			if (ourcubes[id].kickable_target(target, plt->getBall().pos) && ( (plt->getBall().vel.dir() - theta_T_B).abs() > 40) && ourcubes[id].kickable(plt->getBall().pos, plt->getBall().pos + plt->getBall().vel, plt->ourRobot(id).vel.length()))
			{
				kick_holy_diver(id, target);
				logg.test1 << "e_theta:13  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}
			 else if ((theta_T_B - theta_R_B).abs() <40  &&(theta_T_B - theta_R_B).abs() > 10 && ourcubes[id].dribbleable(ball) )
			{
				rcsc::AngleDeg e_theta = (theta_T_B - theta_R_B);
				rcsc::Vector2D newpos = (ball - plt->ourRobot(id).pos);
				e_theta /= 40;
				heading_position(id, plt->ourRobot(id).pos + newpos.rotate(e_theta), plt->getBall().vel.length() + 5);
				logg.test1 << "e_theta:12  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}
			else 
			{
				heading_position(id, ball, plt->getBall().vel.length()+0.8 );
				logg.test1 << "e_theta:11  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}
		}
		else
		{
			ball = ball + plt->getBall().vel * t ;
			ball = avoidcrash(id, ball);
			ball = posnormalize(id, 1, ball);
			if (ourcubes[id].kickable_target(target, plt->getBall().pos) && ( (plt->getBall().vel.dir() - theta_T_B).abs() > 40) && ourcubes[id].kickable(plt->getBall().pos, plt->getBall().pos + plt->getBall().vel, plt->ourRobot(id).vel.length()))
			{
				kick_holy_diver(id, target);
				logg.test1 << "e_theta:23  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}
			 else if ((theta_T_B - theta_R_B).abs() < 20 && (theta_T_B - theta_R_B).abs() > 10 && ourcubes[id].dribbleable(ball))
			{
				rcsc::AngleDeg e_theta = (theta_T_B - theta_R_B);
				rcsc::Vector2D newpos = (ball - plt->ourRobot(id).pos);
				e_theta /= 40;
				heading_position(id, plt->ourRobot(id).pos + newpos.rotate(e_theta), plt->getBall().vel.length() + 5);
				logg.test1 << "e_theta:22  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}

			else 

			{
				heading_position(id, ball, v);
				logg.test1 << "e_theta:21  " << (theta_T_B - theta_R_B).abs() << std::endl;
			}
		}
		
		

	}
}



