

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

    
    string fullPath = Game::environmentData.basePath;
    fullPath += "/";
    fullPath += "sprite.png";
    
    // BITMAP TESTS
    
    Bitmap testBitmap = Bitmap(fullPath);
    //Bitmap testBitmap = Bitmap(50, 50, true);
    //testBitmap.GenerateNoise();
    //testBitmap.Fill(0xFF0000FF);
    
    
    
    
    
    _sprite.AddBitmap(testBitmap);
    _sprite.setPosition(20, 20);
    _sprite.setSize(64, 64);
    
    //_sprite.showBackground = false;
    //_sprite.backgroundColor = Color(1.0, 0.0, 0.0, 1.0);
    
    
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _sprite.Draw(_renderer);
}