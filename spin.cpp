#include "stdafx.h"
#include "soccerplayer.h"
#include "pid.h"

void Soccer::spin(int id, const rcsc::Vector2D&  targetPos, const double &targetVel) 
{
	const rcsc::Vector2D& ballPos = rcsc::Vector2D(plt->getBall().pos);
	const rcsc::Ray2D& ballPath = rcsc::Ray2D(plt->getBall().pos, plt->getBall().vel);
	const rcsc::Vector2D& robotPos = rcsc::Vector2D(plt->ourRobot(id).pos);
	double angle = rcsc::Vector2D::angleOf(robotPos, ballPos, targetPos).degree();
	rcsc::Circle2D robotArea = rcsc::Circle2D(plt->ourRobot(id).pos, ROBOT_HALF_WIDTH*sqrt(double(2)));
	double vel_w = {(angle > 0) ? -40. : 40. };
	if (targetVel != -1)
		vel_w = (angle > 0) ? -targetVel : targetVel;
	if (Soccer::teamColor == 0)
		vel_w *= -1;
	setRobotVel(id, 0, vel_w);
}
