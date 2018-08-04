#include <stdlib.h>
#include "util.h"

int deadband(int val, int deadband)
{
  return abs(val) < deadband ? 0 : val;
}
