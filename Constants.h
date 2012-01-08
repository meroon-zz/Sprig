#pragma once

#include <stdio.h>
#include <stdarg.h>

#define kActiveFrameRate 30.0
#define kInactiveFrameRate 2.0

#define kUseDepthBuffer 1

#define kZNear			-100.0
#define kZFar			100.0
#define kFieldOfView	45.0

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define trace(str, ...) __trace__("[%s:%d] %s", __FILE__, __LINE__, str) 
#else
    #define trace(str, ...)
#endif

inline void __trace__(const char *format, ...) {
    
    va_list args;
    
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}
