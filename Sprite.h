#pragma once

#include "Color.h"
#include "Renderer.h"

#include <vector>

class Sprite
{
    public:
    
        enum TextureClipType{
            Clipping, NoClipping
        };
    
        Rectangle rect;
        Color backgroundColor;
    
        virtual void Init();
        virtual void Draw(Renderer renderer);
        void ApplyTexture(Texture *texture, TextureClipType clipType);
        void RemoveTexture();
    
    private:
        
        Texture *_texture;
        TextureClipType _clipType;
        Rectangle _clipRect;
        std::vector<Texture *> _textures;
        std::vector<Texture *>::iterator _texIter;
};
