
#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <math.h>

static inline double DegreesToRadians(double angle)
{
	return angle / 180.0 * M_PI;
}

static inline float randf()
{
    return (float)rand()/(float)RAND_MAX;
}

#endif