#pragma once

class Rectangle
{    
  public:
 
    Rectangle(): x(0.0) , y(0.0) , width(1.0) , height(1.0) {}
    Rectangle(float width, float height);
    Rectangle(float x, float y, float width, float height);
    
    float x, y, width, height;
};
