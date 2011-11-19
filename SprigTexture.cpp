

#include <OpenGLES/ES1/gl.h>

#include "SprigTexture.h"


// TESTS ///////////////////////////////////////////////////




// IMPLEMENTAION ///////////////////////////////////////////


Texture::Texture()
{
    init();
}

void Texture::init()
{
    _width = 0;
    _height = 0;
    _clamp = true;
    _pixelSize = 4;
    _textureData = NULL;
	
	scrollSpeedX = 0;
	scrollSpeedY = 0;
	offsetX = 0;
	offsetY = 0;
}

Texture::~Texture()
{    
    //printf("deleting texture: %d\n", textureID);
    
    //glDeleteTextures(1, &textureID);
}

Texture::Texture(unsigned int width, unsigned int height, GLubyte *textureData, bool clamp)
{
    init();
    
    _width = width;
    _height = height;
    _clamp = clamp;
    
    SetTextureData(textureData);
}

Texture::Texture(Bitmap &bitmap)
{
    init();
    
    _width = bitmap.GetWidth();
    _height = bitmap.GetHeight();
    
    SetTextureData((GLubyte *)bitmap.GetBitmapData());
}

void Texture::rebuildFromTextureData()
{    
    glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    printf("generated texture: %d\n", textureID);
	
    if(_clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	}
    
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
	if(_textureData)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _textureData);
}


unsigned int Texture::GetWidth()
{
    return _width;
}

unsigned int Texture::GetHeight()
{
    return _height;
}

bool  Texture::GetClamp()
{
    return _clamp;
}

unsigned int Texture::GetPixelSize()
{
    return _pixelSize;
}

void Texture::SetTextureData(GLubyte *textureData)
{
    deleteTextureData();
    
    int dataSize = _width * _height * _pixelSize;
    
	_textureData = new GLubyte[dataSize];

	if(textureData)
        memcpy(_textureData, textureData, dataSize);
	else
		memset(_textureData, 0, dataSize);
    
    rebuildFromTextureData();
}

unsigned char* Texture::GetTextureData()
{
    return _textureData;
}

void Texture::deleteTextureData()
{
    delete [] _textureData;
    
    _textureData = NULL;
}


void Texture::Apply(Texture &texture)
{
    _width = texture.GetWidth();
    _height = texture.GetHeight();
    _clamp = texture.GetClamp();
    _pixelSize = texture.GetPixelSize();
    _textureData = texture.GetTextureData();
	
    textureID = texture.textureID;
	scrollSpeedX = texture.scrollSpeedX;
	scrollSpeedY = texture.scrollSpeedY;
	offsetX = texture.offsetX;
	offsetY = texture.offsetY;
}

