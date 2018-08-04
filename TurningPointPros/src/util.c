#include <stdlib.h>
#include "util.h"

int deadband(int power,int limit)
{
  return abs(power) > limit ? power : 0;
}
