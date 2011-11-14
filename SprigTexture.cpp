

#include <OpenGLES/ES1/gl.h>

#include "SprigTexture.h"


// TESTS ///////////////////////////////////////////////////




// IMPLEMENTAION ///////////////////////////////////////////


Texture::~Texture()
{    
    printf("deleting texture: %d\n", textureID);
    
    glDeleteTextures(1, &textureID);
}

Texture::Texture(unsigned int width, unsigned int height, GLubyte *textureData, bool clamp)
{
    _width = width;
    _height = height;
    _clamp = clamp;
    _pixelSize = 4;
    _textureData = NULL;
	
	scrollSpeedX = 0;
	scrollSpeedY = 0;
	scrollOffsetX = 0;
	scrollOffsetY = 0;
    
    SetTextureData(textureData);
}

Texture::Texture(Bitmap &bitmap)
{
    _width = bitmap.GetWidth();
    _height = bitmap.GetHeight();
    _clamp = true;
    _pixelSize = 4;
    _textureData = NULL;
    
    scrollSpeedX = 0;
	scrollSpeedY = 0;
	scrollOffsetX = 0;
	scrollOffsetY = 0;
    
    printf("setting bitmap\n");
    
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
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
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

void Texture::SetTextureData(GLubyte *textureData)
{
    deleteTextureData();
    
    int dataSize = _width * _height * _pixelSize;
    
	_textureData = (GLubyte *)malloc(dataSize);

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
    if(_textureData != NULL)
		free(_textureData);
    
    _textureData = NULL;
}

/*

void Texture::ComputeUV()
{
    GLfloat baseWidth = 256.0;//_parent != NULL ? _parent->width : width;
    GLfloat baseHeight = 256.0;//_parent != NULL ? _parent->height : height;
    
    printf("\nsettings the uv[0] %f    %d   %f", (GLfloat)offsetX / baseWidth , offsetX, baseWidth);
    
    _uv[0] = (GLfloat)offsetX / baseWidth;
    _uv[1] = (GLfloat)offsetY / baseHeight;
    _uv[2] = (GLfloat)offsetX / baseWidth;
    _uv[3] = (GLfloat)(offsetY + height) / baseHeight;
    _uv[4] = (GLfloat)(offsetX + (GLfloat)width) / baseWidth;
    _uv[5] = (GLfloat)offsetY / baseHeight;
    _uv[6] = (GLfloat)(offsetX + (GLfloat)width) / baseWidth;
    _uv[7] = (GLfloat)(offsetY + height) / baseHeight;    
}

void Texture::ComputeUV(Rectangle &clipRect)
{
    GLfloat baseWidth = _parent != NULL ? _parent->width : width;
    GLfloat baseHeight = _parent != NULL ? _parent->height : height;
    
    _uv[0] = (GLfloat)offsetX / baseWidth;
    _uv[1] = (GLfloat)offsetY / baseHeight;
    _uv[2] = (GLfloat)offsetX / baseWidth;
    _uv[3] = (GLfloat)(offsetY + minf((GLfloat)height, clipRect.height)) / baseHeight;
    _uv[4] = (GLfloat)(offsetX + minf((GLfloat)width, clipRect.width)) / baseWidth;
    _uv[5] = (GLfloat)offsetY / baseHeight;
    _uv[6] = (GLfloat)(offsetX + minf((GLfloat)width, clipRect.width)) / baseWidth;
    _uv[7] = (GLfloat)(offsetY + minf((GLfloat)height, clipRect.height)) / baseHeight;   
}

GLfloat* Texture::getUV()
{
    return _uv;
}

*/