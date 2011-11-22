//
//  SprigXMLFile.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-21.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigXMLFile.h"


XMLFile::~XMLFile()
{
    if(document != NULL)
    {
        delete document;
    }
}

bool XMLFile::Read(const char *path)
{    
    filepath = (char *)path;
    document = new TiXmlDocument(path);
    
    if (document->LoadFile() )
    {
        isLoaded = true;
    }
    else
    {        
        printf( "Could not load test file '%s'. Error='%s'. Exiting.\n", path, document->ErrorDesc() );
        
        delete document;
        document = NULL;
        
        isLoaded = false;
    }
    
    return isLoaded;
}

bool XMLFile::Write(const char *path)
{
    return false;
}

