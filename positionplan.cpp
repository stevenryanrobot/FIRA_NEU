#include "stdafx.h"
#include "soccerplayer.h"

void Soccer::Pos(int id[], int size) {
	
	rcsc::Vector2D ballPos = rcsc::Vector2D(plt->getBall().pos + plt->getBall().vel*0.2);
	if (ballPos.x > 100) ballPos.x = 100;
	if (ballPos.x < -80) ballPos.x = -80;
	switch (size)
	{
	case 1:
	{
		double dist0 = plt->getBall().pos.dist(plt->ourRobot(id[0]).pos);
		if (dist0 < 40)
			spin(id[0], Field::oppGoal(), 30);
		if (ballPos.y < -Field::height / 4)
			ToPoint(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else if (ballPos.y > Field::height / 4)
			ToPoint(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else
			if (plt->ourRobot(id[0]).pos.y > 0)
				ToPoint(id[0], rcsc::Vector2D(ballPos.x, 60), rcsc::Vector2D(1000, 0));
			else
				ToPoint(id[0], rcsc::Vector2D(ballPos.x, -60), rcsc::Vector2D(1000, 0));

		break;
	}
	case 2:
	{
		double dist0 = plt->getBall().pos.dist(plt->ourRobot(id[0]).pos);
		double dist1 = plt->getBall().pos.dist(plt->ourRobot(id[1]).pos);
		if (dist1 < 40)
			spin(id[1], Field::oppGoal(), 30);
		if (dist0 < 40)
			spin(id[0], Field::oppGoal(), 30);
		if (plt->getBall().pos.x < -50) {
			// matching
			int lower = -1, upper = -1;
			if (plt->ourRobot(id[0]).pos.y > 0) {
				upper = id[0];
				lower = id[1];
			}
			else {
				upper = id[1];
				lower = id[0];
			}

			if (plt->getBall().pos.y > 0) {
				ToPoint(upper, rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 25), rcsc::Vector2D(1000, 0));
				ToPoint(lower, rcsc::Vector2D(60, 0), rcsc::Vector2D(0, 1000));
			}
			else {
				ToPoint(lower, rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 25), rcsc::Vector2D(1000, 0));
				ToPoint(upper, rcsc::Vector2D(60, 0), rcsc::Vector2D(0, 1000));
			}
		}
		else if (ballPos.y < -Field::height / 4) {
			ToPoint(id[0], rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 25), rcsc::Vector2D(1000, 0));
			ToPoint(id[1], rcsc::Vector2D(73, 0), rcsc::Vector2D(1000, 0));
		}
		else if (ballPos.y > Field::height / 4) {
			ToPoint(id[0], rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 25), rcsc::Vector2D(1000, 0));
			ToPoint(id[1], rcsc::Vector2D(73, 0), rcsc::Vector2D(1000, 0));
		}
		else {
			// matching
			int lower = -1, upper = -1;
			if (plt->ourRobot(id[0]).pos.y > 0) {
				upper = id[0];
				lower = id[1];
			}
			else {
				upper = id[1];
				lower = id[0];
			}
			ToPoint(upper, rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2 + 10), rcsc::Vector2D(1000, 0));
			ToPoint(lower, rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2 - 10), rcsc::Vector2D(1000, 0));
		}
		break;
	}
	default:
		break;
	}
}
