#pragma once

class PNGImage
{

public:
    PNGImage();
    ~PNGImage();
    
    bool Read(const char * filepath);
    bool Write(const char * filepath);
    
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
