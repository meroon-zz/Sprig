
#include "SprigFileSystem.h"
#include "SprigImageEncoding.h"
#include "png.h"
#include <cstdlib>

bool validate(SprigFile *pngFile) {
    
    //Allocate a buffer of 8 bytes, where we can put the file signature.
    png_byte header[8];
    
    fread(&header, 8, sizeof(png_byte), pngFile->file);
    rewind(pngFile->file);//rewind to prepare for reading the file
    
    if(!png_check_sig(header, 8))
    {
        return false;
    }
    
    return true;
}

const char * PNGImage::getID()
{
    return "1";
}

PNGImage::PNGImage()
{
    _data = NULL;
}

PNGImage::~PNGImage()
{
    if(_data)
    {
        delete [] _data;
    }
}

bool PNGImage::Read(const char * filepath)
{
    SprigFile *pngFile = SprigFileSystem::open(filepath, "rb");
    
    if(!pngFile)
    {
        printf("[PNGImage::Read] ERROR: File %s could not be opened for reading", filepath);
        return false;
    }
    
    if(!validate(pngFile))
    {
        printf("[PNGImage::Read] ERROR: File %s is not recognized as a PNG file", filepath);
    }
    
    //Here we create the png read struct
    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) 
    {
        printf("[PNGImage::Read] ERROR: Couldn't initialize png read struct");
        return false; 
    }
    
    //Here we create the png info struct.
    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) 
    {
        printf("[PNGImage::Read] ERROR: Couldn't initialize png info struct");
        png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
        return false; 
    }
    
    //Here I've defined 2 pointers up front, so I can use them in error handling.
    //I will explain these 2 later. Just making sure these get deleted on error.
    png_bytep* rowPtrs = NULL;
    
    if (setjmp(png_jmpbuf(pngPtr))) 
    {
        png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
        delete [] rowPtrs;
        
        printf("[PNGImage::Read] ERROR: An error occured while reading the PNG file");
        
        return false;
    }
    
    png_init_io(pngPtr, pngFile->file);
    
    //Now call png_read_info with our pngPtr as image handle, and infoPtr to receive the file info.
    png_read_info(pngPtr, infoPtr);
    
    
    _imgWidth =  png_get_image_width(pngPtr, infoPtr);
    _imgHeight = png_get_image_height(pngPtr, infoPtr);
    
    //bits per CHANNEL! note: not per pixel!
    _bitDepth   = png_get_bit_depth(pngPtr, infoPtr);
    
    //Number of channels
    _channels   = png_get_channels(pngPtr, infoPtr);
    
    //Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
    png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);
    
    
    printf("width: %d  height: %d  bitDepth: %d  channels: %d  color type: %d", _imgWidth, _imgHeight, _bitDepth, _channels, color_type);
    
    switch (color_type) {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(pngPtr);
            //Don't forget to update the channel info (thanks Tom!)
            //It's used later to know how big a buffer we need for the image
            _channels = 3;           
            break;
        case PNG_COLOR_TYPE_GRAY:
            if (_bitDepth < 8)
                png_set_expand_gray_1_2_4_to_8(pngPtr);
            _bitDepth = 8;
            break;
    }
    
    /*if the image has a transperancy set.. convert it to a full Alpha channel..*/
    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(pngPtr);
        _channels+=1;
    }
    
    //We don't support 16 bit precision.. so if the image Has 16 bits per channel
    //precision... round it down to 8.
    if (_bitDepth == 16)
        png_set_strip_16(pngPtr);
    
    //This pointer was also defined in the error handling section, so we can clean it up on error.
    rowPtrs = new png_bytep[_imgHeight];
    _data = new unsigned char[_imgWidth * _imgHeight * _bitDepth * _channels / 8];
    
    
    //This is the length in bytes, of one row.
    const unsigned int stride = _imgWidth * _bitDepth * _channels / 8;
    
    //A little for-loop here to set all the row pointers to the starting
    //Adresses for every row in the buffer
    
    for (size_t i = 0; i < _imgHeight; i++) {
        //Set the pointer to the data pointer + i times the row stride.
        //Notice that the row order is reversed with q.
        //This is how at least OpenGL expects it,
        //and how many other image loaders present the data.
        png_uint_32 q = (_imgHeight- i - 1) * stride;
        rowPtrs[i] = (png_bytep)_data + q;
        //rowPtrs[i] = (png_bytep)_data + (stride * i);
    }
    
    //And here it is! The actuall reading of the image!
    //Read the imagedata and write it to the adresses pointed to
    //by rowptrs (in other words: our image databuffer)
    png_read_image(pngPtr, rowPtrs);
    
    
    //Delete the row pointers array....
    delete[] (png_bytep)rowPtrs;
    
    //And don't forget to clean up the read and info structs !
    png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);
    
    
    return true;
}

bool PNGImage::Write(const char * filepath)
{
    return false;
}

unsigned char* PNGImage::GetPixelData()
{
    return _data;
}

unsigned int PNGImage::GetWidth()
{
    return _imgWidth;
}

unsigned int PNGImage::GetHeight()
{
    return _imgHeight;
}

unsigned int PNGImage::GetChannels()
{
    return _channels;
}

unsigned int PNGImage::GetBitDepth()
{
    return _bitDepth;
}

unsigned int PNGImage::GetPixelCount()
{
    return _imgWidth * _imgHeight * _channels;
}