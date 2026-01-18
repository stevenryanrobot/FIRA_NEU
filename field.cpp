#include "stdafx.h"
#include "field.h"

/**需要调参**/
const double Field::height = 180;
const double Field::width = 220;
const double Field::goalDepth = 40;
const double Field::goalWidth = 15;
const double Field::penaltyAheight = 50;
const double Field::penaltyAwidth = 15;
const double Field::penaltyBheight = 80;
const double Field::penaltyBwidth = 35;
const double Field::penaltyPoint = 37.5;
const double Field::penaltyCheight = 120;
const double Field::penaltyCwidth = 80;
const double Field::FBHeightOffSet = 30;
const double Field::FBHWidthOffSet = 55;
const double Field::markerFBOffSet = 25;
const double Field::centerCircleRadius = 25;
const double Field::cornerTriangleSide = 7;
const double Field::pushingWidth = 8;
bool Field::OurGoalinterexist(rcsc::Segment2D balltrack)
{
	if (balltrack.origin().getX() > 193 && abs(balltrack.origin().getY() - 90) < 40)
	{
		return true;
	}rcsc::Vector2D RT(2000, 130), RB(2000, 50), LT(193, 130), LB(193, 50);
	rcsc::Segment2D L1(LT, RT), L2(RT,RB),L3(RB,LB),L4(LB,LT);
	if (L1.existIntersection(balltrack)  || L3.existIntersection(balltrack) || L4.existIntersection(balltrack))
		return true;
	else return false;
 }
rcsc::Vector2D Field::OurGoalinter(rcsc::Segment2D balltrack)
{
	int count = 0, line[2];
	rcsc::Vector2D RT(2000, 130), RB(2000, 50), LT(193, 130), LB(193, 50), offset_top(0, 2), offset_bottom(0, -2), offset_left(-2, 0), intersection[2];
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	rcsc::Line2D l1(LT, RT), l2(RT, RB), l3(RB, LB), l4(LB, LT);

	if (balltrack.origin().getX() > 193 && abs(balltrack.origin().getY() - 90) <40)return L4.projection(balltrack.origin())+offset_left;
	
	intersection[1] = RT;
	if (L4.existIntersection(balltrack))
	{
		intersection[count] = L4.intersection(balltrack, 1);
		line[count] = 1;
		count++;
	}
	if (L1.existIntersection(balltrack))
	{
		intersection[count] = L1.intersection(balltrack, 1);
		line[count] = 2;
		count++;
	}
	if (L3.existIntersection(balltrack))
	{
		intersection[count] = L3.intersection(balltrack, 1);
		line[count] = 3;
		count++;
	}
	if (balltrack.origin().dist(intersection[0]) > balltrack.origin().dist(intersection[1]))
	{
		line[0] = line[1];
	}
	if (line[0] == 2) return l1.projection(balltrack.terminal()) + offset_left;
	if (line[0] == 1) return l4.projection(balltrack.terminal()) + offset_top;
	if (line[0] == 3) return l3.projection(balltrack.terminal()) + offset_bottom;
	else return balltrack.terminal();
 }
bool Field::OurPenaltyinterexist(rcsc::Segment2D balltrack)
{
	if (balltrack.origin().getX() > 183 && abs(balltrack.origin().getY() - 90) < 40)return true;
	rcsc::Vector2D LT(183, 130), LB(183, 50), RT(220, 130), RB(220, 50);
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	if (L1.existIntersection(balltrack) || L3.existIntersection(balltrack) || L4.existIntersection(balltrack))
		return true;
	else return false;
}

rcsc::Vector2D Field::OurPenaltyinter(rcsc::Segment2D balltrack)
{
	int count = 0, line[2];
	rcsc::Vector2D LT(183, 130), LB(183, 50), RT(2000, 130), RB(2000, 50), offset_top(0, 2), offset_bottom(0, -2), offset_left(-2, 0), intersection[2];
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	rcsc::Line2D l1(LT, RT), l2(RT, RB), l3(RB, LB), l4(LB, LT);
	if (balltrack.origin().getX() > 183 && abs(balltrack.origin().getY() - 90) < 40)return L4.projection(balltrack.origin())+offset_left;
	intersection[1] = RT;
	if (L4.existIntersection(balltrack))
	{
		intersection[count] = L4.intersection(balltrack, 1);
		line[count] = 1;
		count++;
	}
	if (L1.existIntersection(balltrack))
	{
		intersection[count] = L1.intersection(balltrack, 1);
		line[count] = 2;
		count++;
	}
	if (L3.existIntersection(balltrack))
	{
		intersection[count] = L3.intersection(balltrack, 1);
		line[count] = 3;
		count++;
	}
	if (balltrack.origin().dist(intersection[0]) > balltrack.origin().dist(intersection[1]))
	{
		line[0] = line[1];
	}
	if (line[0] == 2) return l1.projection(balltrack.terminal()) + offset_left;
	if (line[0] == 1) return l4.projection(balltrack.terminal()) + offset_top;
	if (line[0] == 3) return l3.projection(balltrack.terminal()) + offset_bottom;
	else return balltrack.terminal();
}


bool Field::OppPenaltyinterexist(rcsc::Segment2D balltrack)
{
	if (balltrack.origin().getX() < 37 && abs(balltrack.origin().getY() - 90) < 40)return true;
	rcsc::Vector2D LT(-1000, 130), LB(-1000, 50), RT(37, 130), RB(37, 50);
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	if (L1.existIntersection(balltrack) || L3.existIntersection(balltrack) || L2.existIntersection(balltrack))
		return true;
	else return false;
}

rcsc::Vector2D Field::OppPenaltyinter(rcsc::Segment2D balltrack)
{
	int count = 0, line[2];
	rcsc::Vector2D LT(-1000, 130), LB(-1000, 50), RT(37, 130), RB(37, 50), offset_top(0, 2), offset_bottom(0, -2), offset_right(2, 0), intersection[2];
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	rcsc::Line2D l1(LT, RT), l2(RT, RB), l3(RB, LB), l4(LB, LT);
	if (balltrack.origin().getX() < 37 && abs(balltrack.origin().getY() - 90) < 40)return L2.projection(balltrack.origin())+offset_right;
	intersection[1] = LT;
	if (L1.existIntersection(balltrack))
	{
		intersection[count] = L1.intersection(balltrack, 1);
		line[count] = 1;
		count++;
	}
	if (L2.existIntersection(balltrack))
	{
		intersection[count] = L2.intersection(balltrack, 1);
		line[count] = 2;
		count++;
	}
	if (L3.existIntersection(balltrack))
	{
		intersection[count] = L3.intersection(balltrack, 1);
		line[count] = 3;
		count++;
	}
	if (balltrack.origin().dist(intersection[0]) > balltrack.origin().dist(intersection[1]))
	{
		line[0] = line[1];
	}
	if (line[0] == 2) return l2.projection(balltrack.terminal()) + offset_right;
	if (line[0] == 1) return l1.projection(balltrack.terminal()) + offset_top;
	if (line[0] == 3) return l3.projection(balltrack.terminal()) + offset_bottom;
	else return balltrack.terminal();
}

bool Field::OppGoalinterexist(rcsc::Segment2D balltrack)
{
	if (balltrack.origin().getX() < 25 && abs(balltrack.origin().getY() - 90) < 40)return true;
	rcsc::Vector2D RT(25, 120), RB(25, 60), LT(-1000, 120), LB(-1000, 60);
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	if (L1.existIntersection(balltrack) || L3.existIntersection(balltrack) || L2.existIntersection(balltrack))
		return true;
	else return false;
}
rcsc::Vector2D Field::OppGoalinter(rcsc::Segment2D balltrack)
{
	int count = 0, line[2];
	rcsc::Vector2D RT(25, 120), RB(25, 60), LT(-1000, 120), LB(-1000, 60), offset_top(0, 2), offset_bottom(0, -2), offset_right(2, 0), intersection[2];
	rcsc::Segment2D L1(LT, RT), L2(RT, RB), L3(RB, LB), L4(LB, LT);
	rcsc::Line2D l1(LT, RT), l2(RT, RB), l3(RB, LB), l4(LB, LT);
	if (balltrack.origin().getX() < 25 && abs(balltrack.origin().getY() - 90) < 40)return L2.projection(balltrack.origin())+offset_right;
	intersection[1] = LT;
	if (L1.existIntersection(balltrack))
	{
		intersection[count] = L1.intersection(balltrack, 1);
		line[count] = 1;
		count++;
	}
	if (L2.existIntersection(balltrack))
	{
		intersection[count] = L2.intersection(balltrack, 1);
		line[count] = 2;
		count++;
	}
	if (L3.existIntersection(balltrack))
	{
		intersection[count] = L3.intersection(balltrack, 1);
		line[count] = 3;
		count++;
	}
	if (balltrack.origin().dist(intersection[0]) > balltrack.origin().dist(intersection[1]))
	{
		line[0] = line[1];
	}
	if (line[0] == 2) return l2.projection(balltrack.terminal()) + offset_right;
	if (line[0] == 1) return l1.projection(balltrack.terminal()) + offset_top;
	if (line[0] == 3) return l3.projection(balltrack.terminal()) + offset_bottom;
	else return balltrack.terminal();
}

bool Field::InFobidenBound(rcsc::Vector2D pos)//球在边界重灾区
{
	double topy = 170,bottomy=10,leftx=10,rightx=210;
	if (pos.getX() > rightx || pos.getY() < bottomy || pos.getX() < leftx || pos.getY() > topy||pos.getX()+pos.getY()<19|| pos.getX() + pos.getY()>381||pos.getY()-pos.getX()<-201||pos.getY() - pos.getX()>161)return true;
	else return false;
}

bool Field::Boundintersctionexist(rcsc::Segment2D L)
{
	return( L.existIntersection(Field::LTforball())|| L.existIntersection(Field::Topforball()) || L.existIntersection(Field::RTforball()) || L.existIntersection(Field::Rightforball())|| L.existIntersection(Field::RBforball()) || L.existIntersection(Field::Bottomforball()) || L.existIntersection(Field::LBforball()) || L.existIntersection(Field::Leftforball()));
 }
  rcsc::Vector2D  Field::Boundintersction(rcsc::Segment2D L)
{
	  
	  if (L.existIntersection(LTforball()))
	  {
		  return L.intersection(L_LTforball());
		}
	  else if (L.existIntersection(Topforball()))
	  {
		  return L.intersection(L_Topforball());
	  }
	  else if (L.existIntersection(RTforball()))
	  {
		  return L.intersection(L_RTforball());
	  }
	  else if (L.existIntersection(Rightforball()))
	  {
		  return L.intersection(L_Rightforball());
	  }
	  else if (L.existIntersection(RBforball()))
	  {
		  return L.intersection(L_RBforball());
	  }
	  else if (L.existIntersection(Bottomforball()))
	  {
		  return L.intersection(L_Bottomforball());
	  }
	  else if (L.existIntersection(LBforball()))
	  {
		  return L.intersection(L_LBforball());
	  }
	  else if (L.existIntersection(Leftforball()))
	  {
		  return L.intersection(L_Leftforball());
	  }
}
Field::Field()
{
}

Field::~Field()
{
}
