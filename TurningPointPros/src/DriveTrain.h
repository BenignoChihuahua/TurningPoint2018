#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "API.h"


Encoder RightEncoder;
Encoder LeftEncoder;
Gyro    baseGyro;
int iteration;
double rightVel;
double leftVel;
double angVel;
bool SystemsError();
void InitDriveTrain();
void DriveOnLoop();
void arcadeDrive(unsigned char ver_axis, unsigned char hor_axis);
void mecanumDrive(unsigned char hor_axis);
void moveRightMotor(int val);
void moveLeftMotor(int val);
void setRightVel(double vel);
void setLeftVel(double vel);
int getLeftEncoder();
int getRightEncoder();
int getYaw();
double distanceTraveled(int encoderCounts);
double numRotations(int encoderCounts);




#endif
