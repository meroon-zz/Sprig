#pragma once

#include <vector>

#include "Renderer.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "EnvironmentData.h"
#include "AssetManager.h"

using std::vector;

class Game
{
public:
    
    static EnvironmentData environmentData;
    static AssetManager assetManager;
    
	void Init(EnvironmentData data);
	void Update();
	
    
private:
	Renderer _renderer;
    vector<Sprite> _sprites;
    Sprite _testSprite;
    int _speed;
};
