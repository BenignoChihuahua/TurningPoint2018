#ifndef _UTIL_H
#define _UTIL_H

int deadband(int val, int limit);

int deadband(int val, int limit)
{
	return abs(val) > limit ? val : 0;
}

#endif
