//
//  SprigMesh.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-16.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigMesh.h"

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    
}

void Mesh::AddVertex(GLfloat x, GLfloat y, GLfloat z)
{
    Vector3 *vertex = new Vector3(x, y, z);
    
    vertex->Print();
    
    vertices.push_back(vertex);
}

void Mesh::AddNormal(GLfloat x, GLfloat y, GLfloat z)
{
    Vector3 *normal = new Vector3(x, y, z);
    
    normals.push_back(normal);
}

void Mesh::AddUV(GLfloat x, GLfloat y)
{
    Vector2 *coor = new Vector2(x, y);
    
    uv.push_back(coor);
}

void Mesh::Clear()
{
    vertices.clear();
    normals.clear();
    uv.clear();
}