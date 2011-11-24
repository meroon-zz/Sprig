#pragma once

#include <vector>

#include "SprigTexture.h"
#include "tinyxml.h"



class SpriteAtlas
{
  
public:
    
    SpriteAtlas();
    ~SpriteAtlas();
    
    bool LoadSheet(const char *path);
    void Reset();
    Rectangle* CurrentRect();
    Rectangle* NextRect();
    void setRectIndex(int index);
    
    Texture texture;

    
    
private:
    
 
    
    std::vector<Rectangle *> _clipRects;
    std::vector<Rectangle *>::iterator _clipRectPtr;
};