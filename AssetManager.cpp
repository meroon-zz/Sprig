//
//  AssetManager.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-09-25.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "AssetManager.h"
#include "Game.h"
#include "png.h"
#include "MathUtil.h"
#include "SprigFileSystem.h"


#include <cstdio>
#include <iostream>



using std::string;

Texture* AssetManager::GetTexture(std::string &key)
{
    std::map<std::string, Texture*>::iterator itr;
    
    itr = textureFiles.find((const std::string)key);
    
    if(itr != textureFiles.end())
    {
        return itr->second;
    }
    
    return NULL;    
}

TiXmlDocument* AssetManager::GetXMLFile(std::string &key)
{
    std::map<std::string, TiXmlDocument*>::iterator itr;
    
    itr = xmlFiles.find((const std::string)key);
    
    if(itr != xmlFiles.end())
    {        
        return itr->second;
    }
    
    return  NULL;    
}

std::vector<Texture *> AssetManager::GetTextures(std::string &configKey, std::string &textureKey)
{
    std::vector<Texture *> aniTextures;
    TiXmlDocument *doc = GetXMLFile(configKey);
    Texture *mainTexture = GetTexture(textureKey);
    Texture *subTexture;
    
    doc->Print(stdout);
    
    TiXmlNode *atlasNode = doc->FirstChild("TextureAtlas");
    TiXmlElement *atlas = atlasNode->ToElement();
    TiXmlElement *textureElement;
    
    for(textureElement = atlas->FirstChildElement(); textureElement; textureElement = textureElement->NextSiblingElement())
    {        
        subTexture = ParseTextureForElement(mainTexture->textureName, textureElement);
        mainTexture->AddSubTexture(subTexture);
        
        printf("the name of the texture: %d", subTexture->textureName);
        
        aniTextures.push_back(subTexture);
    }
    
    return aniTextures;
}

Texture* AssetManager::ParseTextureForElement(GLuint texName, TiXmlElement *element)
{
    string key = string(element->Attribute("name"));
    
    Texture *texture = new Texture(key, texName);
    element->QueryIntAttribute("x", &texture->offsetX);
    element->QueryIntAttribute("y", &texture->offsetY);
    element->QueryUnsignedAttribute("height", &texture->width); //height and width are swapped because of a bug in zwoptex exporting sparrow XML
    element->QueryUnsignedAttribute("width", &texture->height);
    
    printf("Texture  key: %s  x: %d  y: %d  width: %d  height: %d\n", texture->key.c_str(), texture->offsetX, texture->offsetY, texture->width, texture->height);
    return texture;
}



int GetTextureInfo(int ColourType)
{
    int ret;
    switch(ColourType)
    {
        case PNG_COLOR_TYPE_GRAY:
            ret = 1;
            break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            ret = 2;
            break;
        case PNG_COLOR_TYPE_RGB:
            ret = 3;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            ret = 4;
            break;
        default:
            ret = -1;//fucked
    };
    return ret;
};

void AssetManager::LoadXMLFile(std::string &filename)
{
    string  fullPath = Game::environmentData.basePath + "/" + filename;
    
    TiXmlDocument *doc = new TiXmlDocument(fullPath.c_str());
    
    bool loadOkay = doc->LoadFile();
    
    if ( !loadOkay )
    {
        printf( "Could not load test file '%s'. Error='%s'. Exiting.\n", fullPath.c_str(), doc->ErrorDesc() );
        exit( 1 );
    }
    
    //doc->Print( stdout );  
    
    xmlFiles.insert(std::pair<std::string, TiXmlDocument*>(filename, doc));
}


void AssetManager::LoadPNG(GLubyte *imageData, unsigned int &width, unsigned& height)
{
    
}

void AssetManager::LoadImage(std::string &filename)
{
    Texture *texture = new Texture(filename);
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    int bitDepth, colourType;
    
    string  fullPath = Game::environmentData.basePath;
    fullPath += "/";
    fullPath += filename;
    
    SprigFile *pngFile = SprigFileSystem::open(fullPath.c_str(), "rb");
    
    if(!pngFile)
        return;
    
    png_byte sig[8];
    
    fread(&sig, 8, sizeof(png_byte), pngFile->file);
    rewind(pngFile->file);//so when we init io it won't bitch
    if(!png_check_sig(sig, 8))
        return;
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);
    
    if(!png_ptr)
        return;
    
    if(setjmp(png_jmpbuf(png_ptr)))
        return;
    
    info_ptr = png_create_info_struct(png_ptr);
    
    if(!info_ptr)
        return;
    
    png_init_io(png_ptr, pngFile->file);
    
    png_read_info(png_ptr, info_ptr);
    
    bitDepth = png_get_bit_depth(png_ptr, info_ptr);
    
    colourType = png_get_color_type(png_ptr, info_ptr);
    
    if(colourType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    
    /*if(colourType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
     png_set_gray_1_2_4_to_8(png_ptr);*/
    
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    
    if(bitDepth == 16)
        png_set_strip_16(png_ptr);
    else if(bitDepth < 8)
        png_set_packing(png_ptr);
    
    png_read_update_info(png_ptr, info_ptr);
    
    
    png_get_IHDR(png_ptr, info_ptr, &texture->width, &texture->height,
                 &bitDepth, &colourType, NULL, NULL, NULL);
    
    int components = GetTextureInfo(colourType);
    
    if(components == -1)
    {
        if(png_ptr)
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return;
    }
    
    GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (texture->width * texture->height * components));
    
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * texture->height);
    
    for(int i = 0; i < texture->height; ++i)
        row_pointers[i] = (png_bytep)(pixels + (i * texture->width * components));
    
    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, NULL);
    
    
    // make it
    glGenTextures(1, &texture->textureName);
    // bind it
    glBindTexture(GL_TEXTURE_2D, texture->textureName);
    
    GLuint glcolours;
    
    switch (components) {
        case 1: 
            glcolours = GL_LUMINANCE;
            break;
        case 2: 
            glcolours = GL_LUMINANCE_ALPHA;
            break;
        case 3: 
            glcolours = GL_RGB;
            break;
        case 4: 
            glcolours = GL_RGBA;
            break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, glcolours, texture->width, texture->height, 0, glcolours, GL_UNSIGNED_BYTE, pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    delete pngFile;
    free(row_pointers);
    free(pixels);
    
    textureFiles.insert(std::pair<std::string, Texture*>(filename, texture));
}

void AssetManager::CreateNoisyTexture(std::string &key, const int width, const int height)
{     
    Texture *texture = new Texture(key, 0, width, height);
    const unsigned int components = 4;
    
    
    GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (texture->width * texture->height * components));
    GLubyte *pitr1 = pixels;    
    GLubyte *pitr2 = pixels + (texture->width * texture->height * components);
    
    while (pitr1 != pitr2) {
        
        *pitr1 = rand() * 0xFF;
        *(pitr1 + 1) = rand() * 0xFF;
        *(pitr1 + 2) = rand() * 0xFF;
        *(pitr1 + 3)  = 0xFF;
        
        pitr1 += 4;
    }
    
    glEnable(GL_TEXTURE_2D);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glGenTextures(1, &texture->textureName);    
    glBindTexture(GL_TEXTURE_2D, texture->textureName); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    free(pixels);
    
    printf("Created texture with key: %s  name: %d  error: %x\n", texture->key.c_str(), texture->textureName, glGetError());
    
    textureFiles.insert(std::pair<std::string, Texture*>(key, texture));
}