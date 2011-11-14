#pragma once

#include <OpenGLES/ES1/gl.h>
#include <string>
#include <vector>

#include "SprigBitmap.h"
#include "SprigRectangle.h"

class Texture
{

public:
    
    Texture() : _textureData(NULL) , _pixelSize(4){};
    ~Texture();
    
    Texture(unsigned int width, unsigned int height, GLubyte *textureData, bool clamp);
    Texture(Bitmap &bitmap); 
    
    GLuint textureID;
    GLuint frameBufferID;
    
    float scrollSpeedX;
    float scrollSpeedY;
    float scrollOffsetX;
    float scrollOffsetY;
    
    unsigned int GetWidth();
    unsigned int GetHeight();
    
    void SetTextureData(GLubyte *textureData);
    unsigned char * GetTextureData();
    
private:

    void rebuildFromTextureData();
    void deleteTextureData();
    
    GLubyte *_textureData;
    unsigned int _width;
    unsigned int  _height;
    bool _clamp;
    int _pixelSize;
    
};  