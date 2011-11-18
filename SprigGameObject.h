#pragma once

#include <string>

#include "SprigRenderer.h"
#include "SprigTexture.h"
#include "SprigMesh.h"

using namespace std;

class GameObject	
{
    
public:
    
    GameObject();
    virtual ~GameObject();
    
    virtual void Draw(Renderer& renderer);
    
    Color backgroundColor;
    bool showBackground;
    
    Texture& getTexture(); 
    Mesh& getMesh();
    
private:
    
    Texture _texture;
    Mesh _mesh;
};