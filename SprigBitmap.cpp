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
    
    /*
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    png_byte bitDepth, colorType;
    int width, height, pixelCount;
    
    //load the file from the file system
    SprigFile *pngFile = SprigFileSystem::open(filepath.c_str(), "rb");
    
    if(!pngFile)
    {
        printf("[Bitmap::LoadPNG] File %s could not be opened for reading", filepath.c_str());
        return false;
    }
    
    
    //read the png header to see if this is a valid png
    png_byte header[8];
    
    fread(&header, 8, sizeof(png_byte), pngFile->file);
    rewind(pngFile->file);//rewind to prepare for reading the file
    
    if(!png_check_sig(header, 8))
    {
        printf("[Bitmap::LoadPNG] File %s is not recognized as a PNG file", filepath.c_str());
        return false;
    }
    
    
    //intialize our struct
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);
    
    if(!png_ptr)
    {
        printf("[Bitmap::LoadPNG] png_create_read_struct failed");
        return false;
    }
    
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[Bitmap::LoadPNG] error during init_io");
        return false;
    }
    
    
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        printf("[Bitmap::LoadPNG] png_create_info_struct failed");
        return false;
    }
    
    
    png_init_io(png_ptr, pngFile->file);
    
    png_read_info(png_ptr, info_ptr);
    
    
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    colorType = png_get_color_type(png_ptr, info_ptr);
    bitDepth = png_get_bit_depth(png_ptr, info_ptr);
    
    printf("width: %d   height: %d   colorType: %d  bitDepth: %d", width, height, colorType, bitDepth);
    
    
    if(colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    
    //if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    
    if(bitDepth == 16)
        png_set_strip_16(png_ptr);
    else if(bitDepth < 8)
        png_set_packing(png_ptr);
    
    png_read_update_info(png_ptr, info_ptr);
    
    
    //setup our memory to read the image
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y=0; y<height; y++)
    {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
        
        printf("row bytes: %lu\n", png_get_rowbytes(png_ptr,info_ptr));
    }
    
    PrintData((unsigned char *)row_pointers, width * height * 4);
    
    //read the image data
    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, NULL); 
    
    printf("\n--------------------\n");
    
    PrintData((unsigned char *)row_pointers, width * height * 4);
    
    //copy the data into our bitmap data
    pixelCount = width * height * 4;
    _bitmapData = (unsigned char *)malloc(pixelCount);
    memcpy(_bitmapData, row_pointers, pixelCount);
    _width = width;
    _height = height;
    
    
    printf("\nsetting the data: width = %d  height = %d", _width, _height);
    
    //cleanup
           
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    free(row_pointers);
    delete pngFile;
    
    
    ==================================================================
    
    
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_bytep *row_pointers = NULL;
    int bitDepth, colourType;
    unsigned int width, height;
    
    
    SprigFile *pngFile = SprigFileSystem::open(filepath.c_str(), "rb");
    
    if(!pngFile)
        return false;
    
    png_byte sig[8];
    
    fread(&sig, 8, sizeof(png_byte), pngFile->file);
    rewind(pngFile->file);//so when we init io it won't bitch
    if(!png_check_sig(sig, 8))
        return false;
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);
    
    if(!png_ptr)
        return false;
    
    if(setjmp(png_jmpbuf(png_ptr)))
        return false;
    
    info_ptr = png_create_info_struct(png_ptr);
    
    if(!info_ptr)
        return false;
    
    png_init_io(png_ptr, pngFile->file);
    
    png_read_info(png_ptr, info_ptr);
    
    
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bitDepth = png_get_bit_depth(png_ptr, info_ptr);
    colourType = png_get_color_type(png_ptr, info_ptr);
    
    if(colourType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    
    
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    
    if(bitDepth == 16)
        png_set_strip_16(png_ptr);
    else if(bitDepth < 8)
        png_set_packing(png_ptr);
    
    png_read_update_info(png_ptr, info_ptr);
    
    
    png_get_IHDR(png_ptr, info_ptr, &width, &height,
               &bitDepth, &colourType, NULL, NULL, NULL);
    
    
    _bitmapData = (unsigned char *)malloc(sizeof(unsigned char) * (width * height * 4));
    
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    
    for(int i = 0; i < height; ++i)
      row_pointers[i] = (png_bytep)(_bitmapData + (i * width * 4));
    
    PrintData((unsigned char *)row_pointers, width * height * 4);
    
    printf("\n--------------------\n");
    
    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, NULL);   

    PrintData((unsigned char *)row_pointers, width * height * 4);
    
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    delete pngFile;
    free(row_pointers);
     */
    
    PNGImage image;
    
    if(image.Read(filepath.c_str()))
    {
        printf("loaded file %s", filepath.c_str());
        
        
        _width = image.GetWidth();
        _height = image.GetHeight();
        _pixelSize = image.GetChannels();        
        _bitmapData = new unsigned char[image.GetPixelCount()];
        
        memcpy(_bitmapData, image.GetPixelData(), image.GetPixelCount());
    
        //PrintData();
    }
    
    return true;
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