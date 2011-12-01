#pragma once

#include <string>

#include "Game.h"





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
    
private:
    
    Game _game;
    static Application *_instance;
    string _basePath;
};


