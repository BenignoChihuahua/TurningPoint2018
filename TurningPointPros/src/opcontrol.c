/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

#include "DriveTrain.h"
#include "RobotArm.h"
#include "RollerIntake.h"
#include "PathFollower.h"
#include "util.h"
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	Path path;
	int total = 0;
	/*for(int i = 0; i < 25; i++)
	{
		Point point;
		point.x = 0;
		point.y = total + 1;
		total += 1;
		path.waypoints[i] = point;
	}*/

	Point point;
	point.x = 0;
	point.y = 2;
	path.waypoints[0] = point;
	Point point1;
  point.x = 0;
	point.y = 5;
  path.waypoints[1] = point1;
	Point point2;
	point.x = 5;
	point.y = 9;
	path.waypoints[2] = point2;
	Point point3;
	point.x = 9;
	point.y = 9;
	path.waypoints[3] = point3;
	InitPath(&path);

	while (1) {

		DriveOnLoop();
		ArmOnLoop();
		IntakeOnLoop();
		followPath();
		//driveToPoint(point);
    /*
		printf("[ ");
		printf("rightVel: %f, " ,rightVel);
		printf("leftVel: %f, " , leftVel);
		printf("rightEnc: %d, ", getRightEncoder());
		printf("leftEnc: %d, ",  getLeftEncoder());
		printf("BaseAngle: %d, ", getYaw());
		printf("] \n");
    */
		delay(20);
	}
}
