#ifndef _PID_H
#define _PID_H

#include "PID.h"

/*
 *---------------------------PID----------------------------
 *PID module provides robot subsystems with the PID control
 *to filter the output of its motors.
 *
 *Module: PID
 *Author: Benigno Vargas Chihuahua
 *Version:1.0
 *----------------------------------------------------------
 */

typedef struct
{
	float kP;
	float kI;
	float kD;
	float setpoint;
	float sumError;
	float prevError;
	float prevInput;
	float integralZone;
	float pidDeadband;
	int maxOutput;
	int minOutput;
} PID;

//PID Objects
PID driveTrainPID;
PID robotArmPID;

//function declarations
void SetPID(float kP, float kI, float kD, PID pidObj);
void setTarget(PID pidObj,float target);
int calculateOuput(PID pidObj,float inputVal);

void SetPID(float kP, float kI, float kD, PID pidObj)
{
	pidObj.kP = kP;
	pidObj.kI = kI;
	pidObj.kD = kD;
}

void setTarget(PID pidObj, float target)
{
	pidObj.setpoint = target;
}

/*
 * Implements a PID control algorithm to smooth and filter output to motors
 *
 * inputVal - the value from the controlling sensor such as an optical encoder or gyro
 */
int calculateOuput(PID pidObj, float inputVal)
{
	pidObj.prevInput = inputVal;
	float error = pidObj.setpoint - inputVal;

	int integral;
	int proportional;
	int derivative;

	float perror = (error < pidObj.pidDeadband ? 0 : error);

	proportional = perror * pidObj.kP;

	if(abs(error) < pidObj.integralZone)
		integral = 0;
	else
		integral = pidObj.kI * pidObj.sumError;


	pidObj.sumError += error;

	float output = proportional + integral + derivative;

	if(output > pidObj.maxOutput)
		return pidObj.maxOutput;
	else if(output < pidObj.minOutput)
		return pidObj.minOutput;


		return output;
}

#endif
