#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"
void Soccer::heading_position(int id, rcsc::Vector2D target, double v)
{
	rcsc::Vector2D targetn=target;
	if (target.getX() > 215)targetn.x = 215;
	else if (target.getX() < 5)targetn.x = 5;
	if (target.getY() > 175) targetn.y = 175;
	else if (target.getY() < 5)targetn.y = 5;

	rcsc::Vector2D velocitynow= plt->ourRobot(id).vel;
	bool face = true;
	rcsc::Vector2D o(0, 0),tran_target;
	rcsc::AngleDeg turnangle, posangle, vangle;
	tran_target = targetn - plt->ourRobot(id).pos;
	posangle = tran_target.dir();
	turnangle = posangle - plt->ourRobot(id).th;
	vangle = posangle - plt->ourRobot(id).vel.dir();
	double velocitycontrol,wcontrol;
	if (turnangle.degree() > 90)
	{//判断小车是否是正面前进
		face = false;
		turnangle.normalize_again();
	}
	else if (turnangle.degree() < -90)
	{
		face = false;
		turnangle.normalize_again();
	}
	else
	{
		face = true;
	}
	
	if (rcsc::AngleDeg::normalize_angle(((plt->ourRobot(id).vel.dir() - posangle).degree()) > 90) && abs(v) > 0.93)//是否反向运动
	{
		robots[id].velocityLeft = 0;
		robots[id].velocityRight = 0;


		return;
	}
	//if (abs(abs(v) - plt->ourRobot(id).vel.dist(o)) <= 0.3||abs(plt->ourRobot(id).vel.dist(o)>v))
	//{
	//	velocitycontrol = u * v+4;
	//}
	//else
	//{
	//	velocitycontrol = 125;
	//}
	velocitycontrol = velPID[id].run(v - plt->ourRobot(id).vel.length());
	wcontrol = angPID[id].run(turnangle.degree());
	logg.test1 << "w:" << wcontrol << std::endl;
	logg.test1 << "degree:" << turnangle.degree() << std::endl;
	//logg.test1 << "Kp:" <<( v - plt->ourRobot(id).vel.length())*velPID[id].Kp << std::endl;
	//logg.test1 << "Ki:" << velPID[id].sum*velPID[id].Ki << std::endl;
	//logg.test1 << "velcon:" << velocitycontrol << std::endl;
	//logg.test1 << "wcon:" << wcontrol << std::endl;
	if (abs(turnangle.degree()) > 20 && plt->ourRobot(id).vel.dist(o) < 0.5||abs(plt->ourRobot(id).pos.getX()-110)>100.6|| abs(plt->ourRobot(id).pos.getY() - 90)>80.6)
	{
		//if (plt->ourRobot(id).w<10&& abs(turnangle.degree()) < 3)
		//{
		//}
		//else
		//{
		//	Angle_n(id, posangle);
		//	logg.test2 << "vl:" << robots[id].velocityLeft << std::endl;
		//	logg.test2 << "vr:" << robots[id].velocityRight << std::endl;
		//	return;
		//}
	}
	if (abs(turnangle.degree()) > 20)
	{



			robots[id].velocityRight = 2 * (face - 0.5) * velocitycontrol + wcontrol;
			robots[id].velocityLeft = 2 * (face - 0.5) * velocitycontrol - wcontrol;

			if (plt->ourRobot(id).vel.length() > 1.5 && turnangle.degree() > 0)robots[id].velocityLeft = 0;
			if (plt->ourRobot(id).vel.length() > 1.5 && turnangle.degree() < 0)robots[id].velocityRight = 0;
	}

	else if (abs(turnangle.degree()) > 5)
	{
		robots[id].velocityRight = 2 * (face - 0.5) * velocitycontrol + wcontrol*0.6;
		robots[id].velocityLeft = 2 * (face - 0.5) * velocitycontrol - wcontrol*0.6;
	}
	else
	{
		robots[id].velocityLeft = velocitycontrol * 2 * (face - 0.5);
		robots[id].velocityRight = velocitycontrol * 2 * (face - 0.5);
	}
	logg.test1 << "Tx:" << target.getX() << std::endl;
	logg.test1 << "Ty:" << target.getY() << std::endl;
	logg.test1 << "velleftt:" << robots[id].velocityLeft << std::endl;
	logg.test1 << "velright:" << robots[id].velocityRight << std::endl;
}