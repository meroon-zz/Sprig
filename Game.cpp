
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include "MathUtil.h"
#include "AssetManager.h"

using std::string;
using std::cout;
using std::endl;

EnvironmentData Game::environmentData;
AssetManager Game::assetManager;

void Game::Init(EnvironmentData envData)
{		
    srand ( time(NULL) );
    
    environmentData = envData;
    
    _speed = 2;
    
    _renderer.backgroundColor = Color(0.5, 0.5, 0.5, 1.0);
	_renderer.Setup(environmentData.screenRect, Renderer::Orthographic);

    assetManager.CreateNoisyTexture("noise", 128, 128);
    assetManager.LoadImage("sprite.png");
    
    _testSprite = Sprite();
    _testSprite.rect = Rectangle(64, 64);
}

void Game::Update()
{	
    static float angle = 0;
    const float range = 208;
    const float yOffset = 240;
    
    angle += _speed;
    
	_renderer.Clear();
    
    _testSprite.rect.x = 160 - (_testSprite.rect.width / 2);
    _testSprite.rect.y = yOffset + (sinf(DegreesToRadians(angle)) * range) - (_testSprite.rect.height / 2);    
    _testSprite.Draw(_renderer);
}