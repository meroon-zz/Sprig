#pragma once

#include <OpenGLES/ES1/gl.h>
#include <string>
#include <vector>

#include "Rectangle.h"

class Texture
{
  public:
    
    Texture(std::string &key) : textureName(0), offsetX(0), offsetY(0), width(1), height(1), _parent(NULL) { this->key = key; }
    Texture(std::string &key, GLuint textureName): offsetX(0), offsetY(0), width(1), height(1), _parent(NULL) 
    {
        this->key = key; this->textureName = textureName; 
    }
    
    Texture(std::string &key, GLuint textureName, int width, int height) : offsetX(0), offsetY(0), _parent(NULL)
    {
        this->textureName = textureName;
        this->key = key;
        this->width = width;
        this->height = height;
    }
    
    std::string key;
    
    int offsetX;
    int offsetY;
    unsigned int width;
    unsigned int height;
    
    GLuint textureName;
    
    Texture *getParent();
    void setParent(Texture *parent);
    
    void AddSubTexture(Texture *subTexture);
    void RemoveSubTexture(Texture *subTexture);
    bool ContainsSubTexture(Texture *subTexture); 
    void ComputeUV();
    void ComputeUV(Rectangle &clipRect);
    GLfloat *getUV();
    
private:
    
    Texture *_parent;
    GLuint _name;
    std::vector<Texture *> _textures;
    GLfloat _uv[8];
};  