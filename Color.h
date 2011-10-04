#pragma once

class Color
{
  public:
    Color() : red(1.0), green(1.0), blue(1.0), alpha(1.0) {};
    Color(float red, float green, float blue, float alpha);
    
    float red, green, blue, alpha;
    
};
