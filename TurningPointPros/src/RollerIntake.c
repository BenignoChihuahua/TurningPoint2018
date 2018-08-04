#include <API.h>
#include "RollerIntake.h"
#include "util.h"

#define INTAKE_MOTOR 7


void InitRollerIntake()
{

}

void IntakeOnLoop()
{
  bool intake  = joystickGetDigital(1,6,JOY_UP);
  bool backward = joystickGetDigital(1,5,JOY_DOWN);
  if(!IntakeError())
  {
    if(intake)
      motorSet(INTAKE_MOTOR,64);
    else if(backward)
      motorSet(INTAKE_MOTOR,-64);

  }
}

void intakeMotor(int val)
{
  motorSet(INTAKE_MOTOR,deadband(val,10));
}

void forward() {intakeMotor(64);}
void reverse() {intakeMotor(-64);}

bool IntakeError()
{
  return false;
}
