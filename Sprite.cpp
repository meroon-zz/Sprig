//
//  Sprite.cpp
//  SpriEng
//
//  Created by Cam Warnock on 11-09-22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sprite.h"
#include "Game.h"

#include <string>

using std::string;

void Sprite::Init()
{
    string configKey("run_test.xml");
    string textureKey("run_test.png");
    
    mainTexture = Game::assetManager.GetTexture(textureKey);
    animatedTextures = Game::assetManager.GetTextures(configKey, textureKey);
    textureItr = animatedTextures.begin();
}

void Sprite::Draw(Renderer renderer)
{    
    //renderer.DrawRect(rect, Color(0.0, 1.0, 0.5, 1.0));
    
    //string spritesheetKey("spritesheet.png");
    
    //Texture *texture = Game::assetManager.GetTexture(spritesheetKey);
    
    //Texture texture("sprite", 64, 64);
    //texture.name = 2;
    
    Texture *texture = *textureItr;
    
    renderer.DrawTexture(rect.x, rect.y, *texture, mainTexture->width, mainTexture->height);
    
    if(++textureItr == animatedTextures.end())
    {
        textureItr = animatedTextures.begin();
    }
}