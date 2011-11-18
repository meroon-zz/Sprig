
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
    
    renderer.Translate(0.0f, 0.0f, -30.0f);
    
    renderer.setVertexColor(backgroundColor);
    
    renderer.DrawMesh(_mesh);
    
    renderer.PopMatrix();
    
    if(showBackground)
    {
        //renderer.DrawRect(rect, backgroundColor);
    }
    
    if(_texture.GetTextureData() != NULL)
    {
        //renderer.DrawTexture(rect, _texture);
    }
    
    
    
}


Texture& GameObject::getTexture()
{
    return _texture;
}

Mesh& GameObject::getMesh()
{
    return _mesh;
}