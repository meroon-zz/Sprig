#pragma once


#include "SprigRenderer.h"
#include "SprigGameObject.h"

#include "EnvironmentData.h"

class Game
{
    
public:
    
    static EnvironmentData environmentData;
    
	void Init(EnvironmentData data);
	void Update();
	    
private:
	Renderer _renderer;
    GameObject _gameObject;
};
