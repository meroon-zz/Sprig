#pragma once

#define kActiveFrameRate 30.0
#define kInactiveFrameRate 2.0

#define kUseDepthBuffer 1

#define kZNear			-100.0
#define kZFar			100.0
#define kFieldOfView	45.0

#include <stdio.h>
#include <stdarg.h>

inline void trace(const char *format, ...) {
    
    va_list args;
    
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}