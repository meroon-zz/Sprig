#include "SprigApplication.h"
#include "SprigApplicationUpdate.h"
#include "SprigScreen.h"
#include "Game.h"

Application *Application::_instance = NULL;

Application* Application::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new Application;
    }
    
    return _instance;
}

void Application::start()
{
    _basePath = std::string([[[NSBundle mainBundle] bundlePath] UTF8String]); 
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    
    Screen::getInstance()->dimensions = Rectangle(screenBounds.size.width, screenBounds.size.height);
    
    _game.Init();
    
    [[ApplicationUpdate currentApplicationUpdate] setInterval:60];
    [[ApplicationUpdate currentApplicationUpdate] startMainLoop];
}

void Application::pause()
{
    
}

void Application::stop()
{
    
}

void Application::update()
{
    _game.Update();
}

string& Application::getBasePath()
{
    return _basePath;
}