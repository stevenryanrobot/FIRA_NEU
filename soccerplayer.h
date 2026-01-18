#include "stdafx.h"
#include <string.h>
#include <fstream>
#include "logger.h"
#include "base.h"
#include "pid.h"
#include "geometric.h"
#include "Platform.h"
#include "sensor.h"
#include "A.h"
#include "sector_2d.h"
// y值最大的点为P1，顺时针编号依次增加
class Cube
{
private:
	rcsc::Vector2D P1,P2, P3, P4,position;
	double length;

	rcsc::AngleDeg theta;
public:
	rcsc::Vector2D wheelleft, wheelright;
	Cube():P1(0,0),P2(0,0),P3(0,0),P4(0,0),position(0,0),length(0),theta(0),wheelright (0,0),wheelleft(0,0){}
	Cube(rcsc::Vector2D pos, rcsc::AngleDeg th,double len):length(len),P1(pos.getX(),pos.getY()), P2(pos.getX(), pos.getY()), P3(pos.getX(), pos.getY()), P4(pos.getX(), pos.getY()),wheelleft(0,0),wheelright(0,0)
	{
		rcsc::Vector2D corner(len / 2, len / 2);
		rcsc::AngleDeg nighty(90);
		P1 = pos + corner.rotate(th);
		P2 = pos + corner.rotate(nighty);
		P3 = pos + corner.rotate(nighty);
		P4 = pos + corner.rotate(nighty);
		position = pos;
		theta = th;
		wheelleft = P1 / 2 + P2 / 2;
		wheelright = P3 / 2 + P4 / 2;
	}
	void update(rcsc::Vector2D pos, rcsc::AngleDeg th,double len)
	{
		length = len;
		rcsc::Vector2D P5=pos;
		rcsc::Vector2D corner(length / 2, length / 2);
		rcsc::AngleDeg nighty(90);
		P1 = pos + corner.rotate(th);
		P2 = pos + corner.rotate(nighty);
		P3 = pos + corner.rotate(nighty);
		P4 = pos + corner.rotate(nighty);
		wheelleft = P1 / 2 + P2 / 2;
		wheelright = P3 / 2 + P4 / 2;
		position = pos;
		theta = th;
		if (P1.getY() > P5.getY())P5 = P1;
		if (P2.getY() > P5.getY())P5 = P2;
		if (P3.getY() > P5.getY())P5 = P3;
		if (P4.getY() > P5.getY())P5 = P4;
		corner = P5 - pos;
		P1 = P5;
		P2 = pos + corner.rotate(nighty);
		P3 = pos + corner.rotate(nighty);
		P4 = pos + corner.rotate(nighty);
	}
	double distl(rcsc::Vector2D pos)
	{
		rcsc::Line2D Line1(position, theta);
		return  Line1.dist(pos);
	}
	double dist2(rcsc::Vector2D pos)
	{
		rcsc::Line2D Line1(position, theta+90);
		return  Line1.dist(pos);
	}
	bool kickable(rcsc::Vector2D now,rcsc::Vector2D next,double v)
	{
		if (v >= 5) return false;
		rcsc::Line2D Line1(position, theta), Line2(position, theta + 90);
		double dist11,dist12,dist21,dist22;
		dist11 = Line1.dist(now);
		dist12 = Line2.dist(now);
		dist21 = Line1.dist(next);
		dist22 = Line2.dist(next);
		bool nowkick = (dist11 <= 3.85&&dist12<=6.7+v*0.953)|| (dist12 <= 3.85 && dist11 <= 6.7 + v * 0.953);
		bool nextkick= (dist21 <= 3.85 && dist22 <= 6.7 + v * 0.953)|| (dist22 <= 3.85 && dist21 <= 6.7 + v * 0.953);
		return nowkick || nextkick;
	}
	bool kickable_target(rcsc::Vector2D pos, rcsc::Vector2D ball)
	{
		if (position.getX() < pos.getX() && position.getY() < pos.getY() && 2 != getedge(ball))return true;
		else if (position.getX() < pos.getX() && position.getY() > pos.getY() && 1 != getedge(ball))return true;
		else if (position.getX() > pos.getX() && position.getY() > pos.getY() && 4 != getedge(ball))return true;
		else if (position.getX() > pos.getX() && position.getY() < pos.getY() && 3 != getedge(ball))return true;
		else return false;
	}
	bool dribbleable(rcsc::Vector2D pos)
	{
		rcsc::Line2D Line1(position, theta);
		return Line1.dist(pos)<=3.65;
	}
	double getxdist(rcsc::Vector2D ball)
	{
		rcsc::Line2D  Line2(position, theta + 90);
		return Line2.dist(ball);
	}
	int getedge(rcsc::Vector2D pos)//计算球所在智能体的方向
	{
		double dist= P1.dist(pos)+P2.dist(pos);
		int edge = 1;
		if (P2.dist(pos)+P3.dist(pos) < dist)
		{
			dist = P2.dist(pos) + P3.dist(pos);
			edge = 2;
		}
		if (P3.dist(pos) + P4.dist(pos) < dist)
		{
			dist = P3.dist(pos) + P4.dist(pos);
			edge = 3;
		}
		if (P4.dist(pos) + P1.dist(pos) < dist)
		{
			dist = P4.dist(pos) + P1.dist(pos);
			edge = 4;
		}
		return edge;
	}
};




class Soccer
{
public:
	Soccer();
	//~Soccer();
	void init(const char* _teamName, int teamcolor);//定义队名
	void updatePlt(Environment* _env);// 更新速度和位姿
	void updateGM(const PlayMode& pm);//更新模式
	void initRobot(Robot* robot) { robots = robot; }
	void setFormerRobots(Robot* robots);
	void setLaterRobots(Robot* robots, const Robot* oppRobots, const Vector3D& _ball);
	void setBall(Vector3D* ball);
	void run(Robot* _robots);
	void ToPoint(int id, const rcsc::Vector2D& targetPos, const rcsc::Vector2D& targetVel, double Kp = 0.2);
	//holy_diver
	void Angle_n(int id, rcsc::AngleDeg desiredangle);//wrote by donqianli (球员号，目标角度（90°以内）)
	void PositionAndStop(int  id, rcsc::Vector2D pos, rcsc::AngleDeg bestangle,double vdown,bool PorN);//wrote by donqianli （球员号，目标位置，到达后角度，最大减速区半径）
	void heading_position(int id, rcsc::Vector2D target, double v);//快速跑位函数，没有停止
	void dribble(int id, rcsc::Vector2D target, double v);//运球，待调
	void kick_holy_diver(int id,rcsc::Vector2D pos);//踢球
	void Goalie_holy_diver_care(int id);
	void shoot_holy_diver(int id);
	void setRobotVel(int id, double v_tan, double w);
	void setRobotAng(int id, double th);
	double getRobotW(int id, double th);
	void logdown();
	PID velPID[5];
	PID angPID[5];
	logger logg;
	int		teamColor;
	//决策部分
	void Run_holy_diver(Robot* _robots);
	void playon_holy_diver();
	rcsc::Vector2D predictball(int t);
	double test,testraw,vle,vri;
	void Goalie_holy_diver(int id);
	rcsc::Vector2D MaptoPoint(int id ,rcsc::Vector2D start ,rcsc::Vector2D end);
	void setMap(int id,int status);
private:
	Cube ourcubes[5], oppcubes[5];
	const char* teamName;
	Platform* plt;
	Environment* env;
	Robot* robots;
	A::CAStar players[5];
	//PID *posPID;
	//PID *angPID;
	/**Plays**/
	void playon();
	bool ballInOurSide;
	int playonCounter;
	bool playonFlag;
	
	/**Plans**/
	void Defense(int ids[], int size);
	void Pos(int ids[], int size);

	/**Characters**/
	void Goalie(int id);
	void PlayMake(int id);

	/**ControlSkill**/


	/**ToPoint**/


	/**Spin**/
	void spin(int id, const rcsc::Vector2D& targetPos, const double &targetVel);
	/**Kick**/
	void kick(int id, const rcsc::Vector2D& targetPos);
	double pm_threshold;
	int last_pm;//上一个主攻队员


	/**holy_diver**/
	bool specialsituation1();//防止犯规，在对方禁区
	bool specialsituation2();//在我方禁区
	bool player_in_area1(int id, bool our);
	bool player_in_area2(int id, bool our);
	bool player_in_area3(int id, bool our);
	bool player_in_area4(int id, bool our);
	bool ball_in_area2();
	bool ball_in_area1();
	int playerstatus[5];//球员地位，越低越重要
	int lastmain;
	double cost_rainbow(int id);
	void catch_the_rainbow();
	void man_on_the_silver_mountain();//暴力进攻
	double cost_man_on_the_silver_mountain(int id);
	rcsc::Vector2D avoidcrash(int id,rcsc::Vector2D target);//紧急避障
	bool crash(int id1,bool who1, int id2,bool who2);//判断会不会碰撞，who为是否己方队员
	rcsc::Vector2D posnormalize(int id,int status ,rcsc::Vector2D target);
	double Takeballcost1(int id,rcsc::Vector2D ball);//边界评价
	int getourclosest(rcsc::Vector2D pos);//我方离某点最近
	int getoppclosest(rcsc::Vector2D pos);
	int getourclosestplayer(int id); //离我方队员最近的我方队员
	int getoppclosestplayer(int id);//离我方队员最近的敌方球员
	double Takeballcost(int id,bool our);//稳定截球的cost
	double Takeballfast(int id,bool our);//快速截球的cost
	void defense_holy_diver();//防守策略
	void attack_holy_diver(int id);//进攻策略
	void shell_holy_diver(int id);//壳式防守
	void shell_holy_diver_Bound(int id);//边界防守策略
	rcsc::Vector2D gettarget_Bound();
};
