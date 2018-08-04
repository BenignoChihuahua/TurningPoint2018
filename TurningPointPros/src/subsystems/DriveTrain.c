#include <API.h>
#include <math.h>
#include "DriveTrain.h"
#include "../control/PID.h"
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
  PIDInit(gyroPID,1.4,0.0,0.0);
  PIDInit(velPID,0.0,0.0,0.0);
  PIDInit(rightEncPID,0.0,0.0,0.0);
  PIDInit(leftEncPID,0.0,0.0,0.0);
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

  if(iteration % 10)
  {
    finalLeftEnc = getLeftEncoder();
    finalRightEnc = getRightEncoder();
    double rightDistance = distanceTraveled(finalRightEnc - prevRightEnc);
    double leftDistance = distanceTraveled(finalLeftEnc - prevLeftEnc);
    setRightVel(rightDistance/0.02);
    setLeftVel(leftDistance/0.02);
    prevRightEnc = encoderGet(RightEncoder);
    prevLeftEnc = encoderGet(LeftEncoder);
  }

  PrintDriveData();

  ++iteration;
}

void PrintDriveData()
{
  printf("[ ");
  printf("RightVelocity: %f, ", rightVel);
  printf("LeftVelocity: %f, ", leftVel);
  printf("RightEnc: %d, ", encoderGet(RightEncoder));
  printf("RightEnc: %d, ", encoderGet(LeftEncoder));
  printf("BaseGyro: %d ", gyroGet(baseGyro));
  printf("distance traveled: %f", encoderToDistance(encoderGet(RightEncoder)));
  printf("] \n");
}

void driveDistance(double x)
{
    int correction = deadband(CalculateOutput(gyroPID, getYaw()), 15);
    motorSet(2,-64 + correction);
    motorSet(3,-64 + correction);
    motorSet(4,64 - correction);
    motorSet(5,64 - correction);
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

void setGyroSetpoint(int degree)
{
  gyroPID.setPoint = degree;
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
