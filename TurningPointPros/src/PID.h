#ifndef PID_H
#define PID_H

typedef struct
{
  double p;
  double i;
  double d;
  double lastInput;
  double setPoint;
  double error;
  double sumError;
  double deadband;
  double prevError;
  int maxOutput;
  int minOutput;
} PID;

void PIDInit(PID pid,double p, double i, double d);
double CalculateOutput(PID pid, double input);
void SetPoint(PID pid, double target);
void SetDeadband(PID pid, double deadband);
void SetP(PID pid, double p);
void SetI(PID pid, double i);
void SetD(PID pid, double d);
double PID_P(PID pid);
double PID_I(PID pid);
double PID_D(PID pid);
double PID_Error(PID pid);


#endif
