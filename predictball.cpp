
#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"

rcsc::Vector2D Soccer::posnormalize(int id,int status,rcsc::Vector2D target)
{
	rcsc::Vector2D posnow=plt->ourRobot(id).pos;
	rcsc::Vector2D no_target=target;
	if (Field::InFobidenBound(plt->getBall().pos)&&status!=1)
	{
		if (target.getY() > 165)
			no_target.y = 165;
		else if (target.getY() < 15)
		{
			no_target.y = 15;
		}
		if (target.getX() > 205)
		{
			no_target.x = 205;
		}
		else if (target.getX() < 15)
		{
			no_target.x = 15;
		}

		
	}
	rcsc::Segment2D balltrack(posnow, no_target);
	if (Field::OurGoalinterexist(balltrack))
	{
		no_target=Field::OurGoalinter(balltrack);
		logg.test1 << "1" << std::endl;
		return no_target;
		
	}
	if (Field::OppGoalinterexist(balltrack)&&status!=1)
	{
		no_target = Field::OppGoalinter(balltrack);
		logg.test1 << "2" << std::endl;
		return no_target;
		
	}
	if (status == 1||status==2)return no_target;
	if (Field::OurPenaltyinterexist(balltrack)&&status>2)
	{
		no_target = Field::OurPenaltyinter(balltrack);
		logg.test1 << "3" << std::endl;
		return no_target;
	}
	if (status > 3 && Field::OppPenaltyinterexist(balltrack))
	{
		no_target = Field::OppPenaltyinter(balltrack);
		logg.test1 << "4" << std::endl;
		return no_target;
	}
	return no_target;

}

rcsc::Segment2D Bound(rcsc::Segment2D v)
{
	rcsc::Vector2D s, e;
	rcsc::Vector2D velocity = v.terminal() - v.origin();
	if (v.existIntersection(Field::Topforball()))
	{
		s = v.intersection(Field::Topforball(),1);
		e = Field::L_Topforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s,e);
		return v_new;
	}
	else if (v.existIntersection(Field::RTforball()))
	{
		s = v.intersection(Field::RTforball(), 1);
		e = Field::L_RTforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::Rightforball()))
	{
		s = v.intersection(Field::Rightforball(), 1);
		e = Field::L_Rightforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::LTforball()))
	{
		s = v.intersection(Field::LTforball(), 1);
		e = Field::L_LTforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::RBforball()))
	{
		s = v.intersection(Field::RBforball(), 1);
		e = Field::L_RBforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::Bottomforball()))
	{
		s = v.intersection(Field::Bottomforball(), 1);
		e = Field::L_Bottomforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::LBforball()))
	{
		s = v.intersection(Field::LBforball(), 1);
		e = Field::L_LBforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else if (v.existIntersection(Field::Leftforball()))
	{
		s = v.intersection(Field::Leftforball(), 1);
		e = Field::L_Leftforball().Symmetry(v.terminal());
		rcsc::Segment2D v_new(s, e);
		return v_new;
	}
	else
	{
		return v;
	}
}
rcsc::Vector2D Soccer::predictball(int t)
{
	rcsc::Vector2D velocity = plt->getBall().vel,pos=plt->getBall().pos;

	for(int i=0;i<t;i++)
	{
		rcsc::Segment2D v(pos, pos + velocity);
		
		if (Field::Boundintersctionexist(v))
		{
			pos = Bound(v).terminal();
			velocity = (Bound(v).terminal() - Bound(v).origin()) / (Bound(v).terminal() - Bound(v).origin()).length() * velocity.length();
			velocity *= 0.45;

		}
		else
		
		{
			pos += velocity;
			continue;
		}

	}
	

	return pos;
}



int Soccer::getoppclosest(rcsc::Vector2D pos)
{
	double dist = 100000;
	int id = 0;
	for (int i = 0; i <= 4; i++)
	{
		if (dist >= plt->oppRobot(i).pos.dist(pos))
		{
			dist = plt->oppRobot(i).pos.dist(pos);
			id = i;
		}
	}
	return id;
}

int Soccer::getourclosest(rcsc::Vector2D pos)
{
	double dist = 100000;
	int id = 0;
	for (int i = 1; i <= 4; i++)
	{
		if (dist >= plt->ourRobot(i).pos.dist(pos))
		{
			dist = plt->ourRobot(i).pos.dist(pos);
			id = i;
		}
	}
	return id;
}

int Soccer::getourclosestplayer(int id)
{
	rcsc::Vector2D pos = plt->ourRobot(id).pos;
	double dist = 100000;
	int idour=10;
	for (int i = 1; i <= 4; i++)
	{
		if (dist >= plt->ourRobot(i).pos.dist(pos)&&id!=i)
		{
			dist = plt->ourRobot(i).pos.dist(pos);
			idour = i;
		}
	}
	return idour;
}
int Soccer::getoppclosestplayer(int id)
{
	rcsc::Vector2D pos = plt->ourRobot(id).pos;
	double dist = 100000;
	int idour=10;
	for (int i = 0; i <= 4; i++)
	{
		if (dist >= plt->oppRobot(i).pos.dist(pos) && id != i)
		{
			dist = plt->oppRobot(i).pos.dist(pos);
			idour = i;
		}
	}
	return idour;
}
rcsc::Vector2D Soccer::MaptoPoint(int id, rcsc::Vector2D start, rcsc::Vector2D end)
{
	int startx,starty,endx,endy;
	startx = (start.getX()-2)/4+5;
	starty = (start.getY()-2)/4+1;
	endx = (end.getX()-2)/4+5;
	endy =( end.getY()-2)/4+1;//´ýÐÞÕý
	A::CPoint* star =new A::CPoint(startx, starty);
	A:: CPoint* en = new A::CPoint(endx, endy);
	A::CPoint* point=players[id].FindPath(star,en,0);
	logg.test1 << "test1" << std::endl;
	if (point == NULL)
	{
		return end;

	}
	else
	{
		while (point != NULL&&(point->X!=startx||point->Y!=starty))
		{
			logg.test1 << point->X << std::endl;
			logg.test1 << point->Y << std::endl;
			point = point->m_parentPoint;
			logg.test1 << "test2" << std::endl;
			logg.test1 << point->X << std::endl;
			logg.test1 << point->Y << std::endl;
		}
	}
	rcsc::Vector2D target(point->X, point->Y);
	return target;
}

void Soccer::setMap(int id,int status)
{
	rcsc::Vector2D ball = plt->getBall().pos;
	rcsc::Vector2D opp[5],our[5];
	for (int i = 0; i <= 4; i++)
	{
		opp[i] = plt->oppRobot(id).pos;
		if (i == id)our[i] = rcsc::Vector2D(-8, 8);
		else our[i] = plt->ourRobot(id).pos;
	}
	int ouriy, ourix, oppix, oppiy,ballx,bally;
	if (status == 0 || status == 1)
	{
		;
	}
	else
	{
		players[id].SetmapC();
	}
	ballx = (ball.getX() - 2) / 4 + 5;
	bally = (ball.getY() - 2) / 4+1;
	players->m_array[ballx][bally] = 1;
	players->m_array[ballx+1][bally] = 1;
	players->m_array[ballx][bally+1] = 1;
	players->m_array[ballx][bally-1] = 1;
	players->m_array[ballx-1][bally] = 1;
	for (int i = 0; i <= 4; i++)
	{

		ourix = (our[i].getX() - 2) / 4 + 5;
		ouriy = (our[i].getY() - 2) / 4+1;
		oppix= (opp[i].getX() - 2) / 4 + 5;
		oppiy = (opp[i].getY() - 2) / 4+1;
		for (int j = -1; j <= 1; j++)
		{
			for (int q = -1; q <= 1; q++)
			{
				players[id].m_array[oppix + j][oppiy + q] = 1;
				players[id].m_array[ourix + j][ouriy + q] = 1;
			}
		}
	}


}