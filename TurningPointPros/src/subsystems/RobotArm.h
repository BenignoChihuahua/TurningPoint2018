#ifndef ROBOT_ARM_H
#define ROBOT_ARM_H


bool toggle;//for one button control of the arm
bool ArmError();
void InitRobotArm();
void ArmOnLoop();
void drive(int val);
void resetArm();

#endif
