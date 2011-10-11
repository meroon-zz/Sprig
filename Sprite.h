#pragma once

#include "Color.h"
#include "Renderer.h"

#include <vector>

class Sprite
{
    public:
    
        Rectangle rect;
        Color backgroundColor;

        void Init();
        void Draw(Renderer renderer);
    
    private:
    
        std::vector<Texture *> animatedTextures;
        std::vector<Texture *>::iterator textureItr;
        Texture *mainTexture;
};
