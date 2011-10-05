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


#include <cstdio>
#include <iostream>
#include <string>

Texture* AssetManager::GetTextureWithKey(const char *key)
{
    std::vector<Texture>::iterator itr;
    
    for (itr = textures.begin(); itr != textures.end(); ++itr) 
    {
        if (itr->key == key) 
        {
            return &(*itr);  
        }
    }
    
    return NULL;    
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

void LoadPNG(GLubyte *imageData, unsigned int &width, unsigned& height)
{
    
}

void AssetManager::LoadImage(const char *filename)
{
    Texture texture(filename);
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    int bitDepth, colourType;
    
    FILE *pngFile = fopen(std::string(Game::environmentData.basePath + "/" + filename).c_str(), "rb");
    
    if(!pngFile)
        return;
    
    png_byte sig[8];
    
    fread(&sig, 8, sizeof(png_byte), pngFile);
    rewind(pngFile);//so when we init io it won't bitch
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
    
    png_init_io(png_ptr, pngFile);
    
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
    
    
    png_get_IHDR(png_ptr, info_ptr, &texture.width, &texture.height,
                 &bitDepth, &colourType, NULL, NULL, NULL);
    
    int components = GetTextureInfo(colourType);
    
    if(components == -1)
    {
        if(png_ptr)
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return;
    }
    
    GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (texture.width * texture.height * components));
    
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * texture.height);
    
    for(int i = 0; i < texture.height; ++i)
        row_pointers[i] = (png_bytep)(pixels + (i * texture.width * components));
    
    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, NULL);
    
    
    // make it
    glGenTextures(1, &texture.name);
    // bind it
    glBindTexture(GL_TEXTURE_2D, texture.name);
    
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
    
    glTexImage2D(GL_TEXTURE_2D, 0, glcolours, texture.width, texture.height, 0, glcolours, GL_UNSIGNED_BYTE, pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    fclose(pngFile);
    free(row_pointers);
    free(pixels);
    
    textures.push_back(texture);
}

void AssetManager::CreateNoisyTexture(const char * key, const int width, const int height)
{     
    Texture texture(key, width, height);
    const unsigned int components = 4;
    
    
    GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (texture.width * texture.height * components));
    GLubyte *pitr1 = pixels;    
    GLubyte *pitr2 = pixels + (texture.width * texture.height * components);
    
    while (pitr1 != pitr2) {
        
        *pitr1 = rand() * 0xFF;
        *(pitr1 + 1) = rand() * 0xFF;
        *(pitr1 + 2) = rand() * 0xFF;
        *(pitr1 + 3)  = 0xFF;
        
        pitr1 += 4;
    }
    
    glEnable(GL_TEXTURE_2D);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glGenTextures(1, &texture.name);    
    glBindTexture(GL_TEXTURE_2D, texture.name); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    free(pixels);
    
    printf("Created texture with key: %s  name: %d  error: %x\n", texture.key, texture.name, glGetError());
    
    textures.push_back(texture);
}