#include <API.h>
#include "DriveTrain.h"
#include "util.h"

#define FRONT_RIGHT_MOTOR 1
#define BACK_RIGHT_MOTOR  2
#define FRONT_LEFT_MOTOR  3
#define BACK_LEFT_MOTOR   4

#define RIGHT_ENC_TOP 1
#define RIGHT_ENC_BOTTOM 2
#define LEFT_ENC_TOP 3
#define LEFT_ENC_BOTTOM 4

#define GYRO 1

#define WHEEL_CIRCUM 9.6 //in inches

void InitDriveTrain()
{
  RightEncoder = encoderInit(RIGHT_ENC_TOP, RIGHT_ENC_BOTTOM, false);
  LeftEncoder = encoderInit(LEFT_ENC_TOP,LEFT_ENC_BOTTOM,false);
  baseGyro = gyroInit(GYRO,0);
}

void DriveOnLoop()
{
  int prevLeftEnc = getLeftEncoder();
  int prevRightEnc = getRightEncoder();

  if(!(SystemsError()))
  {
      //if(EMERGENCY_BUTTON) then stop drive system
      arcadeDrive(2,1); //arcade drive with these axis
      mecanumDrive(3);
  }

  int finalLeftEnc = getLeftEncoder();
  int finalRightEnc = getRightEncoder();
  double rightDistance = distanceTraveled(finalRightEnc - prevRightEnc);
  double leftDistance = distanceTraveled(finalLeftEnc - prevLeftEnc);
  setRightVel(rightDistance/0.02);
  setLeftVel(leftDistance/0.02);

}

void arcadeDrive(unsigned char vert_axis, unsigned char hor_axis)
{
  int power = deadband(joystickGetAnalog(1,vert_axis),15);
  int turn  = deadband(joystickGetAnalog(1,hor_axis) ,15);
  moveRightMotor(power - turn);
  moveLeftMotor(power + turn);
}

void mecanumDrive(unsigned char hor_axis)
{
  int strafe_power = joystickGetAnalog(1, hor_axis);
  motorSet(FRONT_RIGHT_MOTOR, strafe_power);
  motorSet(BACK_RIGHT_MOTOR, -strafe_power);
  motorSet(FRONT_LEFT_MOTOR, -strafe_power);
  motorSet(BACK_LEFT_MOTOR,   strafe_power);
}

bool SystemsError()
{
  return false;
}

void moveRightMotor(int val)
{
  motorSet(FRONT_RIGHT_MOTOR, val);
  motorSet(BACK_RIGHT_MOTOR, val);
}

void moveLeftMotor(int val)
{
  motorSet(FRONT_LEFT_MOTOR, val);
  motorSet(BACK_LEFT_MOTOR, val);
}

void resetEncoders()
{
  encoderReset(RightEncoder);
  encoderReset(LeftEncoder);
}

int getRightEncoder()
{
  return encoderGet(RightEncoder);
}

int getLeftEncoder()
{
  return encoderGet(LeftEncoder);
}

int getYaw()
{
  return gyroGet(baseGyro);
}

void setRightVel(double vel)
{
  rightVel = vel;
}

void setLeftVel(double vel)
{
  leftVel = vel;
}

double distanceTraveled(int encoderCounts)
{
  return numRotations(encoderCounts) * WHEEL_CIRCUM;
}

double numRotations(int encoderCounts)
{
  return encoderCounts/360.0;
}
