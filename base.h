#ifndef _BASE_HEADER_
#define _BASE_HEADER_

#include <math.h>
//1
const long PLAYERS_PER_SIDE = 5;
const double PI = 3.1415926535;
/**需要调参**/
const double ROBOT_HALF_WIDTH = 3.75;
const double ROBOT_WIDTH = 7.5;
const double vel_max = 4.65; // cm / cycle
const double dec_max = 0.4; // cm / cycle^2
const double acc_max = 0.2; // cm / cycle^2
const double max_w = 53; // deg / cycle
const double M=794.36;//agent质量kg
const double I=20.54;//agent转动惯量B=(L*F+L^2*w*PI/360)/I
const double u=25.81;//速度阻尼系数a=(F*2-u*V*2)/M
const double L=4.156;//agent边长和轮子可能是到中心的距离
const double hitdistance = 7.3;//球速度为0时接触距离
const double dribbledistance = 9;//带球时的距离
typedef struct
{
	double x, y, z;
} Vector3D;

typedef struct
{
	long left, right, top, bottom;
} Bounds;                              

typedef struct
{
	Vector3D pos;
	double rotation;
	double velocityLeft, velocityRight;
} Robot;

typedef struct
{
	Vector3D pos;
	double rotation;
} OpponentRobot;                      

typedef struct
{
	Vector3D pos;
} Ball;

typedef struct
{
	Robot home[PLAYERS_PER_SIDE];
	OpponentRobot opponent[PLAYERS_PER_SIDE];
	Ball currentBall, lastBall, predictedBall;
	Bounds fieldBounds, goalBounds;
	long gameState;
	long whosBall;
	void *userData;
} Environment;

enum PlayMode {
	PM_PlayOn = 0,           //  
	PM_FreeBall_LeftTop,     //   1
	PM_FreeBall_LeftBot,     //   2
	PM_FreeBall_RightTop,    //   3
	PM_FreeBall_RightBot,    //   4
	PM_PlaceKick_Yellow,     //   5
	PM_PlaceKick_Blue,       //   6
	PM_PenaltyKick_Yellow,   //   7
	PM_PenaltyKick_Blue,     //   8
	PM_FreeKick_Yellow,      //   9
	PM_FreeKick_Blue,        //   10
	PM_GoalKick_Yellow,      //   11
	PM_GoalKick_Blue         //   12
};

#endif _BASE_HEADER