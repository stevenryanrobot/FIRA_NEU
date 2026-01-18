#ifndef _PLATFORM_HEADER_
#define _PLATFORM_HEADER_

#include "geometric.h"
#include "base.h"
#include "field.h"

struct PltMovingObject
{
	rcsc::Vector2D pos, vel, acc;
};

struct PltRobot : public PltMovingObject
{
	unsigned int id;
	double w, th,B;
};

class GameMode
{
public:
	static const int PlayOn            = 0,
	FreeBall_LeftTop  = 1,
	FreeBall_LeftBot  = 2,
	FreeBall_RightTop = 3,
	FreeBall_RightBot = 4,
	OurKickOff        = 5,
	OppKickOff        = 6,
	OurPenaltyKick    = 7,
	OppPenaltyKick    = 8,
	OurFreeKick       = 9,
	OppFreeKick       = 10,
	OurGoalKick       = 11,
	OppGoalKick       = 12;
};
class TColor
{
public:
	TColor();
	~TColor();
	static const int Yellow = 0;
	static const int Blue = 1;
};

class Platform{
public:
	Platform();
	~Platform();

	int gm;
	int teamColor;

	const PltMovingObject& getBall() const {return ball;}
	const PltRobot& ourRobot(const unsigned int & _id) const{return our[_id];}
	const PltRobot& oppRobot(const unsigned int & _id) const{return opp[_id];} 
	const PltRobot* ourRobots() const {return our;}
	const PltRobot* oppRobots() const {return opp;}
	void increaseLoop() {loop++;}
	unsigned long long getLoop() const{return loop;}
	void update(const Environment* _env);
private:
	PltMovingObject ball, lastBall;
	PltRobot our[PLAYERS_PER_SIDE];
	PltRobot opp[PLAYERS_PER_SIDE];
	PltRobot lastOur[PLAYERS_PER_SIDE];
	PltRobot lastOpp[PLAYERS_PER_SIDE];
	unsigned long long loop;
};
#endif