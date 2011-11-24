#pragma once


#include "SprigRenderer.h"
#include "SprigGameObject.h"
#include "SprigSprite.h"
#include "SprigInput.h"

#include "EnvironmentData.h"

class Game
{
    
public:
    
    Game() : _accel(0), _velocity(0), _gravity(0.98), _isJumping(true) {};
    
    static EnvironmentData environmentData;
    
	void Init(EnvironmentData data);
	void Update();
    
    Input input;
    
private:
	Renderer _renderer;
    AnimatedSprite _sprite;
    Sprite _ground;
    
    float _accel , _velocity, _gravity;
    bool _isJumping;
};
