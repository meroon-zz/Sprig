#pragma once

#include <string>

#include "SprigRenderer.h"
#include "SprigTexture.h"

using namespace std;

class GameObject	
{
    
public:
    
    GameObject() : width(100), height(100), showBackground(false){};
    virtual ~GameObject();
    
    virtual void Draw(Renderer& renderer);
    
    Color backgroundColor;
    bool showBackground;
    
    unsigned int width;
    unsigned int height;
    
    int x;
    int y;
    
    Texture *texture;
};