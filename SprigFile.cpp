

#include "SprigFile.h"

SprigFile* SprigFileSystem::open(const char *filename)
{
    SprigFile *retFile = NULL;
    FILE *file = fopen(filename, "r");

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
