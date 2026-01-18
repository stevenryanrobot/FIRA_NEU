#include "stdafx.h"
#include "soccerplayer.h"

void Soccer::Goalie(int id) {
	rcsc::Vector2D ballPos = rcsc::Vector2D(plt->getBall().pos + plt->getBall().vel*5);
	rcsc::Line2D ballPath = rcsc::Line2D(plt->getBall().pos, plt->getBall().pos + plt->getBall().vel.normalizedVector()*1000);
	rcsc::Line2D goalLine = rcsc::Line2D(Field::ourGoalB(), Field::ourGoalT());
	rcsc::Vector2D p;
	p = ballPath.intersection(goalLine);
	if (plt->getBall().vel.length() < 0.5) p.invalidate();
	else if (ballPos.x < -100 && ballPos.y > Field::goalWidth/2) p.invalidate();
	else if (ballPos.x < -100 && ballPos.y < -Field::goalWidth / 2) p.invalidate();
	else if (ballPos.x > 45) p.invalidate();
	double y;
	bool forward = false;
	if (Field::ourPenaltyBRect().contains(ballPos) && plt->getBall().vel.length() < 1.5)
		forward = true;
	p.invalidate();
	if (p.isValid()) {
		y = p.y;
	}
	else {
		y = plt->getBall().pos.y + plt->getBall().vel.y*1;
	}


	if (y < -Field::goalWidth / 2 + 5) y = -Field::goalWidth / 2 + 2;
	if (y > Field::goalWidth / 2 - 5) y = Field::goalWidth / 2 - 2;

	rcsc::Vector2D targetVel = rcsc::Vector2D(0, 1000);
	rcsc::Vector2D targetPos = rcsc::Vector2D(-Field::width / 2 + 2, y);
	if (plt->ourRobot(id).pos.x > -Field::width / 2 + 5) targetPos = Field::ourGoal();
	
	if (!forward) {
		ToPoint(id, targetPos, targetVel, 0.3);
	} else {
		kick(id, Field::oppGoal());
	}

	// SPIN
	if (plt->getBall().pos.dist(plt->ourRobot(id).pos) < 8.5 && plt->getBall().vel.length() < 2) {
		spin(id, plt->getBall().pos, 30);
	}

}