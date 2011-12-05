
#include "SprigEntity.h"
#include "SprigRectangle.h"
#include "SprigVector.h"

#include <vector>


Entity::Entity()
{
    
}

Entity::~Entity()
{
    
}

void Entity::Update()
{
    
}

void Entity::Draw(Renderer &renderer)
{
    renderer.PushMatrix();
    
    renderer.LoadIdentity();
    
    renderer.Translate(0.0f, 0.0f, -30.0f);
    
    if(showBackground)
    {
        renderer.setVertexColor(backgroundColor);
    }
    else
    {
        //Color clearedColor = Color(1,1,1,0);
        
        //renderer.setVertexColor(clearedColor);
    }
    
    if(_texture.GetTextureData() != NULL)
    {   
        renderer.EnableTexture();
        renderer.BindTexture(_texture);
    }
    else
    {
        renderer.DisableTexture();
    }
    
    renderer.DrawMesh(_mesh);
    
    renderer.PopMatrix();
    
    
    
    
    
}


Texture& Entity::getTexture()
{
    return _texture;
}

Mesh& Entity::getMesh()
{
    return _mesh;
}