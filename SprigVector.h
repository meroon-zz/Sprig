#pragma once

#include <OpenGLES/ES1/gl.h>

class Vector2
{

public:
    
    Vector2(GLfloat x, GLfloat y) : x(x), y(y) {};
    
    Vector2();
    ~Vector2();

    GLfloat x;
    GLfloat y;
};

class Vector3
{
    
public:
    
    Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {};
    
    Vector3();
    ~Vector3();
    
    void Print();
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
