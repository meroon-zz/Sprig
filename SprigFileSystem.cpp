

#include "SprigFileSystem.h"

SprigFile::~SprigFile()
{
    SprigFileSystem::close(this);
}

SprigFile* SprigFileSystem::open(const char *filename, const char *options)
{
    SprigFile *retFile = NULL;
    FILE *file = fopen(filename, options);

	if(file) {
		retFile = new SprigFile(filename);
		retFile->file = file;		
		return retFile;
	}
	
	return NULL;
}

int SprigFileSystem::close(SprigFile *file)
{
    return fclose(file->file);
}
