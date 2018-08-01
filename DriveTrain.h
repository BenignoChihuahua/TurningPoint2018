#ifndef _DRIVE_TRAIN_H
#define _DRIVE_TRAIN_H

#include "util.h"

/*
  All port information can be found in the excel file of this program's directory
  9898AMetadata.xlsx
 */

//DriveTrain Motors
#define FRONT_RIGHT_MOTOR port5
#define FRONT_LEFT_MOTOR port2
#define BACK_RIGHT_MOTOR port3
#define BACK_LEFT_MOTOR port4

//DriveTrain sensors
#define _GYRO
#define _ACCEL

//DriveTimer that is used to calculate the velocity of the base
#define DRIVE_TIMER T1

//DriveTrain constants
#define WHEEL_DIAM 3.25
#define WHEEL_CIRCUM 20.42

/*
 * ---------------------Drive Train Description---------------------
 * The DriveTrain base of the robot contains 4 mecanum wheels,
 * with two of them being equipped with optical encoders. The
 * mecanum wheels provide the robot with the capability of strafing.
 * Combining the odometry and internal measurement unit(gyro/accelerometer)
 * we will be able to a certain degree of accuracy find the position
 * of the robot using an extended kalman filter.
 *
 * Module: DriveTrain
 * Author:Benigno Vargas Chihuahua
 * Version:1.0
 * -----------------------------------------------------------------
 */

//function declarations
void initDriveTrain();
void DriveOnLoop();
void zeroEncoders();
void resetGyro();
void clearDriveTimer();
void strafe(int val);
void moveRightMotor(int val);
void moveLeftMotor(int val);
float driveDistance(int numRotations);
float driveVelocity(int encoderCounts);
float numRotations(int encoderCounts);

//module variables
float timeDifference;//this is the time that is passed on each iteration of the auto or user loop


void initDriveTrain()
{
	bMotorReflected[FRONT_RIGHT_MOTOR] = false;
 	bMotorReflected[BACK_RIGHT_MOTOR] = false;
	bMotorReflected[FRONT_LEFT_MOTOR] = true;
 	bMotorReflected[BACK_LEFT_MOTOR] = true;

 	zeroEncoders();
 	resetGyro();
 	clearDriveTimer();
}

void DriveOnLoop()
{
   	moveRightMotor(deadband(vexRT(Ch2) -  vexRT(Ch1),25));
		moveLeftMotor(deadband(vexRT(Ch2) + vexRT(Ch1),25));
		strafe(deadband(vexRT(Ch4),20));
}

void strafe(int val)
{
	motor[FRONT_LEFT_MOTOR] = -val;
	motor[BACK_LEFT_MOTOR] =   val;
	motor[FRONT_RIGHT_MOTOR] = val;
	motor[BACK_RIGHT_MOTOR] = -val;
}

void moveRightMotor(int val)
{
		motor[FRONT_RIGHT_MOTOR] = val;
		motor[BACK_RIGHT_MOTOR] = val;
}

void moveLeftMotor(int val)
{
		motor[FRONT_LEFT_MOTOR] = val;
		motor[BACK_LEFT_MOTOR] =  val;
}

float numRotations(int encoderCounts)
{
	return encoderCounts/WHEEL_DIAM;
}

float driveDistance(int numRotations)
{
	return numRotations * WHEEL_CIRCUM;
}

float driveVelocity(int encoderCounts)
{
		return driveDistance(numRotations(encoderCounts))/timeDifference;
}


void zeroEncoders()
{
	return;
}

void resetGyro()
{
	return;
}

void clearDriveTimer()
{
	ClearTimer(DRIVE_TIMER);
}

#endif
