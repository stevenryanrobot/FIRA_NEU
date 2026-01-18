#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"

bool Soccer::crash(int id1,bool who1,int id2,bool who2)
{
	rcsc::Vector2D pos1, pos2, vel1, vel2;
	if(who1)
	{
		pos1 = plt->ourRobot(id1).pos;
		vel1 = plt->ourRobot(id1).vel;
	}
	else
	{
		pos1 = plt->oppRobot(id1).pos;
		vel1 = plt->oppRobot(id1).vel;
	}
	if (who2)
	{
		pos2 = plt->ourRobot(id2).pos;
		vel2 = plt->ourRobot(id2).vel;
	}
	else
	{
		pos2 = plt->oppRobot(id2).pos;
		vel2 = plt->oppRobot(id2).vel;
	}
	for (int i = 0; i <= 60; i++)
	{
		if ((pos1 + vel1 * i/3).dist(pos2 + vel2 * i/3) <= 12)return true;
	}
	return false;
}
rcsc::Vector2D Soccer::avoidcrash(int id,rcsc::Vector2D target)
{
	rcsc::Vector2D pos = plt->ourRobot(id).pos,our,opp,evade_target=target;
	rcsc::Vector2D ourveldiff, oppveldiff,evade_our,evade_opp,ourvel;
	int ourcrash,oppcrash;
	rcsc::AngleDeg standard(100),e_theta;
	ourcrash=getourclosestplayer(id);
	oppcrash = getoppclosestplayer(id);
	our = plt->ourRobot(ourcrash).pos;
	opp = plt->oppRobot(oppcrash).pos;
	evade_our = our - pos;
	evade_opp = opp - pos;
	//logg.test1 << "crash id" << id << std::endl;
	//logg.test1 << "our crash " << ourcrash << std::endl;
	if (oppcrash == 0&&crash(id,true,oppcrash,false)&&pos.dist(plt->oppRobot(0).pos)<20&&player_in_area3(0,false))
	{
		if (pos.getY() > opp.getY())
		{
			evade_target = pos + evade_opp.rotate(100).setLength(20);
		}
		else
		evade_target = pos + evade_opp.rotate(-100).setLength(20);
		//logg.test1 << "crash opp" << crash(id, true, ourcrash, true) << std::endl;
		return evade_target;
	}
	if (plt->ourRobot(ourcrash).pos.dist(pos) > plt->ourRobot(0).pos.dist(pos) && crash(id, true, 0, true))
	{
		if (pos.getY() > plt->ourRobot(0).pos.getY())
		{
			evade_target = pos + evade_our.rotate(-100).setLength(20);
		}
		else
			evade_target = pos + evade_our.rotate(100).setLength(20);
		//logg.test1 << "crash 0" << crash(id, true, ourcrash, true) << std::endl;
		return evade_target;
	}
	else if(ourcrash!=10&&crash(id,true,ourcrash,true))
	{
		if (playerstatus[id] > playerstatus[ourcrash])
		{
			
			ourvel = plt->ourRobot(ourcrash).vel;
			e_theta =ourvel.dir() - (target - pos).dir();
			if(e_theta.degree()>=0)
			standard = -standard;
			evade_target = pos + evade_our.rotate(standard).setLength(20);
			//logg.test1 << "crash our" << crash(id, true, ourcrash, true) << std::endl;
			return evade_target;
		}
	}
	//logg.test1 << "crash" << crash(id, true, ourcrash, true) << std::endl;

	return target;
}