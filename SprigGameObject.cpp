//
//  SprigGameObject.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigGameObject.h"
#include "SprigRectangle.h"


GameObject::~GameObject()
{
    delete texture;
}

void GameObject::Draw(Renderer &renderer)
{
    Rectangle rect = Rectangle(x, y, width, height);
    
    if(showBackground)
    {
        
        renderer.DrawRect(rect, backgroundColor);
    }
    
    if(texture->GetTextureData() != NULL)
    {
        renderer.DrawTexture(rect, *texture);
    }
    
}
