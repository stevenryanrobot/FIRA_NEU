#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"

void Soccer::ToPoint(int id, const rcsc::Vector2D& targetPos, const rcsc::Vector2D& targetVel, double Kp)
{
	//calculat the path distance
	double pathdist = plt->ourRobot(id).pos.dist(targetPos);//距离计算
	double pathTh = -(targetPos - plt->ourRobot(id).pos).th().degree();//目标角度
	double angle = fabs(plt->ourRobot(id).th-pathTh);//求绝对值角度插
	if (Soccer::teamColor == 0)//teamColor = YELLOW
	{
		pathTh *= -1;
		angle = 180 - angle;
	}
	// if Yellow pathTh *= -1;
	// if Yellow angle = 180 - angle;
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;
	angle = fabs(angle);
	if (pathdist < 3) {
		if (pathdist < 2) {
			if (angle < 90) pathTh = targetVel.th().degree();
			else pathTh = -targetVel.th().degree();
		}
		
	}
	if (angle <= 15)
	{
		setRobotVel(id, pathdist*Kp, 0);
	}
	else if (angle >= 165 && angle <= 180) {
		setRobotVel(id, -pathdist*Kp, 0);
	}
	else if (angle > 15 && angle <= 90) {
		setRobotAng(id, pathTh);
	}
	else if (angle > 90 && angle < 165) {
		setRobotAng(id, 180 + pathTh);
	}
}