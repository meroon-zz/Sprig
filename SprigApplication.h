#pragma once

#include <string>

#include "Game.h"
#include "SprigScreen.h"


using std::string;

class Application
{

public: 
    
    Application(){};
    
    static Application* getInstance();
    
    void start();
    void pause();
    void stop();
    void update();
    
    string& getBasePath();
    Screen screen;
    
private:
    
    Game _game;
    static Application *_instance;
    string _basePath;
};


