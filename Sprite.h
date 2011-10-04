#pragma once

#include "Color.h"
#include "Renderer.h"

class Sprite
{
    public:
    
        Rectangle rect;
        Color backgroundColor;

        void Draw(Renderer renderer);
};
