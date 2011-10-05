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
    //renderer.DrawRect(rect, Color(0.0, 1.0, 0.5, 1.0));
    
    Texture *texture = Game::assetManager.GetTextureWithKey("sprite.png");
    
    //Texture texture("sprite", 64, 64);
    //texture.name = 2;
    
    renderer.DrawTexture(rect.x, rect.y, *texture);
}