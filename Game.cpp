

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
    
    //Bitmap testBitmap = Bitmap(fullPath);
    //Bitmap testBitmap = Bitmap(50, 50, true);
    //testBitmap.GenerateNoise();
    //testBitmap.Fill(0xFF0000FF);
    //Texture testTexture = Texture(testBitmap);
    //_gameObject.getTexture().Apply(testTexture);
    
    
    // MESH TESTS
    GLfloat z = 0.0f;
    
    //Mesh mesh = _gameObject.getMesh();
    _gameObject.getMesh().AddVertex(40, 420, z);
    _gameObject.getMesh().AddVertex(40, 40, z);
    _gameObject.getMesh().AddVertex(280, 420, z);
    _gameObject.getMesh().AddVertex(280, 40, z);    
    
    
    /*
    mesh.AddNormal(0, 0, 1);
    mesh.AddNormal(0, 0, 1);
    mesh.AddNormal(0, 0, 1);
    mesh.AddNormal(0, 0, 1);
     */
    
    
    _gameObject.showBackground = true;
    _gameObject.backgroundColor = Color(1.0, 0.0, 0.0, 1.0);
    
    
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _gameObject.Draw(_renderer);
}