#include "stdafx.h"
#include <iostream>

#include "soccerplayer.h"

Soccer::Soccer()
{
	playerstatus[0] = 0;
	playerstatus[1] = 1;
	playerstatus[2] = 2;
	playerstatus[3] = 3;
	playerstatus[4] = 4;
	env = NULL;
	plt = new Platform();
}
void Soccer::init(const char* _teamName, int _teamColor)
{
	teamName  = _teamName;
	teamColor = _teamColor;//blue = 1; yellow = 0;
	
}

#define IFYELLOW(A,B) ((plt->teamColor == TColor::Yellow) ? (A) : (B))
void Soccer::updateGM(const PlayMode& pm)
{
	switch(pm)
	{
	case PM_PlayOn:
		plt->gm = GameMode::PlayOn; break;
	case PM_FreeBall_LeftTop:
		plt->gm = GameMode::FreeBall_LeftTop; break;
	case PM_FreeBall_LeftBot:
		plt->gm = GameMode::FreeBall_LeftBot; break;
	case PM_FreeBall_RightTop:
		plt->gm = GameMode::FreeBall_RightTop; break;
	case PM_FreeBall_RightBot:
		plt->gm = GameMode::FreeBall_RightBot; break;
	case PM_PlaceKick_Yellow:
		plt->gm = IFYELLOW(GameMode::OurKickOff, GameMode::OppKickOff); break;
	case PM_PlaceKick_Blue:
		plt->gm = IFYELLOW(GameMode::OppKickOff, GameMode::OurKickOff); break;
	case PM_PenaltyKick_Yellow:
		plt->gm = IFYELLOW(GameMode::OurPenaltyKick, GameMode::OppPenaltyKick); break;
	case PM_PenaltyKick_Blue:
		plt->gm = IFYELLOW(GameMode::OppPenaltyKick, GameMode::OurPenaltyKick); break;
	case PM_FreeKick_Yellow:
		plt->gm = IFYELLOW(GameMode::OurFreeKick, GameMode::OppFreeKick); break;
	case PM_FreeKick_Blue:
		plt->gm = IFYELLOW(GameMode::OppFreeKick, GameMode::OurFreeKick); break;
	case PM_GoalKick_Yellow:
		plt->gm = IFYELLOW(GameMode::OurGoalKick, GameMode::OppGoalKick); break;
	case PM_GoalKick_Blue:
		plt->gm = IFYELLOW(GameMode::OppGoalKick, GameMode::OurGoalKick); break;
	}
}

void Soccer::updatePlt(Environment* _env)
{
	env = _env;
	plt->update(_env);
	for (int i = 0; i < 5; i++)
	{
		ourcubes[i].update(plt->ourRobot(i).pos, plt->ourRobot(i).th, 4.15);
		oppcubes[i].update(plt->oppRobot(i).pos, plt->oppRobot(i).th, 4.15);
		velPID[i].Kp = 1000000;
		velPID[i].Ki = 1;
		velPID[i].maxoutput = 125;
		velPID[i].maxSum = 50;
		velPID[i].minErr = 3;
		angPID[i].Kp = 0.5;
		angPID[i].Ki = 0.1;
		angPID[i].minErr = 1;
		angPID[i].maxSum = 10;
		angPID[i].maxoutput = 30;
		angPID[i].Kd = 5;
	}
	
	angPID[0].Kp = 0.5;
	angPID[0].Ki = 0.15;
	angPID[0].minErr = 2;
	angPID[0].maxSum = 10;
	angPID[0].maxoutput = 50;
	angPID[0].Kd = 3;
	logg.test2<<"distx:"<<ourcubes[3].getxdist(plt->getBall().pos)<<std::endl;
	logg.test2 << "velocity:" << plt->getBall().vel.length() << std::endl;
	
}

void Soccer::setFormerRobots(Robot* robots)
{
	logg.test2 << "set former" << plt->gm << std::endl;
	playonFlag = false;
	playonCounter = 0;
	switch (plt->gm)
	{
		case GameMode::FreeBall_RightTop:
		robots[0].pos.x = 215;
		robots[0].pos.y = 100;
		robots[0].rotation = -90;
		robots[1].pos.x = 195;
		robots[1].pos.y = 150;
		robots[1].rotation = 180;
		robots[2].pos.x = 198;
		robots[2].pos.y = 80;
		robots[2].rotation = 180;
		robots[3].pos.x = 160;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 140;
		robots[4].pos.y = 50;
		robots[4].rotation = 180;
		break;
	case GameMode::FreeBall_RightBot:
		robots[0].pos.x = 215;
		robots[0].pos.y = 80;
		robots[0].rotation = -90;
		robots[1].pos.x = 195;
		robots[1].pos.y = 30;
		robots[1].rotation = 180;
		robots[2].pos.x = 198;
		robots[2].pos.y = 100;
		robots[2].rotation = 180;
		robots[3].pos.x = 160;
		robots[3].pos.y = 100;
		robots[3].rotation = 180;
		robots[4].pos.x = 140;
		robots[4].pos.y = 130;
		robots[4].rotation = 180;
		break;
	case GameMode::OurKickOff:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 135;
		robots[1].pos.y = 90;
		robots[1].rotation = 180;
		robots[2].pos.x = 120;
		robots[2].pos.y = 110;
		robots[2].rotation = 180;
		robots[3].pos.x = 115;
		robots[3].pos.y = 70;
		robots[3].rotation = 180;
		robots[4].pos.x = 160;
		robots[4].pos.y = 90;
		robots[4].rotation = 180;
		break;
	case GameMode::OppPenaltyKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 105;
		robots[1].pos.y = 160;
		robots[1].rotation = 180;
		robots[2].pos.x = 105;
		robots[2].pos.y = 120;
		robots[2].rotation = 180;
		robots[3].pos.x = 105;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 105;
		robots[4].pos.y = 50;
		robots[4].rotation = 180;

		break;
	case GameMode::OppFreeKick:
		// Goalie -> Center Of Goal
		robots[0].pos.x = 220 - 5; robots[0].pos.y = 90; robots[0].rotation = 90;
		// Others
		robots[1].pos.x = 220 - Field::penaltyAwidth - ROBOT_HALF_WIDTH;  robots[1].pos.y = Field::height / 2 + Field::penaltyAheight / 2 - ROBOT_HALF_WIDTH;  robots[1].rotation = 90;
		robots[2].pos.x = 220 - Field::penaltyAwidth - ROBOT_HALF_WIDTH;  robots[2].pos.y = Field::height / 2 + -Field::penaltyAheight / 2 + ROBOT_HALF_WIDTH; robots[2].rotation = 90;
		robots[3].pos.x = 220 - Field::penaltyBwidth + ROBOT_HALF_WIDTH;  robots[3].pos.y = Field::height / 2 + Field::penaltyBheight / 2 + ROBOT_HALF_WIDTH;  robots[3].rotation = 0;
		robots[4].pos.x = Field::penaltyBwidth - ROBOT_HALF_WIDTH;  robots[4].pos.y = Field::height / 2 + -Field::penaltyBheight / 2 - ROBOT_HALF_WIDTH; robots[4].rotation = 0;

		break;
	case GameMode::OurGoalKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 190;
		robots[1].pos.y = 100;
		robots[1].rotation = 180;
		robots[2].pos.x = 170;
		robots[2].pos.y = 65;
		robots[2].rotation = 180;
		robots[3].pos.x = 150;
		robots[3].pos.y = 40;
		robots[3].rotation = 180;
		robots[4].pos.x = 130;
		robots[4].pos.y = 130;
		robots[4].rotation = 180;

		break;

	default: /* For Case That We Don't Put Our Robots First */
		break;
	}
}

void Soccer::setLaterRobots(Robot* robots, const Robot* oppRobots, const Vector3D& _ball)
{
	playonFlag = false;
	logg.test1 << "set later" << plt->gm << std::endl;
	playonCounter = 0;
	switch(plt->gm)
	{
		
		case GameMode::FreeBall_LeftTop:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 165;
		robots[1].pos.y = 100;
		robots[1].rotation = 180;
		robots[2].pos.x = 130;
		robots[2].pos.y = 120;
		robots[2].rotation = 180;
		robots[3].pos.x = 95;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 85;
		robots[4].pos.y = 150;
		robots[4].rotation = 180;
		break;
	case GameMode::FreeBall_LeftBot:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 165;
		robots[1].pos.y = 80;
		robots[1].rotation = 180;
		robots[2].pos.x = 130;
		robots[2].pos.y = 60;
		robots[2].rotation = 180;
		robots[3].pos.x = 95;
		robots[3].pos.y = 100;
		robots[3].rotation = 180;
		robots[4].pos.x = 85;
		robots[4].pos.y = 30;
		robots[4].rotation = 180;
		break;
	case GameMode::OppKickOff:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 190;
		robots[1].pos.y = 90;
		robots[1].rotation = 180;
		robots[2].pos.x = 150;
		robots[2].pos.y = 90;
		robots[2].rotation = 180;
		robots[3].pos.x = 130;
		robots[3].pos.y = 60;
		robots[3].rotation = 180;
		robots[4].pos.x = 130;
		robots[4].pos.y = 120;
		robots[4].rotation = 180;
		break;
	case GameMode::OurPenaltyKick://更改
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 45;//点球人员
		robots[1].pos.y = 105;
		robots[1].rotation = 180;
		robots[2].pos.x = 115;
		robots[2].pos.y = 110;
		robots[2].rotation = 180;
		robots[3].pos.x = 115;
		robots[3].pos.y = 70;
		robots[3].rotation = 180;
		robots[4].pos.x = 180;
		robots[4].pos.y = 91;
		robots[4].rotation = 180;
		break;

		break;
	case GameMode::OurFreeKick:
		robots[0].pos.x = 220 - 5;
		robots[0].pos.y = 90;
		robots[0].rotation = 90;
		robots[1].pos.x = 220 - 30;
		robots[1].pos.y = 80;
		robots[1].rotation = 0;
		robots[2].pos.x = 220 - 50;
		robots[2].pos.y = 180 - 65;
		robots[2].rotation = 0;
		robots[3].pos.x = 220 - 70;
		robots[3].pos.y = 180 - 40;
		robots[3].rotation = 0;
		robots[4].pos.x = 220 - 90;
		robots[4].pos.y = 180 - 130;
		robots[4].rotation = 0;
		break;
	case GameMode::OppGoalKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 140;
		robots[1].pos.y = 50;
		robots[1].rotation = 180;
		robots[2].pos.x = 140;
		robots[2].pos.y = 130;
		robots[2].rotation = 180;
		robots[3].pos.x = 120;
		robots[3].pos.y = 60;
		robots[3].rotation = 180;
		robots[4].pos.x = 120;
		robots[4].pos.y = 90;
		robots[4].rotation = 180;
		break;

	default: /* For Case That We Put Our Robots First */
		break;
	}
}

void Soccer::setBall(Vector3D* ball) {
	if (plt->gm == GameMode::OurGoalKick) 
	{
		if(Soccer::teamColor == 1)
		{
			ball->x = 10;
			ball->y = 70;
		}
		else
		{
			ball->x = 215;
			ball->y = 80;
		}
	}
}

void Soccer::run(Robot* _robots)
{
	robots = _robots;
	updateGM(PM_PlayOn);
	playon();
}
void Soccer::Run_holy_diver(Robot* _robots)
{
	robots = _robots;
	updateGM(PM_PlayOn);
	playon_holy_diver();
}

void Soccer::setRobotVel(int id, double vel_tan, double w)
{
	getRobotWheelPID(plt->ourRobot(id), w, vel_tan, robots[id].velocityRight, robots[id].velocityLeft);
}

void Soccer::setRobotAng(int id, double th)
{
	/*if YELLOW th += 180*/
	/**需要调参**/
	angPID[id].Kp = 0.35;
	angPID[id].Ki = 0;
	angPID[id].Kd = 0.05;
	double diff = plt->ourRobot(id).th-th;
	if (diff > 180)
		diff = -360 + diff;
	if (diff < -180)
		diff = 360 + diff;
	angPID[id].run(diff);
	setRobotVel(id, 0, -angPID[id].lastOut);
}

double Soccer::getRobotW(int id, double th)
{
	angPID[id].Kp = 0.35;
	angPID[id].Ki = 0;
	angPID[id].Kd = 0.05;
	double diff = plt->ourRobot(id).th - th;
	if (diff > 180)
		diff = -360 + diff;
	if (diff < -180)
		diff = 360 + diff;
	angPID[id].run(diff);
	return -1 * angPID[id].lastOut;
}
