#include "stdafx.h"
#include "soccerplayer.h"
#include "pid.h"

void Soccer::kick(int id, const rcsc::Vector2D&  targetPos) {

	rcsc::Vector2D ballPos = rcsc::Vector2D(plt->getBall().pos + plt->getBall().vel*(15. / 5.));
	rcsc::Vector2D robotPos = rcsc::Vector2D(plt->ourRobot(id).pos + plt->ourRobot(id).vel*(5. / 5.));
	rcsc::Vector2D norm = rcsc::Vector2D(ballPos - targetPos);
	norm = norm.normalize();
	rcsc::Vector2D prependicular = rcsc::Vector2D(norm.rotatedVector(90));
	rcsc::Vector2D behindPos = rcsc::Vector2D(ballPos + norm * 20);
	rcsc::Vector2D avoidPos = rcsc::Vector2D(ballPos + prependicular * 20);
	rcsc::Circle2D robotArea = rcsc::Circle2D(robotPos, ROBOT_HALF_WIDTH * sqrt(double(2)));
	rcsc::Vector2D sol1, sol2;

	rcsc::Ray2D temp = rcsc::Ray2D(ballPos, targetPos);
	if (robotArea.intersection(temp, &sol1, &sol2) > 0)
	{
		if (avoidPos.x < -Field::width / 2 + ROBOT_WIDTH || avoidPos.x > Field::width / 2 + ROBOT_WIDTH || avoidPos.y < -Field::height / 2 + ROBOT_WIDTH || avoidPos.x > Field::height / 2 + ROBOT_WIDTH)
			avoidPos = ballPos;
		ToPoint(id, avoidPos, behindPos, 0.3);
	}
	else if (plt->ourRobot(id).pos.dist(behindPos) > 25)
	{
		if (avoidPos.x < -Field::width / 2 + ROBOT_WIDTH || avoidPos.x > Field::width / 2 + ROBOT_WIDTH || avoidPos.y < -Field::height / 2 + ROBOT_WIDTH || avoidPos.x > Field::height / 2 + ROBOT_WIDTH)
			behindPos = ballPos;
		ToPoint(id, behindPos, targetPos, 0.3);
	}
	else {
		ToPoint(id, ballPos, targetPos, 0.3);
	}
	if (Field::oppPenaltyARect().contains(plt->getBall().pos) && plt->ourRobot(id).pos.dist(plt->getBall().pos) < 10) {

		spin(id, Field::oppGoal(), 50);

	}
}


void Soccer::kick_holy_diver(int id, rcsc::Vector2D pos)
{
	
	rcsc::Vector2D ball=plt->getBall().pos;
	rcsc::Segment2D balltrack(ball, ball + plt->getBall().vel*50);
	rcsc::AngleDeg e_theta ,ballvelocity,robotdir(plt->ourRobot(id).th);
	ballvelocity = plt->getBall().vel.dir();
	int edge=ourcubes[id].getedge(ball),k=1;
	double th4 = robotdir.normalize_again().abs(),th2,th3,th1;
	th3 = (robotdir -90).degree();
	th2= (robotdir - 180).degree();
	th1 = (robotdir - 270).degree();
	e_theta = ballvelocity - (pos - ball).dir();
	bool eth = e_theta.abs() > 15, baltr = balltrack.dist(pos) > 5;
	if (plt->getBall().vel.length() < 0.2)
	{
		eth = true;
		baltr = true;
	}
	if (ourcubes[id].kickable(ball, ball + plt->getBall().vel, plt->ourRobot(id).vel.length()) && (eth && baltr))
	{
		if (ourcubes[id].wheelleft.dist(ball) > ourcubes[id].wheelright.dist(ball))k = -1;
		//logg.test1 <<" kickK:  " << k << std::endl;
		//logg.test1 << " distleft:  " << ourcubes[id].wheelleft.dist(ball) << std::endl;
		//logg.test1 << " distright:  " << ourcubes[id].wheelright.dist(ball) << std::endl;
		
		if(edge==1)
		{
			e_theta = -ballvelocity + (pos - ball).dir();
			robots[id].velocityRight = e_theta.degree() * 9 * (0.5 - k / 2);
			robots[id].velocityLeft = -e_theta.degree() * 9*(0.5+k/2);
			//logg.test1 << " theta1:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta1:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta1:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta1:  " << e_theta.degree() << std::endl;
		}
		else if (edge == 2)
		{
			e_theta = -ballvelocity + (pos - ball).dir();
			robots[id].velocityRight = e_theta.degree() * 9 * (0.5 - k / 2);
			robots[id].velocityLeft = -e_theta.degree() * 9 * (0.5 + k / 2);
			//logg.test1 << " theta2:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta2:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta2:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta2:  " << e_theta.degree() << std::endl;
		}
		else if (edge == 3)
		{
			e_theta = -ballvelocity + (pos - ball).dir();
			robots[id].velocityRight = e_theta.degree() * 9 * (0.5 - k / 2);
			robots[id].velocityLeft =- e_theta.degree() * 9 * (0.5 + k / 2);
			//logg.test1 << " theta3:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta3:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta3:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta3:  " << e_theta.degree() << std::endl;
		}
		else if (edge == 4)
		{
			e_theta = -ballvelocity + (pos - ball).dir();
			robots[id].velocityRight = e_theta.degree() * 9 * (0.5 - k / 2);
			robots[id].velocityLeft = -e_theta.degree() * 9 * (0.5 + k / 2);
			//logg.test1 << " theta4:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta4:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta4:  " << e_theta.degree() << std::endl;
			//logg.test1 << " theta4:  " << e_theta.degree() << std::endl;
		}
	}
	else
	{
		robots[id].velocityRight = e_theta.degree() * 0;
		robots[id].velocityLeft = -e_theta.degree() * 0;
	}
	//logg.test1 << "thetaofkick:  " << e_theta.degree() << std::endl;
}

void Soccer::shoot_holy_diver(int id)
{
	rcsc::Vector2D ball = plt->getBall().pos;
	rcsc::Vector2D velball = plt->getBall().vel;
	rcsc::Vector2D p(0, 7);
	rcsc::AngleDeg B = (Field::oppGoalB() + ball).dir();
	rcsc::AngleDeg T = (Field::oppGoalT() - ball).dir();
	rcsc::AngleDeg O = ((plt->oppRobot(getoppclosest(Field::oppGoal())).pos)-ball).dir();
	if (ourcubes[id].kickable(ball, ball + velball, plt->ourRobot(id).vel.length()))
	{
		if ((B - O).abs() > (T - O).abs())
		{
			kick_holy_diver(id, Field::oppGoalB() + p);
		}
		else
		{
			kick_holy_diver(id, Field::oppGoalB() - p);
		}
	}
}