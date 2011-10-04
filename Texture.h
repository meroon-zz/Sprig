#pragma once

#include <OpenGLES/ES1/gl.h>
#include <string>

class Texture
{
  public:
    
    Texture(const char *key) : name(0), width(1), height(1) { this->key = key; }
    Texture(const char *key, int width, int height) : name(0)
    {
        this->key = key;
        this->width = width;
        this->height = height;
    }
    
    GLuint name;
    
    unsigned int width;
    unsigned int height;
    
    const char *key;
};  