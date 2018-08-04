#include <API.h>
#include "RobotArm.h"

#define RIGHT_MOTOR 5
#define LEFT_MOTOR  6

void InitRobotArm()
{
  toggle = true;
}

void ArmOnLoop()
{
  bool powerFor = joystickGetDigital(1,6,JOY_UP);
  if(!ArmError())
  {
    if(toggle)
    {
      if(powerFor)
        drive(64);
      else
        toggle = !toggle;
    }
    else if(!toggle)
    {
      if(powerFor)
        drive(-64);
      else
        toggle = !toggle;
    }
  }
}

void drive(int val)
{
  motorSet(RIGHT_MOTOR, val);
  motorSet(LEFT_MOTOR,  val);
}

void resetArm()
{

}

bool ArmError()
{
  return false;//TODO: implement safety checks
}
