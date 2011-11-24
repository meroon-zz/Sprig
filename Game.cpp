

#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "MathUtil.h"
#include "SprigSpriteAtlas.h"
#include "Constants.h"

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
    
    
    _sprite.setPosition(60, 300);
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
    
    
	
    
    trace("the y: %f   velocity: %f\n", _sprite._y, _velocity);
    
    
    //gameplay
    
    if (_isJumping)
    {
        _sprite.setPosition(_sprite._x, _sprite._y + _velocity);
        _velocity += _gravity;
        
        if(_sprite._y > 345)
        {
            _sprite.setPosition(_sprite._x, 345);
            _isJumping = false;
        }
    }
    else
    {
        _sprite.Update();
    }
    
    if(input.GetPressed() && !_isJumping)
    {
        trace("mouse was pressed: %f, %f", input.GetLastX(), input.GetLastY());
        
        _sprite.GotoFrame(1);
        _isJumping = true;
        _velocity = -14;
    }
    
    input.Reset();
    
    
    //draw
    
    _renderer.Clear();
    
    _ground.Draw(_renderer);
    _sprite.Draw(_renderer);
    
    
}