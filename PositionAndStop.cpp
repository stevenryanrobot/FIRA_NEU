
#include "stdafx.h"
#include "pid.h"
#include "soccerplayer.h"

void Soccer::PositionAndStop(int  id, rcsc::Vector2D pos, rcsc::AngleDeg bestangle,double vdown,bool PorN)//vdown一般1.8稳定停止
{
	int k = 1;
	double vupline = 4.65;
	double vmax = 125;
	double anglespeedmax = 0;
	double Limitedangle = 3;
	rcsc::Vector2D o(0, 0), target;
	double  distance;
	rcsc::AngleDeg turnangle, posangle, vangle;
	double v;				//临时保存速度的大小!!!
	double f = vmax;				//加速度变量
	double s = 0;					//预测的减速位移(路程)
	int n = 0;					//跑位的步数
	bool face = true;			//判断小车是否是正面前进
	v = plt->ourRobot(id).vel.dist(o);
	target = pos - plt->ourRobot(id).pos;
	distance = pos.dist(plt->ourRobot(id).pos);
	posangle = target.dir();
	turnangle = posangle - plt->ourRobot(id).th;
	vangle = posangle - plt->ourRobot(id).vel.dir();

	if (turnangle.degree() > 90)
	{//判断小车是否是正面前进
		face = false;
		turnangle.normalize_again();
	}
	else if (turnangle.degree() < -90)
	{
		face = false;
		turnangle.normalize_again();
	}
	else
	{
		face = true;
	}

	if (vangle.degree() < -90 || vangle.degree() > 90)		//同时判断v的正负
		v = -v;
	if (rcsc::AngleDeg::normalize_angle(((plt->ourRobot(id).vel.dir() - posangle).degree()) > 90)&&abs(v)>0.3)
	{
		robots[id].velocityLeft = 0;
			robots[id].velocityRight = 0;

			return;
	}
	
	if (distance >= 3+1.2*abs(v))///
	{
		if (abs(turnangle.degree()) > 30)
		{
			if (abs(v) < 4)
			{
				robots[id].velocityRight = 2 * (face - 0.5) * 125 + turnangle.degree() / 2 * 2.5;
				robots[id].velocityLeft = 2 * (face - 0.5) * 125 - turnangle.degree() / 2 * 2.5;
			}
			else
			{
				robots[id].velocityRight = 2 * (face - 0.5) * 125 + turnangle.degree() / 2 ;
				robots[id].velocityLeft = 2 * (face - 0.5) * 125 - turnangle.degree() / 2;
			}
		}

		 else if (abs(turnangle.degree()) > 5)
		{
			robots[id].velocityRight = 2 * (face - 0.5) * 125+turnangle.degree() / 2;
			robots[id].velocityLeft = 2 * (face - 0.5) * 125 -turnangle.degree() / 2 ;
		}
		else
		{
			robots[id].velocityLeft = 125 * 2 * (face - 0.5);
			robots[id].velocityRight = 125 * 2 * (face - 0.5);
		}
	}
	else if (distance > 2.5)
	{
		if (abs(v) > vdown)
		{
			robots[id].velocityLeft = 0;
			robots[id].velocityRight = 0;

		}
		else
		{
			if (abs(turnangle.degree()) > 30)
			{

				robots[id].velocityRight = 2 * (face - 0.5) * 80 + turnangle.degree() / 2 * 2.5;
				robots[id].velocityLeft = 2 * (face - 0.5) * 80 - turnangle.degree() / 2 * 2.5;
			}

			else if (abs(turnangle.degree()) > 5)
			{
				robots[id].velocityRight = 2 * (face - 0.5) * 110 + turnangle.degree() / 1;
				robots[id].velocityLeft = 2 * (face - 0.5) * 110 - turnangle.degree() / 1;
			}
			else
			{ 
			robots[id].velocityLeft = 110 * 2 * (face - 0.5);
			robots[id].velocityRight = 110 * 2 * (face - 0.5);
			}
		}
	}
	else if (distance < 2.5)
	{


		//if (turnangle.degree() >= 12)
		//{
		//	Angle_n(id, target.dir());
		//}
		 if (0.3 < v)
		{

			robots[id].velocityLeft = 0;
			robots[id].velocityRight = 0;
		}
		 else 
		 {
			 if(PorN)
			 Angle_n(id, bestangle);
		 }

	}


}
