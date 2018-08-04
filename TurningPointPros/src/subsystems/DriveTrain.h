#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "API.h"
#include "../control/PID.h"

//module values
Encoder RightEncoder;//
Encoder LeftEncoder; // Sensors
Gyro    baseGyro;    //
PID velPID;         //
PID rightEncPID;    //PID
PID leftEncPID;     //Controls
PID gyroPID;        //
int iteration;      //used for drive loop
int prevRightEnc;   //
int prevLeftEnc;    //
int finalRightEnc;  //
int finalLeftEnc;   //Velocity variables
double rightVel;    //
double leftVel;     //
double angVel;      //

//function declarations
bool SystemsError();
void InitDriveTrain();
void DriveOnLoop();
void PrintDriveData();

void arcadeDrive(unsigned char ver_axis, unsigned char hor_axis);
void mecanumDrive(unsigned char hor_axis);
void moveRight(double vel);
void moveLeft(double vel);
void getRightVel(double vel);
void getLeftVel(double vel);
void setRightVel(double vel);
void setLeftVel(double vel);
void moveRightMotor(int val);
void moveLeftMotor(int val);

void setGyroSetpoint(int degree);
void setRightEncSetpoint(int encoderCounts);
void setLeftEncSetpoint(int encoderCounts);
void setVelSetpoint(double velocity);

int distanceToEncoder(double distance);
double encoderToDistance(int encoderCounts);
double revolutionsPerEncoder(int encoderCounts);
void resetEncoders();
int getLeftEncoder();
int getRightEncoder();
int getYaw();

#endif
