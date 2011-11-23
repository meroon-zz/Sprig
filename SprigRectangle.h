#pragma once

#include <stdio.h>

class Rectangle
{    
  public:
 
    Rectangle(): x(0.0) , y(0.0) , width(1.0) , height(1.0) {}
    Rectangle(float width, float height);
    Rectangle(float x, float y, float width, float height);
    
    float x, y, width, height;
    
    inline void Print() { printf("[Rectangle] x: %f  y: %f  width: %f  height: %f\n", x, y, width, height); };
};
