//
//  SprigSprite.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigSprite.h"

Sprite::Sprite()
{
    _x = 0;
    _y = 0;
    _width = 100;
    _height = 100;
    
    /* 
     
     1 ------- 3
     |         |
     |         |
     |         |
     2 ------- 4
     
     */
    
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);
    _mesh.AddVertex(0, 0, 0);    
    
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    _mesh.AddNormal(0, 0, 1);
    
    _mesh.AddTextureCoor(0.0f, 1.0f);
    _mesh.AddTextureCoor(0.0f, 0.0f);
    _mesh.AddTextureCoor(1.0f, 1.0f);
    _mesh.AddTextureCoor(1.0f, 0.0f);
    
    
    calculateMesh();    
}

Sprite::~Sprite()
{
    
}

void Sprite::setPosition(float x, float y)
{
    _x = x;
    _y = y;
    
    calculateMesh();
}

void Sprite::setSize(float width, float height)
{
    _width = width;
    _height = height;
    
    calculateMesh();
}

void Sprite::calculateMesh()
{
    //unsigned int screenWidth = 320;
    unsigned int screenHeight = 480;
    
    _mesh.vertices[0]->x = _x;
    _mesh.vertices[0]->y = screenHeight - _y;
    
    _mesh.vertices[1]->x = _x;
    _mesh.vertices[1]->y = screenHeight - (_y + _height);
    
    _mesh.vertices[2]->x = _x + _width;
    _mesh.vertices[2]->y = screenHeight - _y;
    
    _mesh.vertices[3]->x = _x + _width;
    _mesh.vertices[3]->y = screenHeight - (_y + _height);
}

void Sprite::AddBitmap(Bitmap &bitmap)
{
    Texture texture = Texture(bitmap);
    _texture.Apply(texture);
}