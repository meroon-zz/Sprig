#pragma once

#include <OpenGLES/ES1/gl.h>
#include <string>
#include <vector>

#include "SprigBitmap.h"
#include "SprigRectangle.h"

class Texture
{

public:
    
    Texture();
    ~Texture();
    
    Texture(unsigned int width, unsigned int height, GLubyte *textureData, bool clamp);
    Texture(Bitmap &bitmap); 
    
    GLuint textureID;
    GLuint frameBufferID;
    
    float scrollSpeedX;
    float scrollSpeedY;
    float offsetX;
    float offsetY;
    
    unsigned int GetWidth();
    unsigned int GetHeight();
    bool GetClamp();
    unsigned int GetPixelSize();
    
    void SetTextureData(GLubyte *textureData);
    unsigned char * GetTextureData();
    
    void Apply(Texture &texture);
    
private:

    void init();
    void rebuildFromTextureData();
    void deleteTextureData();
    
    GLubyte *_textureData;
    unsigned int _width;
    unsigned int  _height;
    bool _clamp;
    int _pixelSize;
    
};  