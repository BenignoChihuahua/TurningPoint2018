int deadband(int val, int limit);

int deadband(int val, int limit)
{
	return abs(val) > limit ? val : 0;
}
