#include "PathFollower.h"
#include "DriveTrain.h"
#include "PID.h"
#include <Math.h>
#include <API.h>

#define WHEEL_TRACK 10 //inches
#define TIMESTEP 0.02 //timestep of main loop (20 ms)

void InitPath(Path * path)
{

  currentPath = path;
  pathIndex = 0;
  pathPoints = sizeof(currentPath->waypoints)/sizeof(currentPath->waypoints[0]);
  distLastPoint = sumDistances(currentPath->waypoints);
  distNextPoint = distance(robotPos,currentPath->waypoints[0]);
  //distNextPoint = 1;

  //pid
  PIDInit(velControl,0.33,0,0);
  SetPoint(velControl,0);
  velControl.p = 2.5;
  velControl.i = .3;
  velControl.d = 0;
  velControl.maxOutput = 127;
  velControl.minOutput = -127;

  PIDInit(rightVControl,0.2,0,0);
  SetPoint(rightVControl,0);
  rightVControl.p = 1.5;
  rightVControl.i = .15;
  rightVControl.d = 0;
  rightVControl.maxOutput = 127;
  rightVControl.minOutput = -127;

  PIDInit(leftVControl,2,0,0);
  SetPoint(leftVControl,0);
  leftVControl.p = 1.5;
  leftVControl.i = .15;
  leftVControl.d = 0;
  leftVControl.maxOutput = 127;
  leftVControl.minOutput = -127;
}

void followPath() {
      if(distNextPoint > 0.5 && pathIndex < pathPoints)
      {
        driveToPoint(currentPath->waypoints[pathIndex]);
        updateRobotPose();
        distNextPoint = distance(robotPos,currentPath->waypoints[pathIndex]);
        printf("dist: %f ",distNextPoint );
        printf("RobotX: %f, RobotY: %f ",robotPos.x, robotPos.y);
        printf("i: %d \n",pathIndex);
      }
      else
      {
          pathIndex++;
          robotPos.heading = 0;
          distNextPoint = distance(robotPos,currentPath->waypoints[pathIndex]);
          printf("dist: %f ",distNextPoint);
          printf("RobotY: %f ",robotPos.y);

      }
    //distNextPoint = distance(robotPos,currentPath->waypoints[i+1]);


}

void driveToPoint(Point point) {
    deltaX = fabs(point.x - robotPos.x);
    deltaY = fabs(point.y - robotPos.y);
    distLastPoint = deltaY;
    if(deltaX != 0)
    {
      theta = tan(deltaY/deltaX);
      double radius = deltaX;
      rDist = theta * (radius + WHEEL_TRACK);
      lDist = theta * (radius);
    }
    else
    {
      rDist = deltaY;
      lDist = deltaY;
    }
    moveRight(rDist);
    moveLeft(lDist);
}

//use kalman filter for better localization in the future
void updateRobotPose() {
  double robotVel = (getRightVel() + getLeftVel())/2;
  double angularVel = (getRightVel() - getLeftVel())/WHEEL_TRACK;

  robotPos.heading += angularVel * TIMESTEP;
  robotPos.x -= robotVel * TIMESTEP * sin(robotPos.heading);
  robotPos.y += robotVel * TIMESTEP * cos(robotPos.heading);
}

double sumDistances(Point points[]) {
  double sum = 0.0;
  for(int i = 0; i < pathPoints - 1; i++)
  {
    sum += distance(points[i], points[i+1]);
  }

  return sum;
}

double distance(Point a, Point b)
{
  double dX = pow((b.x - a.x),2);
  double dY = pow((b.y - a.y),2);
  return sqrt(dX + dY);
}

void moveRight(double rightDist) {
  double rightVel = CalculateOutput(velControl,distLastPoint);
  rightVel += CalculateOutput(rightVControl, distNextPoint);
  moveRightVel(rightVel);
}

void moveLeft(double leftDist) {
  double leftVel = CalculateOutput(velControl, distLastPoint);
  leftVel += CalculateOutput(leftVControl, distNextPoint);
  moveLeftVel(leftVel);
}
