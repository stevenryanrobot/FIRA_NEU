
#include "stdafx.h"
#include "soccerplayer.h"
#include <string>
#include <iostream>

void Soccer::logdown()
{
	rcsc::Vector2D zer(0, 0);
	logg.Blue0 << "loop: "<<plt->getLoop() << std::endl;
	logg.Blue0 << "x: " << plt->ourRobot(0).pos.getX() << "  y: " << plt->ourRobot(0).pos.getY() <<"  rotation: " <<plt->ourRobot(0).th<<std::endl;
	logg.Blue0 << "vel: "<<plt->ourRobot(0).vel.getX() << "," << plt->ourRobot(0).vel.getY() << "    abs: " << plt->ourRobot(0).vel.dist(zer) << std::endl;
	logg.Blue0 << "acc: " << plt->ourRobot(0).acc.dist(zer)<<"  x: " << plt->ourRobot(0).acc.getX() << "  y: " << plt->ourRobot(0).acc.getY() << std::endl;
	logg.Blue0 << " W: " << plt->ourRobot(0).w << std::endl;
	logg.Blue1 << "loop: " << plt->getLoop() << std::endl;
	logg.Blue1 << "x: " << plt->ourRobot(1).pos.getX() << "  y: " << plt->ourRobot(1).pos.getY() << "  rotation: " << plt->ourRobot(1).th << std::endl;
	logg.Blue1 << "vel: " << plt->ourRobot(1).vel.getX() << "," << plt->ourRobot(1).vel.getY() << "    abs: " << plt->ourRobot(1).vel.dist(zer) << std::endl;
	logg.Blue1 << "acc: " << plt->ourRobot(1).acc.dist(zer) << "  x: " << plt->ourRobot(1).acc.getX() << "  y: " << plt->ourRobot(1).acc.getY() << std::endl;
	logg.Blue1 << " W: " << plt->ourRobot(1).w << std::endl;
	logg.Blue2 << "loop: " << plt->getLoop() << std::endl;
	logg.Blue2 << "x: " << plt->ourRobot(2).pos.getX() << "  y: " << plt->ourRobot(2).pos.getY() << "  rotation: " << plt->ourRobot(2).th << std::endl;
	logg.Blue2 << "vel: " << plt->ourRobot(2).vel.getX() << "," << plt->ourRobot(2).vel.getY() << "    abs: " << plt->ourRobot(2).vel.dist(zer) << std::endl;
	logg.Blue2 << "acc: " << plt->ourRobot(2).acc.dist(zer) << "  x: " << plt->ourRobot(2).acc.getX() << "  y: " << plt->ourRobot(2).acc.getY() << std::endl;
	logg.Blue2 << " W: " << plt->ourRobot(2).w << std::endl;
	logg.Blue3 << "loop: " << plt->getLoop() << std::endl;
	logg.Blue3 << "x: " << plt->ourRobot(3).pos.getX() << "  y: " << plt->ourRobot(3).pos.getY() << "  rotation: " << plt->ourRobot(3).th << std::endl;
	logg.Blue3 << "vel: " << plt->ourRobot(3).vel.getX() << "," << plt->ourRobot(3).vel.getY() << "    abs: " << plt->ourRobot(3).vel.dist(zer) << std::endl;
	logg.Blue3 << "acc: " << plt->ourRobot(3).acc.dist(zer) << "  x: " << plt->ourRobot(3).acc.getX() << "  y: " << plt->ourRobot(3).acc.getY() << std::endl;
	logg.Blue3 << " W: " << plt->ourRobot(3).w << std::endl;
	logg.Blue4 << "loop: " << plt->getLoop() << std::endl;
	logg.Blue4 << "x: " << plt->ourRobot(4).pos.getX() << "  y: " << plt->ourRobot(4).pos.getY() << "  rotation: " << plt->ourRobot(4).th << std::endl;
	logg.Blue4 << "vel: " << plt->ourRobot(4).vel.getX() << "," << plt->ourRobot(4).vel.getY() << "    abs: " << plt->ourRobot(4).vel.dist(zer) << std::endl;
	logg.Blue4 << "acc: " << plt->ourRobot(4).acc.dist(zer) << "  x: " << plt->ourRobot(4).acc.getX() << "  y: " << plt->ourRobot(4).acc.getY() << std::endl;
	logg.Blue4 << " W: " << plt->ourRobot(4).w << std::endl;
	logg.Yellow0 << "loop: " << plt->getLoop() << std::endl;
	logg.Yellow0 << "x: " << plt->oppRobot(0).pos.getX() << "  y: " << plt->oppRobot(0).pos.getY() << "  rotation: " << plt->oppRobot(0).th << std::endl;
	logg.Yellow0 << "vel: " << plt->oppRobot(0).vel.getX() << "," << plt->oppRobot(0).vel.getY() << "    abs: " << plt->oppRobot(0).vel.dist(zer) << std::endl;
	logg.Yellow0 << "acc: " << plt->oppRobot(0).acc.dist(zer) << "  x: " << plt->oppRobot(0).acc.getX() << "  y: " << plt->oppRobot(0).acc.getY() << std::endl;
	logg.Yellow0 << " W: " << plt->oppRobot(0).w << std::endl;
	logg.Yellow1 << "loop: " << plt->getLoop() << std::endl;
	logg.Yellow1 << "x: " << plt->oppRobot(1).pos.getX() << "  y: " << plt->oppRobot(1).pos.getY() << "  rotation: " << plt->oppRobot(1).th << std::endl;
	logg.Yellow1 << "vel: " << plt->oppRobot(1).vel.getX() << "," << plt->oppRobot(1).vel.getY() << "    abs: " << plt->oppRobot(1).vel.dist(zer) << std::endl;
	logg.Yellow1 << "acc: " << plt->oppRobot(1).acc.dist(zer) << "  x: " << plt->oppRobot(1).acc.getX() << "  y: " << plt->oppRobot(1).acc.getY() << std::endl;
	logg.Yellow1 << " W: " << plt->oppRobot(1).w << std::endl;
	logg.Yellow2 << "loop: " << plt->getLoop() << std::endl;
	logg.Yellow2 << "x: " << plt->oppRobot(2).pos.getX() << "  y: " << plt->oppRobot(2).pos.getY() << "  rotation: " << plt->oppRobot(2).th << std::endl;
	logg.Yellow2 << "vel: " << plt->oppRobot(2).vel.getX() << "," << plt->oppRobot(2).vel.getY() << "    abs: " << plt->oppRobot(2).vel.dist(zer) << std::endl;
	logg.Yellow2 << "acc: " << plt->oppRobot(2).acc.dist(zer) << "  x: " << plt->oppRobot(2).acc.getX() << "  y: " << plt->oppRobot(2).acc.getY() << std::endl;
	logg.Yellow2 << " W: " << plt->oppRobot(2).w << std::endl;
	logg.Yellow3 << "loop: " << plt->getLoop() << std::endl;
	logg.Yellow3 << "x: " << plt->oppRobot(3).pos.getX() << "  y: " << plt->oppRobot(3).pos.getY() << "  rotation: " << plt->oppRobot(3).th << std::endl;
	logg.Yellow3 << "vel: " << plt->oppRobot(3).vel.getX() << "," << plt->oppRobot(3).vel.getY() << "    abs: " << plt->oppRobot(3).vel.dist(zer) << std::endl;
	logg.Yellow3 << "acc: " << plt->oppRobot(3).acc.dist(zer) << "  x: " << plt->oppRobot(3).acc.getX() << "  y: " << plt->oppRobot(3).acc.getY() << std::endl;
	logg.Yellow3 << " W: " << plt->oppRobot(3).w << std::endl;
	logg.Yellow4 << "loop: " << plt->getLoop() << std::endl;
	logg.Yellow4 << "x: " << plt->oppRobot(4).pos.getX() << "  y: " << plt->oppRobot(4).pos.getY() << "  rotation: " << plt->oppRobot(4).th << std::endl;
	logg.Yellow4 << "vel: " << plt->oppRobot(4).vel.getX() << "," << plt->oppRobot(4).vel.getY() << "    abs: " << plt->oppRobot(4).vel.dist(zer) << std::endl;
	logg.Yellow4 << "acc: " << plt->oppRobot(4).acc.dist(zer) << "  x: " << plt->oppRobot(4).acc.getX() << "  y: " << plt->oppRobot(4).acc.getY() << std::endl;
	logg.Yellow4 << " W: " << plt->oppRobot(4).w << std::endl;
	logg.Ball << "loop:" << plt->getLoop() << std::endl;
	logg.Ball << "acc: " << plt->getBall().acc.dist(zer) <<"  x,y "<< plt->getBall().acc.getX()<<","<<plt->getBall().acc.getY()<< std::endl;
	logg.Ball << "vel: " << plt->getBall().vel.dist(zer) << "  x,y " << plt->getBall().vel.getX() << "," << plt->getBall().vel.getY() << std::endl;
	logg.Ball << "pos: " << plt->getBall().pos.getX() << "," << plt->getBall().pos.getY() << std::endl;

	logg.test1 <<"X:"<< test<<std::endl;
	logg.test1 << "Y:" << testraw << std::endl;
	logg.test2 << "X:"<<vle<<std::endl;
	logg.test2 << "Y:" << vri << std::endl;
}
