
#pragma once

#include <cstdio>


class SprigFile
{    
    
public:
    
    SprigFile(const char *filename) { this->filename = filename; }
    ~SprigFile();
    
    const char *filename;
    FILE *file;
    
};


class SprigFileSystem
{
    
public:
    static SprigFile* open(const char *filename, const char *options);
    static int close(SprigFile *file);
    
};