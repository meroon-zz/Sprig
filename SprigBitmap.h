#pragma once

#include <string>



/*
 This class is used to deal with bitmap data. 
 */
class Bitmap {

public:

    Bitmap(unsigned int width, unsigned int height, bool transparent);
    Bitmap(std::string& filepath); 
    
    
    Bitmap();
    ~Bitmap();
    
    unsigned char * GetBitmapData();

    bool IsLoaded();

    void Fill(unsigned int color);
    void GenerateNoise();
    void PrintData();

    bool LoadPNG(std::string& filepath);
    
    unsigned int GetWidth();
    unsigned int GetHeight();

private:

    void PrintData(unsigned char *data, unsigned int count);
    void createEmpty(unsigned int width, unsigned int height);
    void setTransparency(bool transparent);

    unsigned int _pixelSize;
    unsigned char *_bitmapData;
    unsigned int _width;
    unsigned int _height;
    bool _transparent;
    bool _loaded;
    
};