
#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"

void Soccer::Angle_n(int id, rcsc::AngleDeg desiredangle)
{
	//double  vl = 0, vr = 0, kd =2 , kp = 1.5;
	rcsc::AngleDeg e_theta(desiredangle-plt->ourRobot(id).th);
	e_theta.normalize_again();
	//angPID[id].Kd = kd;
	//angPID[id].Ki = 0.12;
	//angPID[id].Kp = kp;
	//angPID[id].maxSum = 35;
	angPID[id].run(e_theta.degree());
	if (abs(e_theta.degree()) >= 30)
	{
		robots[id].velocityLeft = -angPID[id].lastOut*1.2;
		robots[id].velocityRight = angPID[id].lastOut*1.2;
	}
	else
	{
		robots[id].velocityLeft = -angPID[id].lastOut * 0.8;
		robots[id].velocityRight = angPID[id].lastOut * 0.8;
	}
	if (abs(e_theta.degree() -plt->ourRobot(id).w / 2) <3&& abs(e_theta.degree() + plt->ourRobot(id).w / 2) < 3&&e_theta.abs()<4)
	{
		robots[id].velocityLeft = 0;
		robots[id].velocityRight =0;
	}
}