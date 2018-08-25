#ifndef PATH_FOLLOWER_H
#define PATH_FOLLOWER_H

#include "PID.h"
#include "Path.h"


int pathIndex;//keeps track of what point we are approaching
int pathPoints;
double deltaX;
double deltaY;
double theta;
double rDist; //right wheel distance travel
double lDist; //left wheel distance travel
double distNextPoint;
double distLastPoint;
PID velControl;
PID rightVControl;
PID leftVControl;
Point robotPos;
Path * currentPath;
void InitPath(Path * path);
double distance(Point a, Point b);
double sumDistances(Point points[]);
Point currentPoint();
void updateRobotPose();
void moveRight(double rightDist);
void moveLeft(double leftDist);
void driveToPoint(Point point);
void followPath();


#endif
