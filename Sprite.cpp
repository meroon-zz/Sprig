//
//  Sprite.cpp
//  SpriEng
//
//  Created by Cam Warnock on 11-09-22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sprite.h"
#include "Game.h"

void Sprite::Draw(Renderer renderer)
{    
    Texture *texture = Game::assetManager.GetTextureWithKey("noise");
    
    renderer.DrawTexture(rect.x, rect.y, *texture);
}