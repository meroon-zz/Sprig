
#pragma once

#include <cstdio>


class SprigFile
{    
    
public:
    
    SprigFile(const char *filename) { this->filename = filename; }
    
    const char *filename;
    FILE *file;
    
};


class SprigFileSystem
{
    
public:
    static SprigFile* open(const char *filename);
    static int close(SprigFile *file);
    
};