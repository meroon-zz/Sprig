#pragma once

#include "SprigResource.h"

class PNGImage : public Resource
{

public:
    
    PNGImage() : Resource(), _data(NULL)  {};
    ~PNGImage();
    
    bool Read(const char * path);
    bool Write(const char *path);
    
    unsigned char* GetPixelData();
    
    unsigned int GetWidth();
    unsigned int GetHeight();
    unsigned int GetChannels();
    unsigned int GetBitDepth();
    unsigned int GetPixelCount();
    
private:
    
    bool load(const char *path);
    
    unsigned char *_data;
    
    unsigned int _imgWidth;
    unsigned int _imgHeight;
    unsigned int _channels;
    unsigned int _bitDepth;
    
};
