

#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "MathUtil.h"

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

    Bitmap testBitmap = Bitmap(50, 50, true);
    testBitmap.GenerateNoise();
    //testBitmap.Fill(0xFF0000FF);
    
    //_gameObject.showBackground = true;
    //_gameObject.backgroundColor = Color(1.0, 0.0, 0.0, 1.0);
    _gameObject.width = 200;
    _gameObject.height = 200;
    _gameObject.x = 30;
    _gameObject.y = 30;
    
    _gameObject.texture = new Texture(testBitmap);
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _gameObject.Draw(_renderer);
}