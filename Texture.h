#pragma once

#include <OpenGLES/ES1/gl.h>
#include <string>

class Texture
{
  public:
    
    Texture(std::string &key) : name(0), offsetX(0), offsetY(0), width(1), height(1) { this->key = key; }
    Texture(std::string &key, int width, int height) : name(0), offsetX(0), offsetY(0)
    {
        this->key = key;
        this->width = width;
        this->height = height;
    }
    
    GLuint name;
    
    int offsetX;
    int offsetY;
    unsigned int width;
    unsigned int height;
    
    std::string key;
};  