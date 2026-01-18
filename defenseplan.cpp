#include "stdafx.h"
#include "soccerplayer.h"
//·ÀÊØ¾ö²ß
void Soccer::Defense(int id[], int size) {
	
	const rcsc::Vector2D& bp = rcsc::Vector2D(plt->getBall().pos + plt->getBall().vel*0.5);
	const double def_w = -Field::width / 2 + Field::penaltyAwidth + 15;
	double y = bp.y;
	switch (size)
	{
	case 1:
		if (y < -Field::penaltyAheight + 5) y = -Field::penaltyAheight / 2 + 2;
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;

		if (plt->getBall().pos.dist(Field::ourGoal()) > 40 && plt->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 10)
			ToPoint(id[0], rcsc::Vector2D(def_w, y*0.6), rcsc::Vector2D(0, 1000));
		else {
			if (plt->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 10) {
				ToPoint(id[0], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
			}
			if (plt->getBall().pos.y > 0) {
				ToPoint(id[0], rcsc::Vector2D(bp.x - 10, Field::penaltyAheight/2 + 25), rcsc::Vector2D(1000, 0));
			}
			else {
				ToPoint(id[0], rcsc::Vector2D(bp.x - 10, -Field::penaltyAheight/2 - 25), rcsc::Vector2D(1000, 0));
			}
		}

		if (Field::ourPenaltyARect().contains(plt->ourRobot(id[0]).pos)) {
			ToPoint(0, rcsc::Vector2D(0, 0), rcsc::Vector2D(0, 1000));
		}

		if (plt->getBall().pos.dist(plt->ourRobot(id[0]).pos) < 8.5) {
			double spinnSpid = 30;
			if(Soccer::teamColor == 0)
				spinnSpid *= -1;
			if (plt->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}

		break;
	case 2:
		if (y < -Field::penaltyAheight + 5) y = -Field::penaltyAheight / 2 + 2;
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;

		if (plt->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50)
			ToPoint(id[0], rcsc::Vector2D(def_w, y + 5), rcsc::Vector2D(0, 1000));
		else {
			if (plt->getBall().pos.y > 0) {
				ToPoint(id[0], rcsc::Vector2D(bp.x - 10, Field::penaltyAheight / 2 + 15), rcsc::Vector2D(1000, 0));
			}
			else {
				ToPoint(id[0], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
			}
		}
		if (plt->getBall().pos.dist(plt->ourRobot(id[0]).pos) < 8.5 && plt->getBall().pos.x > -Field::width/2 + Field::penaltyAwidth + 5) {
			double spinnSpid = 30;
			if(Soccer::teamColor == 0)
			spinnSpid *= -1;
			if (plt->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}

		if (plt->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50)
			ToPoint(id[1], rcsc::Vector2D(def_w, y - 5), rcsc::Vector2D(0, 1000));
		else {
			if (plt->getBall().pos.y > 0) {
				ToPoint(id[1], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
			}
			else {
				ToPoint(id[1], rcsc::Vector2D(bp.x - 10, -Field::penaltyAheight / 2 - 15), rcsc::Vector2D(1000, 0));
			}
		}

		if (plt->getBall().pos.dist(plt->ourRobot(id[0]).pos) < 8.5 && plt->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 5) {
			double spinnSpid = 30;
			if(Soccer::teamColor == 0)
			spinnSpid *= -1;
			if (plt->getBall().pos.y > 0) setRobotVel(id[0], 0, spinnSpid);
			else setRobotVel(id[0], 0, -spinnSpid);
		}
		break;
	case 3:
		if (bp.x < def_w + 20) {
			ToPoint(id[0], rcsc::Vector2D(bp.x, -Field::penaltyBheight/2), rcsc::Vector2D(1000, 0)); //Left
			ToPoint(id[1], rcsc::Vector2D(def_w, bp.y), rcsc::Vector2D(0, 1000)); // Center
			ToPoint(id[2], rcsc::Vector2D(bp.x, Field::penaltyBheight/2), rcsc::Vector2D(1000, 0)); // Right
		}
		else {
			ToPoint(id[0], rcsc::Vector2D(def_w, bp.y - 20), rcsc::Vector2D(0, 1000));
			ToPoint(id[1], rcsc::Vector2D(def_w, bp.y), rcsc::Vector2D(0, 1000));
			ToPoint(id[2], rcsc::Vector2D(def_w, bp.y + 20), rcsc::Vector2D(0, 1000));

		}
		
		break;
	default:
		break;
	}
}
