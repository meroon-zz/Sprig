#pragma once

#include <vector>
#include <OpenGLES/ES1/gl.h>
#include <string>
#include <map>

#include "Texture.h"
#include "tinyxml.h"

class AssetManager
{

public:
    
    
    Texture* GetTexture(std::string &key);
    std::vector<Texture *>GetTextures(std::string &configKey, std::string &textureKey);
    
    TiXmlDocument* GetXMLFile(std::string &key);
    
    std::map<std::string, TiXmlDocument*> xmlFiles;
    std::map<std::string, Texture *> textureFiles;
    
    void LoadXMLFile(std::string &filename);
    void LoadImage(std::string &filename);
    void CreateNoisyTexture(std::string &key, const int width, const int height);
    
private:
    
    void LoadPNG(GLubyte *imageData, unsigned int &width, unsigned &height); 
    Texture* ParseTextureForElement(GLuint textName, TiXmlElement *element);
};
