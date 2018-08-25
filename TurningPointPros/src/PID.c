#include <API.h>
#include <math.h>
#include "PID.h"

void PIDInit(PID pid,double p, double i, double d)
{
  pid.p = p;
  pid.i = i;
  pid.d = d;
  pid.maxOutput = 128;
  pid.minOutput = -128;
}

void SetPoint(PID pid, double target)
{
    pid.setPoint = target;
}

void SetDeadband(PID pid, double deadband)
{
  pid.deadband = deadband;
}

void SetP(PID pid, double p)
{
  pid.p = p;
}

void SetI(PID pid, double i)
{
  pid.i = i;
}

void SetD(PID pid, double d)
{
  pid.d = d;
}

double PID_P(PID pid)
{
    return pid.p;
}

double PID_I(PID pid)
{
  return pid.i;
}

double PID_D(PID pid)
{
  return pid.d;
}

double PID_Error(PID pid)
{
  return pid.error;
}

double CalculateOutput(PID pid, double input)
{
  pid.lastInput = input;
  double er = pid.setPoint - input;
  pid.error = er;

  //only apply I term if the error is in a close range
  if(((pid.error * pid.p) < pid.maxOutput) && ((pid.error * pid.p) > pid.minOutput))
     pid.sumError += pid.error;
  else
     pid.sumError = 0;
  double pError = fabs(pid.error) < pid.deadband ? 0 : pid.error;

  double output = pError * pid.p + pid.i * pid.sumError + pid.d * (pid.error - pid.prevError);

  pid.prevError = pid.error;

  if(output > pid.maxOutput)
    output = pid.maxOutput;
  else if(output < pid.minOutput)
    output = pid.minOutput;

  return output;
}
