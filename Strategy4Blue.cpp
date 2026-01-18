// Strategy4Blue.cpp  
//

#include "stdafx.h"
#include <string.h>
#include "Strategy4Blue.h"
#include "geometric.h"
#include <fstream>
Soccer soccer;

// Set the team name for blue side.
STRATEGY4BLUE_API void SetBlueTeamName(char* teamName)
{
	// MUST change the name into your own team name!
	//strcpy(teamName, "DEMO Blue");
	strcpy(teamName, "Holy Diver");
	soccer.init(teamName, 0);
}

// Set the positions and rotations of your team when your team places robots first.
// [IN] gameState : the state of game
// [OUT] robots : robots data for placing,including position and rotation
STRATEGY4BLUE_API void SetFormerRobots(PlayMode gameState, Robot robots[])
{
	// This is just for a demo. You may set your own data.
	soccer.updateGM(gameState);
	soccer.setFormerRobots(robots);
}

// Set the positions and rotations of your team when your team places robots last.
// [IN] gameState : the state of game
// [IN] formerRobots : the data of first placing team
// [IN] ball : the position of the ball
// [OUT] laterRobots : robots data for placing,including position and rotation
STRATEGY4BLUE_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], 
	Vector3D ball, Robot laterRobots[])
{	
	// This is just for a demo. You may set your own data.
	soccer.updateGM(gameState);
	soccer.setLaterRobots(laterRobots, formerRobots, ball);
}

// Set the position of the ball when your team get the Goal Kick.
// [IN] gameState : the state of game
// [IN] pBall : the position of the ball
STRATEGY4BLUE_API void SetBall(PlayMode gameState, Vector3D * pBall)
{
	// This is just for a demo. You may set your own data.
	/*
	if (PM_GoalKick_Blue == gameState)
	{
		pBall->x = 210;
		pBall->y = 110;
	}*/
	soccer.updateGM(gameState);
	soccer.setBall(pBall);
}

// Strategy for your team using centimeter unit, cartesian coordinate system.
// The origin is at the left bottom of the field.
STRATEGY4BLUE_API void RunStrategy(Environment* pEnv)
{
	//ToPoint(int id, const rcsc::Vector2D& targetPos, const rcsc::Vector2D& targetVel, double Kp)
	//soccer.ToPoint(4,rcsc::Vector2D(110,90), rcsc::Vector2D(0,100));
	// This is just for a demo. YOU MUST USE YOUR OWN STRATEGY HERE!
	//Goalie(pEnv);
	//LeftWing(pEnv, 1);
	//RightWing(pEnv, 2);
	//CenterDefender(pEnv, 3);
	//CenterAttacker(pEnv, 4);
	soccer.initRobot(pEnv->home);
	soccer.updatePlt(pEnv);
	soccer.logdown();
	//soccer.run(pEnv->home);
	rcsc::AngleDeg c(90);
	rcsc::Vector2D a(8, 4.5), b(0, 90),ball(pEnv->currentBall.pos.x, pEnv->currentBall.pos.y),o(30,30);
	//soccer.ToPoint(1, a, b, 0.2);
	
	//soccer.ToPoint(2, a, b);

		soccer.playon_holy_diver();


		//soccer.Goalie_holy_diver(0);
		////Goalie1(&pEnv->home[0],pEnv);
		//soccer.dribble(2, a, 4.8);
		//soccer.kick_holy_diver(2, b);
	//soccer.PositionAndStop(0, a, c,0,1);

	//soccer.heading_position(2, ball, 4.8);
	//rcsc::Vector2D a(110,90),b(0,0);
	//soccer.setRobotVel(1,2,0);
}

// #############################################################################################
// #############################################################################################

void Goalie(Environment* pEnv)
{
	if (pEnv->currentBall.pos.x < 110)
	{
		Position(pEnv, 0, 205, 90);
	}
	else
	{
		if (pEnv->currentBall.pos.y > 115)
		{
			Position(pEnv, 0, 205, 110);
		}
		else if (pEnv->currentBall.pos.y < 65)
		{
			Position(pEnv, 0, 205, 70);
		}
		else
		{
			Position(pEnv, 0, 205, pEnv->currentBall.pos.y);
			if (pEnv->currentBall.pos.x > 208)
				Position(pEnv, 0, pEnv->currentBall.pos.x, pEnv->currentBall.pos.y);
		}
	}
}

void LeftWing(Environment* pEnv, int id)
{
	Vector3D ball = pEnv->currentBall.pos;
	if (ball.y < 45)
	{
		Position(pEnv, id, ball.x, ball.y);
	}
	else if (ball.y > 135)
	{
		Position(pEnv, id, ball.x + 8, 60);
	}
	else
	{
		if (ball.x > 195)
		{
			if (ball.y > 100)
				Position(pEnv, id, 20, 30);
			else if (ball.y > 40)
				Position(pEnv, id, 20, 60);
			else
				Position(pEnv, id, ball.x, ball.y);
		}
		else
		{
			if (ball.y < 80)
				Position(pEnv, id, ball.x, ball.y);
			else
				Position(pEnv, id, ball.x + 20, 40);
		}
	}
}

void RightWing(Environment* pEnv, int id)
{
	Vector3D ball = pEnv->currentBall.pos;
	if (ball.y < 45)
	{
		Position(pEnv, id, ball.x + 8, 120);
	}
	else if (ball.y > 135)
	{
		Position(pEnv, id, ball.x, ball.y);
	}
	else
	{
		if (ball.x > 195)
		{
			if (ball.y < 80)
				Position(pEnv, id, 20, 150);
			else if (ball.y < 140)
				Position(pEnv, id, 20, 120);
			else
				Position(pEnv, id, ball.x, ball.y);
		}
		else
		{
			if (ball.y > 80)
				Position(pEnv, id, ball.x, ball.y);
			else
				Position(pEnv, id, ball.x + 20, 140);
		}
	}
}

void CenterDefender(Environment* pEnv, int id)
{
	Vector3D ball = pEnv->currentBall.pos;
	if (ball.x < 90)
	{
		Position(pEnv, id, 110, 90);
	}
	else
	{
		if (ball.y > 130)
		{
			Position(pEnv, id, ball.x + 45, 90);
			if (ball.x + 45 > 200)
				Position(pEnv, id, 195, 90);
		}
		else if (ball.y < 50)
		{
			Position(pEnv, id, ball.x + 45, 90);
			if (ball.x + 45 > 200)
				Position(pEnv, id, 195, 90);
		}
		else
		{
			if (ball.x > 195)
			{
				Position(pEnv, id, 195, ball.y);
			}
			else
				Position(pEnv, id, ball.x, ball.y);
		}
	}	
}

void CenterAttacker(Environment* pEnv, int id)
{
	Vector3D ball = pEnv->currentBall.pos;
	if (ball.x < 45)
		Position(pEnv, id, 45, 90);
	else
	{
		if (ball.y > 160)
		{
			Position(pEnv, id, ball.x - 45, 110);
			if (ball.x - 45 < 45)
				Position(pEnv, id, 45, 110);
		}
		else if (ball.y < 20)
		{
			Position(pEnv, id, ball.x - 45, 70);
			if (ball.x - 45 < 45)
				Position(pEnv, id, 20, 70);
		}
		else
		{
			Position(pEnv, id, ball.x, ball.y);
		}
	}
}


void MoonAttack(Robot *robot, Environment *pEnv)
{
	PredictBall(pEnv);
	Position(robot, pEnv->predictedBall.pos.x, pEnv->predictedBall.pos.y);
}

void MoonFollowOpponent(Robot *robot, OpponentRobot *opponent)
{
	Position(robot, opponent->pos.x, opponent->pos.y);
}

void Velocity(Robot *robot, double vl, double vr)
{
	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Angle(Robot *robot, double desired_angle)
{
	double theta_e = 0, vl = 0, vr = 0;
	theta_e = desired_angle - robot->rotation;

	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (theta_e < -90) theta_e += 180;

	else if (theta_e > 90) theta_e -= 180;

	if (abs(theta_e) > 50)
	{
		vl = -9. / 90.0 * theta_e;
		vr = 9. / 90.0 * theta_e;
	}
	else if (abs(theta_e) > 20)
	{
		vl = -11.0 / 90.0 * theta_e;
		vr = 11.0 / 90.0 * theta_e;
	}
	Velocity(robot, vl, vr);
}

void Position(Environment* pEnv, int id, double x, double y)
{
	Position(&(pEnv->home[id]), x, y);
}

void Position(Robot *robot, double x, double y)
{
	double desired_angle = 0, theta_e = 0, d_angle = 0;
	double vl = 0, vr = 0, vc = 100;

	double dx, dy, d_e, Ka = 10.0 / 90.0;
	dx = x - robot->pos.x;
	dy = y - robot->pos.y;
	d_e = sqrt(dx * dx + dy * dy);

	if (dx == 0 && dy == 0)
		desired_angle = 90;
	else
		desired_angle = 180. / PI * atan2((double)(dy), (double)(dx));
	theta_e = desired_angle - robot->rotation;

	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (d_e > 100.)
		Ka = 17. / 90.;
	else if (d_e > 50)
		Ka = 19. / 90.;
	else if (d_e > 30)
		Ka = 21. / 90.;
	else if (d_e > 20)
		Ka = 23. / 90.;
	else
		Ka = 25. / 90.;

	if (theta_e > 95 || theta_e < -95)
	{
		theta_e += 180;

		if (theta_e > 180)
			theta_e -= 360;
		if (theta_e > 80)
			theta_e = 80;
		if (theta_e < -80)
			theta_e = -80;
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}

	else if (theta_e < 85 && theta_e > -85)
	{
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}

	else
	{
		vr = (+.17 * theta_e);
		vl = (-.17 * theta_e);
	}

	Velocity(robot, vl, vr);
}


void PredictBall(Environment *pEnv)
{
	double dx = pEnv->currentBall.pos.x - pEnv->lastBall.pos.x;
	double dy = pEnv->currentBall.pos.y - pEnv->lastBall.pos.y;
	pEnv->predictedBall.pos.x = pEnv->currentBall.pos.x + dx;
	pEnv->predictedBall.pos.y = pEnv->currentBall.pos.y + dy;
}

void Goalie1(Robot *robot, Environment *pEnv)
{
	double velocityLeft = 0, velocityRight = 0;

	double Tx = pEnv->goalBounds.right - pEnv->currentBall.pos.x;
	double Ty = pEnv->fieldBounds.top - pEnv->currentBall.pos.y;

	double Ax = pEnv->goalBounds.right - robot->pos.x;
	double Ay = pEnv->fieldBounds.top - robot->pos.y;

	if (Ay > Ty + 0.9 && Ay > 27)
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	if (Ay > Ty - 0.9 && Ay < 43)
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if (Ay < 27)
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if (Ay > 43)
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	double Tr = robot->rotation;
	if (Tr < 0.001)
		Tr = Tr + 360;
	if (Tr > 360.001)
		Tr = Tr - 360;
	if (Tr > 270.5)
		velocityRight = velocityRight + fabs(Tr - 270);
	else if (Tr < 269.5)
		velocityLeft = velocityLeft + fabs(Tr - 270);

	robot->velocityLeft = velocityLeft;
	robot->velocityRight = velocityRight;
}

void Attack2(Robot *robot, Environment *pEnv)
{
	Vector3D t = pEnv->currentBall.pos;
	double r = robot->rotation;
	if (r < 0) r += 360;
	if (r > 360) r -= 360;
	double vl = 0, vr = 0;

	if (t.y > pEnv->fieldBounds.top - 2.5) t.y = pEnv->fieldBounds.top - 2.5;
	if (t.y < pEnv->fieldBounds.bottom + 2.5) t.y = pEnv->fieldBounds.bottom + 2.5;
	if (t.x > pEnv->fieldBounds.right - 3) t.x = pEnv->fieldBounds.right - 3;
	if (t.x < pEnv->fieldBounds.left + 3) t.x = pEnv->fieldBounds.left + 3;

	double dx = robot->pos.x - t.x;
	double dy = robot->pos.y - t.y;

	double dxAdjusted = dx;
	double angleToPoint = 0;

	if (fabs(robot->pos.y - t.y) > 7 || t.x > robot->pos.x)
		dxAdjusted -= 5;

	if (dxAdjusted == 0)
	{
		if (dy > 0)
			angleToPoint = 270;
		else
			angleToPoint = 90;
	}
	else if (dy == 0)
	{
		if (dxAdjusted > 0)
			angleToPoint = 360;
		else
			angleToPoint = 180;

	}
	else
		angleToPoint = atan(fabs(dy / dx)) * 180.0 / PI;

	if (dxAdjusted > 0)
	{
		if (dy > 0)
			angleToPoint -= 180;
		else if (dy < 0)
			angleToPoint = 180 - angleToPoint;
	}
	if (dxAdjusted < 0)
	{
		if (dy > 0)
			angleToPoint = -angleToPoint;
		else if (dy < 0)
			angleToPoint = 90 - angleToPoint;
	}

	if (angleToPoint < 0) angleToPoint = angleToPoint + 360;
	if (angleToPoint > 360) angleToPoint = angleToPoint - 360;
	if (angleToPoint > 360) angleToPoint = angleToPoint - 360;

	double c = r;

	double angleDiff = fabs(r - angleToPoint);

	if (angleDiff < 40)
	{
		vl = 100;
		vr = 100;
		if (c > angleToPoint)
			vl -= 10;
		if (c < angleToPoint)
			vr -= 10;
	}
	else
	{
		if (r > angleToPoint)
		{
			if (angleDiff > 180)
				vl += 360 - angleDiff;
			else
				vr += angleDiff;
		}
		if (r < angleToPoint)
		{
			if (angleDiff > 180)
				vr += 360 - angleDiff;
			else
				vl += angleDiff;
		}
	}

	NearBound2(robot, vl, vr, pEnv);
}

void NearBound2(Robot *robot, double vl, double vr, Environment *pEnv)
{
	Vector3D a = robot->pos;
	double r = robot->rotation;

	if (a.y > pEnv->fieldBounds.top - 15 && r > 45 && r < 130)
	{
		if (vl > 0)
			vl /= 3;
		if (vr > 0)
			vr /= 3;
	}

	if (a.y < pEnv->fieldBounds.bottom + 15 && r < -45 && r > -130)
	{
		if (vl > 0) vl /= 3;
		if (vr > 0) vr /= 3;
	}

	if (a.x > pEnv->fieldBounds.right - 10)
	{
		if (vl > 0)
			vl /= 2;
		if (vr > 0)
			vr /= 2;
	}

	if (a.x < pEnv->fieldBounds.left + 10)
	{
		if (vl > 0)
			vl /= 2;
		if (vr > 0)
			vr /= 2;
	}

	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Defend(Robot *robot, Environment *pEnv, double low, double high)
{
	double vl = 0, vr = 0;
	Vector3D z = pEnv->currentBall.pos;

	double Tx = pEnv->goalBounds.right - z.x;
	double Ty = pEnv->fieldBounds.top - z.y;
	Vector3D a = robot->pos;
	a.x = pEnv->goalBounds.right - a.x;
	a.y = pEnv->fieldBounds.top - a.y;

	if (a.y > Ty + 0.9 && a.y > low)
	{
		vl = -100;
		vr = -100;
	}
	if (a.y < Ty - 0.9 && a.y < high)
	{
		vl = 100;
		vr = 100;
	}
	if (a.y < low)
	{
		vl = 100;
		vr = 100;
	}
	if (a.y > high)
	{
		vl = -100;
		vr = -100;
	}

	double Tr = robot->rotation;

	if (Tr < 0.001)
		Tr += 360;
	if (Tr > 360.001)
		Tr -= 360;
	if (Tr > 270.5)
		vr += fabs(Tr - 270);
	else if (Tr < 269.5)
		vl += fabs(Tr - 270);

	NearBound2(robot, vl, vr, pEnv);
}