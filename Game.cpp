

#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "MathUtil.h"
#include "SprigSpriteAtlas.h"


using std::string;
using std::cout;
using std::endl;

EnvironmentData Game::environmentData;


void Game::Init(EnvironmentData envData)
{		
    srand ( time(NULL) );
    
    environmentData = envData;
    
    _renderer.backgroundColor = Color(1.0, 1.0, 1.0, 1.0);
	_renderer.Setup(environmentData.screenRect, Renderer::Orthographic);

    
    string imagePath = Game::environmentData.basePath + "/run_test.png"; 
    string xmlPath = Game::environmentData.basePath + "/run_test.xml";
  
    
    Bitmap bitmap = Bitmap(imagePath);
    _test.AddBitmap(bitmap);
    
    _test.setPosition(0, 0);
    _test.setSize(bitmap.GetWidth(), bitmap.GetHeight());
    
    
    _sprite.setPosition(60, 320);
    _sprite.LoadSheet(xmlPath, imagePath);
    _sprite.showBackground = false;
    _sprite.backgroundColor = Color(1.0, 0.0, 0.0, 1.0);
    
    _ground.showBackground = true;
    _ground.backgroundColor = Color(1.0, 0.0, 0.0, 1.0);
    _ground.setPosition(0, 390);
    _ground.setSize(320, 10);
   
}

void Game::Update()
{	    
	_renderer.Clear();
    
    _sprite.Update();
    _sprite.Draw(_renderer);
    
    //_test.Draw(_renderer);
    
    _ground.Draw(_renderer);
}