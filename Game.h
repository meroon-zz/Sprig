#pragma once


#include "SprigRenderer.h"
#include "SprigGameObject.h"
#include "SprigSprite.h"

#include "EnvironmentData.h"

class Game
{
    
public:
    
    static EnvironmentData environmentData;
    
	void Init(EnvironmentData data);
	void Update();
	    
private:
	Renderer _renderer;
    AnimatedSprite _sprite;
    Sprite _ground;
    Sprite _test;
};
