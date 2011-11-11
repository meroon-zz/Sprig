
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include "MathUtil.h"
#include "AssetManager.h"
#include "Bitmap.h"

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

    /*string spritePath("run_test.png");
    string xmlPath("run_test.xml");
    
    assetManager.LoadImage(spritePath);
    assetManager.LoadXMLFile(xmlPath);
    
    Texture* texture = assetManager.GetTexture(spritePath);
    texture->ComputeUV();*/
    
    Bitmap square = Bitmap(200, 200, true);

    
    _testSprite = Sprite();
    _testSprite.rect = Rectangle(64, 64);
    _testSprite.Init();
    _testSprite.ApplyTexture(texture, Sprite::NoClipping);
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _testSprite.Draw(_renderer);
}