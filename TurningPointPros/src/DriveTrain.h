#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "PID.h"
#include <API.h>


Encoder RightEncoder;
Encoder LeftEncoder;
Gyro    baseGyro;
PID rVelControl;//used to send velocity controls to motors
PID lVelControl;
int iteration;
int prevLeftEnc;
int prevRightEnc;
double rightDistance;
double leftDistance;
double rightVel;
double leftVel;
double angVel;
bool SystemsError();
void InitDriveTrain();
void DriveOnLoop();
void sensorData();
void updateVelocity();
void arcadeDrive(unsigned char ver_axis, unsigned char hor_axis);
void mecanumDrive(unsigned char hor_axis);
void moveLeftVel(double vel);
void moveRightVel(double vel);
void moveRightMotor(int val);
void moveLeftMotor(int val);
void setRightVel(double vel);
void setLeftVel(double vel);
double getRightVel();
double getLeftVel();
int getLeftEncoder();
int getRightEncoder();
int getYaw();
double distanceTraveled(int encoderCounts);
double numRotations(int encoderCounts);




#endif
