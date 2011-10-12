#pragma once

#include <math.h>

static inline double DegreesToRadians(double angle)
{
	return angle / 180.0 * M_PI;
}

static inline float randf()
{
    return (float)rand()/(float)RAND_MAX;
}

static inline float minf(float val1, float val2)
{
    return val1 <= val2 ? val1 : val2;
}

static inline float maxf(float val1, float val2)
{
    return val1 >= val2 ? val1 : val2;
}
