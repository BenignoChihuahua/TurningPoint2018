#include <API.h>
#include "DriveTrain.h"
#include "util.h"


#define FRONT_RIGHT_MOTOR 2
#define BACK_RIGHT_MOTOR  3
#define FRONT_LEFT_MOTOR  4
#define BACK_LEFT_MOTOR   5

#define RIGHT_ENC_TOP 8
#define RIGHT_ENC_BOTTOM 9
#define LEFT_ENC_TOP 6
#define LEFT_ENC_BOTTOM 7

#define GYRO 1

#define WHEEL_CIRCUM 9.6 //in inches

void InitDriveTrain()
{
  RightEncoder = encoderInit(RIGHT_ENC_TOP, RIGHT_ENC_BOTTOM, true);
  LeftEncoder = encoderInit(LEFT_ENC_TOP,LEFT_ENC_BOTTOM,true);
  baseGyro = gyroInit(GYRO,0);
  PIDInit(rVelControl,6,0,0);
  rVelControl.p = 6;
  rVelControl.i = 0;
  rVelControl.d = 0;
  rVelControl.maxOutput = 127;
  rVelControl.minOutput = -127;

  PIDInit(lVelControl,6,0,0);
  lVelControl.p = 6;
  lVelControl.i = 0;
  lVelControl.d = 0;
  lVelControl.maxOutput = 127;
  lVelControl.minOutput = -127;
}

void DriveOnLoop()
{


  if(!(SystemsError()))
  {
      //if(EMERGENCY_BUTTON) then stop drive system
      int strafe = deadband(joystickGetAnalog(1,4),15);
      int power = deadband(joystickGetAnalog(1,2),15);
      int turn = deadband(joystickGetAnalog(1,1),15);

      motorSet(2,-power + turn + strafe);//rightmotors
      motorSet(3,-power + turn - strafe);
      motorSet(4,power + turn  + strafe);//leftmotors
      motorSet(5,power + turn  - strafe);

  }

  int finalLeftEnc = getLeftEncoder();
  int finalRightEnc = getRightEncoder();
  rightDistance = distanceTraveled(finalRightEnc - prevRightEnc);
  leftDistance = distanceTraveled(finalLeftEnc - prevLeftEnc);

  if(iteration % 10)
  {

    updateVelocity();
    //sensorData();
  }

  prevLeftEnc =  getLeftEncoder();
  prevRightEnc = getRightEncoder();

  ++iteration;
}

void sensorData()
{
  printf("[ ");
  printf("RightVelocity: %f, ", rightDistance/0.02);
  printf("LeftVelocity: %f, " , leftDistance/0.02);
  printf("RightEnc: %d, "     , encoderGet(RightEncoder));
  printf("LeftEnc: %d, "      , encoderGet(LeftEncoder));
  printf("BaseGyro: %d "      , getYaw());
  printf("] \n");
}

void updateVelocity()
{
  setRightVel(rightDistance/0.02);
  setLeftVel(leftDistance/0.02);
}

void arcadeDrive(unsigned char vert_axis, unsigned char hor_axis)
{
  int power = joystickGetAnalog(1,vert_axis);
  int turn  = joystickGetAnalog(1,hor_axis);
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

void moveRightVel(double vel)
{
  rVelControl.setPoint = vel;
  moveRightMotor(CalculateOutput(rVelControl,rightVel));
}

void moveLeftVel(double vel)
{
  lVelControl.setPoint = vel;
  moveLeftMotor(CalculateOutput(lVelControl,leftVel));
}

void moveRightMotor(int val)
{
  motorSet(FRONT_RIGHT_MOTOR, val);
  motorSet(BACK_RIGHT_MOTOR, val);
}

void moveLeftMotor(int val)
{
  motorSet(FRONT_LEFT_MOTOR, -val);
  motorSet(BACK_LEFT_MOTOR, -val);
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

double getRightVel()
{
  return rightVel;
}

double getLeftVel()
{
  return leftVel;
}

double distanceTraveled(int encoderCounts)
{
  return numRotations(encoderCounts) * WHEEL_CIRCUM;
}

double numRotations(int encoderCounts)
{
  return encoderCounts/360.0;
}
