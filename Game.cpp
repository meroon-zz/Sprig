

#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "MathUtil.h"

#include "SprigXMLFile.h"
#include "SprigResource.h"

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

    
    string fullPath = Game::environmentData.basePath + "/run_test.png";    
    Bitmap testBitmap = Bitmap(fullPath);    
    _sprite.AddBitmap(testBitmap);
    _sprite.setPosition(20, 20);
    _sprite.setSize(64, 64);  
    
    
    string xmlpath = Game::environmentData.basePath + "/run_test.xml";
    
    XMLFile *xmlFile = (XMLFile *)ResourceManager::getInstance()->getResource(xmlpath.c_str(), ResourceManager::ResourceTypeXML);
    
    if(xmlFile != NULL)
    {
        xmlFile->document->Print();
    }
    
    
}

void Game::Update()
{	    
	_renderer.Clear();
       
    _sprite.Draw(_renderer);
}