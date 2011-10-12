
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
    
    _renderer.backgroundColor = Color(1.0, 1.0, 1.0, 1.0);
	_renderer.Setup(environmentData.screenRect, Renderer::Orthographic);

    string spritePath("run_test.png");
    string xmlPath("run_test.xml");
    
    assetManager.LoadImage(spritePath);
    assetManager.LoadXMLFile(xmlPath);
    
    Texture* texture = assetManager.GetTexture(spritePath);
    texture->ComputeUV();

    
    _testSprite = Sprite();
    _testSprite.rect = Rectangle(64, 64);
    _testSprite.Init();
    _testSprite.ApplyTexture(texture, Sprite::Clipping);
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _testSprite.Draw(_renderer);
}