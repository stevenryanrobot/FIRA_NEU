#ifndef _SENSOR_HEADER_
#define _SENSOR_HEADER_

#include "base.h"
#include "geometric.h"
#include "Platform.h"
#include "pid.h"

void getRobotWheel(double w, double vel_tan, double& right_wheel, double& left_wheel);
void getRobotWheelPID(const PltRobot& rbt, double w, double vel_tan, double& right_wheel, double& left_wheel);

#endif _SENSOR_HEADER_