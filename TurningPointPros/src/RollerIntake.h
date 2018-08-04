#ifndef ROLLER_INTAKE_H
#define ROLLER_INTAKE_H

void InitRollerIntake();
void IntakeOnLoop();
void intakeMotor(int val);
void forward();
void reverse();
bool IntakeError();

#endif
