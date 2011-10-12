//
//  Texture.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-09-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Texture.h"
#include "MathUtil.h"

// TESTS ///////////////////////////////////////////////////

void TestAddSubtexture(Texture *texture, Texture *child)
{
    const char *result = texture->ContainsSubTexture(child) ? "SUCCESS" : "FAIL";
    
    printf("[Test] Texture::AddSubTexture [%s]", result);
}


// IMPLEMENTAION ///////////////////////////////////////////


Texture* Texture::getParent()
{
    return _parent;
}

void Texture::setParent(Texture *parent)
{
    this->textureName = parent->textureName;
    
    _parent = parent;
}

void Texture::AddSubTexture(Texture *subTexture)
{    
    if(!ContainsSubTexture(subTexture))
    {
        _textures.push_back(subTexture);
    }
    
    TestAddSubtexture(this, subTexture);
    
}

bool Texture::ContainsSubTexture(Texture *subTexture)
{
    bool result = false;
    
    std::vector<Texture *>::iterator iter;
    
    for(iter = _textures.begin(); iter != _textures.end(); ++iter)
    {
        if (*iter == subTexture) 
        {
            result = true;
            break;
        }
    }
    
    return result;
}

void Texture::ComputeUV()
{
    GLfloat baseWidth = _parent != NULL ? _parent->width : width;
    GLfloat baseHeight = _parent != NULL ? _parent->height : height;
    
    _uv[0] = (GLfloat)offsetX / baseWidth;
    _uv[1] = (GLfloat)offsetY / baseHeight;
    _uv[2] = (GLfloat)offsetX / baseWidth;
    _uv[3] = (GLfloat)(offsetY + height) / baseHeight;
    _uv[4] = (GLfloat)(offsetX + (GLfloat)width) / baseWidth;
    _uv[5] = (GLfloat)offsetY / baseHeight;
    _uv[6] = (GLfloat)(offsetX + (GLfloat)width) / baseWidth;
    _uv[7] = (GLfloat)(offsetY + height) / baseHeight;    
}

void Texture::ComputeUV(Rectangle &clipRect)
{
    GLfloat baseWidth = _parent != NULL ? _parent->width : width;
    GLfloat baseHeight = _parent != NULL ? _parent->height : height;
    
    _uv[0] = (GLfloat)offsetX / baseWidth;
    _uv[1] = (GLfloat)offsetY / baseHeight;
    _uv[2] = (GLfloat)offsetX / baseWidth;
    _uv[3] = (GLfloat)(offsetY + minf((GLfloat)height, clipRect.height)) / baseHeight;
    _uv[4] = (GLfloat)(offsetX + minf((GLfloat)width, clipRect.width)) / baseWidth;
    _uv[5] = (GLfloat)offsetY / baseHeight;
    _uv[6] = (GLfloat)(offsetX + minf((GLfloat)width, clipRect.width)) / baseWidth;
    _uv[7] = (GLfloat)(offsetY + minf((GLfloat)height, clipRect.height)) / baseHeight;   
}

GLfloat* Texture::getUV()
{
    return _uv;
}