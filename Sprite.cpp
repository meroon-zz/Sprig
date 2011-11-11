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
    
    string spritePath("run_test.png");
    string xmlPath("run_test.xml");
    
    _textures = Game::assetManager.GetTextures(xmlPath, spritePath);
    _texIter = _textures.begin();
}

void Sprite::Draw(Renderer renderer)
{        
    if (_texture) {
        
        printf("[Texture] name:  %d  offsetX: %d  offsetY:  %d  width:  %d  height:  %d\n", (**_texIter).textureName, (**_texIter).offsetX, (**_texIter).offsetY, (**_texIter).width, (**_texIter).height);
        
        Rectangle clipRect(130, 220, (**_texIter).width, (**_texIter).height);
        
        renderer.DrawTexture(clipRect, **_texIter);
        
        if(++_texIter == _textures.end())
        {
            _texIter = _textures.begin();
        }
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
    
    if (_clipType == NoClipping) 
    {
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