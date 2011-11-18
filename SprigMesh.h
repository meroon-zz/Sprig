#pragma once
            
#include <vector>
#include "SprigVector.h"

class Mesh
{

public:
    
    Mesh();
    ~Mesh();
    
    void Clear();
    
    void AddVertex(GLfloat x, GLfloat y, GLfloat z);
    void AddNormal(GLfloat x, GLfloat y, GLfloat z);
    void AddUV(GLfloat x, GLfloat y);
    
    std::vector<Vector3*> vertices;
    std::vector<Vector3*> normals;
    std::vector<Vector2*> uv;
    std::vector<unsigned int> triangles; 
};