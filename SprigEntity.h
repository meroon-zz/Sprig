#pragma once

#include <string>

#include "SprigRenderer.h"
#include "SprigTexture.h"
#include "SprigMesh.h"

using namespace std;

class Entity	
{
    
public:
    
    Entity();
    virtual ~Entity();
    
    virtual void Draw(Renderer& renderer);
    virtual void Update();
    
    Color backgroundColor;
    bool showBackground;
    
    Texture& getTexture(); 
    Mesh& getMesh();
    
protected:
    
    Texture _texture;
    Mesh _mesh;
};