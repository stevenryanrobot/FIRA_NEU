#ifndef Log
#define log


#include "stdafx.h"
#include <string.h>
#include <fstream>

class logger
{
public:
	logger():Blue0("C:/Strategy/log/blue0.txt", std::ios::out), Blue1("C:/Strategy/log/blue1.txt", std::ios::out),
		Blue2("C:/Strategy/log/blue2.txt", std::ios::out) , Blue3("C:/Strategy/log/blue3.txt", std::ios::out) ,
		Blue4("C:/Strategy/log/blue4.txt", std::ios::out),Yellow0("C:/Strategy/log/yellow0.txt", std::ios::out),
		Yellow1("C:/Strategy/log/yellow1.txt", std::ios::out), Yellow2("C:/Strategy/log/yellow2.txt", std::ios::out), 
		Yellow3("C:/Strategy/log/yellow3.txt", std::ios::out), Yellow4("C:/Strategy/log/yellow4.txt", std::ios::out),
		Ball("C:/Strategy/log/ball.txt", std::ios::out),test1("C:/Strategy/log/test1.txt", std::ios::out),
		test2("C:/Strategy/log/test2.txt", std::ios::out) {}
	std::ofstream Blue0;
	std::ofstream Blue1;
	std::ofstream Blue2;
	std::ofstream Blue3;
	std::ofstream Blue4;
	std::ofstream Yellow0;
	std::ofstream Yellow1;
	std::ofstream Yellow2;
	std::ofstream Yellow3;
	std::ofstream Yellow4;
	std::ofstream Ball;
	std::ofstream test1;
	std::ofstream test2;
};
#endif // !Log