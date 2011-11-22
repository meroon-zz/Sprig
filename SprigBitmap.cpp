//
//  Bitmap.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-10.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigFileSystem.h"
#include "SprigBitmap.h"
#include "MathUtil.h"
#include "SprigImageEncoding.h"
#include "SprigResource.h"

Bitmap::Bitmap()
{
    _bitmapData = NULL;
}

Bitmap::~Bitmap()
{
    delete _bitmapData;
}

Bitmap::Bitmap(std::string& filepath)
{
    _bitmapData = NULL;
    
    setTransparency(true);
    
    if(LoadPNG(filepath))
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
    _bitmapData = NULL;
    
    setTransparency(transparent);
    
    createEmpty(width, height);
}

void Bitmap::Fill(unsigned int color)
{    
    unsigned int *bitmapData32 = (unsigned int *)_bitmapData;
    unsigned int pixelCount = _width * _height;
    
    for (int i = 0; i < pixelCount; i++) 
    {
        bitmapData32[i] = color;
    }
}

void Bitmap::GenerateNoise()
{    
    unsigned int count = _width * _height * _pixelSize;
    
    for (int i = 0; i < count; i += _pixelSize) 
    {
        int r = rand() % 0xFF;
        int g = rand() % 0xFF;
        int b = rand() % 0xFF;
        
        _bitmapData[i] =  r;   
        _bitmapData[i + 1] = g;
        _bitmapData[i + 2] = b;
        _bitmapData[i + 3] = 0xFF;        
    }
    
}

bool Bitmap::LoadPNG(std::string &filepath)
{
    _loaded = false;
    
    PNGImage *image = (PNGImage *)ResourceManager::getInstance()->getResource(filepath.c_str(), ResourceManager::ResourceTypePNGImage);
    
    if(image)
    {        
        _width = image->GetWidth();
        _height = image->GetHeight();
        _pixelSize = image->GetChannels();   
        _bitmapData = image->GetPixelData();    
        _loaded = true;
    }
    
    return _loaded;
}

void Bitmap::createEmpty(unsigned int width, unsigned int height)
{
    if (_bitmapData != NULL) 
    {
        free(_bitmapData);
    }
    
    _bitmapData = (unsigned char *)malloc(width * height * _pixelSize);
    _width = width;
    _height = height;
    
    Fill(0);
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

bool Bitmap::IsLoaded()
{
    return _loaded;
}

unsigned char* Bitmap::GetBitmapData()
{
    return _bitmapData;
}

unsigned int Bitmap::GetWidth()
{
    return _width;
}

unsigned int Bitmap::GetHeight()
{
    return _height;
}

void Bitmap::PrintData()
{
    PrintData(_bitmapData, _width * _height * _pixelSize);
}

void Bitmap::PrintData(unsigned char * data, unsigned int count)
{    
    for (int i = 0; i < count; ++i) 
    {            
        if (i % 4 == 0) {
            printf("\n[%d] ", i / 4);
        }
        
        printf("%x ", data[i]);
        
    }
}