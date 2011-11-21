#pragma once

#include "SprigResource.h"

class PNGImage : public IResource
{

public:
    PNGImage();
    ~PNGImage();
    
    bool Read(const char * path);
    bool Write(const char * path);
    
    const char* getID();
    
    unsigned char* GetPixelData();
    
    unsigned int GetWidth();
    unsigned int GetHeight();
    unsigned int GetChannels();
    unsigned int GetBitDepth();
    unsigned int GetPixelCount();
    
private:
    
    unsigned char *_data;
    
    unsigned int _imgWidth;
    unsigned int _imgHeight;
    unsigned int _channels;
    unsigned int _bitDepth;
    
};
