#include "stdafx.h"
#include "Platform.h"


Platform::Platform()
{
	loop = 0;
	gm = GameMode::PlayOn;
#ifdef YELLOW
	teamColor = TColor::Yellow;
#else
	teamColor = TColor::Blue;
#endif
}
Platform::~Platform(){}

void Platform::update(const Environment* _env)
{
	int i;
	for (i = 0; i < PLAYERS_PER_SIDE; i++)
	{
		our[i].pos.x=_env->home[i].pos.x;
		our[i].pos.y = _env->home[i].pos.y;
		our[i].vel = our[i].pos - lastOur[i].pos;
		our[i].th = _env->home[i].rotation;
		our[i].w = our[i].th - lastOur[i].th;
		
		if (our[i].w >= 180)our[i].w -= 360;
		if (our[i].w <= -180)our[i].w += 360;
		our[i].B = our[i].w - lastOur[i].w;
		our[i].id = i;
		our[i].acc = our[i].vel - lastOur[i].vel;
		lastOur[i].pos = our[i].pos;
		lastOur[i].vel = our[i].vel;
		lastOur[i].th = our[i].th;
		lastOur[i].w = our[i].w;
		lastOur[i].id = i;
		lastOur[i].acc = our[i].acc;

		opp[i].pos.x = _env->opponent[i].pos.x;
		opp[i].pos.y = _env->opponent[i].pos.y;
		opp[i].vel = opp[i].pos - opp[i].pos;
		opp[i].th = _env->opponent[i].rotation;
		opp[i].w = opp[i].th - lastOpp[i].th;
		opp[i].id = i;
		opp[i].acc = opp[i].vel - lastOpp[i].vel;
		lastOpp[i].pos = opp[i].pos;
		lastOpp[i].vel = opp[i].vel;
		lastOpp[i].th = opp[i].th;
		lastOpp[i].w = opp[i].w;
		lastOpp[i].id = i;
		lastOpp[i].acc = opp[i].acc;
	}
	lastBall = ball;
	
	ball.pos.x = _env->currentBall.pos.x;
	ball.pos.y = _env->currentBall.pos.y;
	ball.vel.x =_env->currentBall.pos.x - lastBall.pos.getX();
	ball.vel.y= _env->currentBall.pos.y - lastBall.pos.getY();
	ball.acc = ball.vel - lastBall.vel;
	loop += 1;
}