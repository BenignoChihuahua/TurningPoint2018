#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "API.h"
#include "PID.h"

Encoder RightEncoder;
Encoder LeftEncoder;
Gyro    baseGyro;
PID velPID;
PID rightEncPID;
PID leftEncPID;
PID gyroPID;
int iteration;
int prevRightEnc;
int prevLeftEnc;
int finalRightEnc;
int finalLeftEnc;
double rightVel;
double leftVel;
double angVel;
bool SystemsError();
void InitDriveTrain();
void DriveOnLoop();
void arcadeDrive(unsigned char ver_axis, unsigned char hor_axis);
void mecanumDrive(unsigned char hor_axis);
void driveDistance(double x);
void moveRightMotor(int val);
void moveLeftMotor(int val);
void setRightVel(double vel);
void setLeftVel(double vel);
void resetEncoders();
void setGyroSetpoint(int degree);
int getLeftEncoder();
int getRightEncoder();
int getYaw();
double encoderToDistance(int encoderCounts);
double revolutionsPerEncoder(int encoderCounts);


#endif
