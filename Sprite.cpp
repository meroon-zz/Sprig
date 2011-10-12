//
//  Sprite.cpp
//  SpriEng
//
//  Created by Cam Warnock on 11-09-22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sprite.h"
#include "Game.h"
#include "MathUtil.h"

#include <string>

using std::string;

void Sprite::Init()
{
    _texture = NULL;
    backgroundColor = Color(0.5, 0.5, 0.5, 1.0);
}

void Sprite::Draw(Renderer renderer)
{        
    if (_texture) {
        
        renderer.DrawTexture(_clipRect, *_texture);
    }
    else
    {        
        renderer.DrawRect(rect, backgroundColor);
    }
}

void Sprite::ApplyTexture(Texture *texture, TextureClipType clipType)
{
    _texture = texture;
    _clipType = clipType;
    
    if (_clipType == NoClipping) {
        _texture->ComputeUV();
        _clipRect = Rectangle(rect.x, rect.y, (GLfloat)_texture->width, (GLfloat)_texture->height);        
    }
    else if(_clipType == Clipping)
    {
        _texture->ComputeUV(rect);

        _clipRect = Rectangle(rect.x, rect.y, minf(rect.width, (GLfloat)_texture->width), minf(rect.height, (GLfloat)_texture->height));
    }
}

void Sprite::RemoveTexture()
{
    _texture = NULL;
}