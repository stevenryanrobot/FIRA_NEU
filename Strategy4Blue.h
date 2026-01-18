// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRATEGY4BLUE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY4BLUE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef STRATEGY4BLUE_EXPORTS
#define STRATEGY4BLUE_API __declspec(dllexport)
#else
#define STRATEGY4BLUE_API __declspec(dllimport)
#endif

#include "soccerplayer.h"
#include "base.h"


// #############################################################################################
STRATEGY4BLUE_API void SetFormerRobots(PlayMode gameState, Robot robots[]);
STRATEGY4BLUE_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], Vector3D ball, Robot laterRobots[]);
STRATEGY4BLUE_API void SetBall(PlayMode gameState, Vector3D * pBall); 
STRATEGY4BLUE_API void RunStrategy(Environment *pEnv);
STRATEGY4BLUE_API void SetBlueTeamName(char* teamName);

// #############################################################################################
void PredictBall(Environment *pEnv);
void Goalie1(Robot *robot, Environment *pEnv);
void NearBound2(Robot *robot, double vl, double vr, Environment *pEnv);
void Attack2(Robot *robot, Environment *pEnv);
void Defend(Robot *robot, Environment *pEnv, double low, double high);
void MoonAttack(Robot *robot, Environment *pEnv);
void MoonFollowOpponent(Robot *robot, OpponentRobot *opponent);
void Velocity(Robot *robot, double vl, double vr);
void Angle(Robot *robot, double desired_angle);
void Position(Robot *robot, double x, double y);
void Position(Environment * pEnv, int id, double x, double y);
void Goalie(Environment* pEnv);
void LeftWing(Environment* pEnv, int id);
void RightWing(Environment* pEnv, int id);
void CenterDefender(Environment* pEnv, int id);
void CenterAttacker(Environment* pEnv, int id);



// #############################################################################################