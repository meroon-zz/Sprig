
#include "SprigGameObject.h"
#include "SprigRectangle.h"
#include "SprigVector.h"

#include <vector>


GameObject::GameObject()
{
    
}

GameObject::~GameObject()
{
    
}

void GameObject::Draw(Renderer &renderer)
{
    renderer.PushMatrix();
    
    renderer.LoadIdentity();
    
    renderer.Translate(0.0f, 0.0f, -30.0f);
    
    if(showBackground)
    {
        renderer.setVertexColor(backgroundColor);
    }
    
    if(_texture.GetTextureData() != NULL)
    {        
        renderer.BindTexture(_texture);
    }
    
    renderer.DrawMesh(_mesh);
    
    renderer.PopMatrix();
    
    
    
    
    
}


Texture& GameObject::getTexture()
{
    return _texture;
}

Mesh& GameObject::getMesh()
{
    return _mesh;
}