//
//  Bitmap.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Bitmap.h"


Bitmap::Bitmap()
{
    _bitmapData = NULL;
}

Bitmap::~Bitmap()
{
    if (_bitmapData != NULL)
    {
        free(_bitmapData);
    }
}

Bitmap::Bitmap(const std::string& filepath)
{
    setTransparency(true);
    _loaded = false;
    
    if(loadPNG(filepath))
    {
        _loaded = true;
    }
    else
    {
        printf("Error: failed to load bitmap at path %s", filepath.c_str());
    }
}

Bitmap::Bitmap(unsigned int width, unsigned int height, bool transparent)
{
    setTransparency(transparent);
    
    createEmpty(width, height);
}

void Bitmap::fill(unsigned int color)
{
    unsigned int *bitmapData32 = (unsigned int *)_bitmapData;
    unsigned int pixelCount = _width * _height;
    
    for (int i = 0; i < pixelCount; i++) 
    {
        bitmapData32[i] = color;
    }
}

bool Bitmap::loadPNG(std::string const &filepath)
{
    return true;
}

void Bitmap::createEmpty(unsigned int width, unsigned int height)
{
    if (_bitmapData != NULL) 
    {
        free(_bitmapData);
    }
    
    _bitmapData = (char *)malloc(width * height * _pixelSize);
    _width = width;
    _height = height;
    
    fill(0);
}

void Bitmap::setTransparency(bool transparent)
{
    _transparent = transparent;
    
    if(_transparent)
    {
        _pixelSize = 4;
    }
    else
    {
        _pixelSize = 3;
    }
}

bool Bitmap::isLoaded()
{
    return _loaded;
}