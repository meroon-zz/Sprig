#pragma once

#include <vector>
#include <OpenGLES/ES1/gl.h>

#include "Texture.h"

class AssetManager
{

public:
    
    Texture* GetTextureWithKey(const char *key);
    
    std::vector<Texture> textures;
    
    void LoadImage(const char *filename);
    void CreateNoisyTexture(const char * key, const int width, const int height);
};
