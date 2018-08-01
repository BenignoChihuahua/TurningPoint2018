#ifndef _FOUR_BAR_ARM_H
#define _FOUR_BAR_ARM_H

//motor,digital, and analog ports are defined in the excel sheet 9898AMetadata.xlsx
#define RIGHT_MOTOR port6
#define LEFT_MOTOR  port7


/*
 *---------------------------FourBarArm----------------------------
 * The FourBarArm is a mechanism that is driven by two Vex393 motors
 * on the same shaft which in turn allows for the claw to move on the
 * z axis. When integrated with encoders, this module provides the
 * functionality of recording the current position of the subsystem to
 * provide more robust control in autonomous and operator control.
 *
 * Module: FourBarArm
 * Author: Benigno Vargas Chihuahua
 * Version: 1.0
 */

//function declarations
void InitRobotArm();
void drive(int val);

void InitRobotArm()
{
}

//this function is called repeatedly in the user control loop
task ArmOnLoop()
{

}

void drive(int val)
{
	motor[RIGHT_MOTOR] = val;
	motor[LEFT_MOTOR] = val;
}


#endif
