//
//  SprigXMLFile.h
//  Sprig
//
//  Created by Cam Warnock on 11-11-21.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "SprigResource.h"
#include "tinyxml.h"

class XMLFile : public Resource
{

public:
    
    XMLFile() : Resource() {};
    ~XMLFile();
    
    bool Read(const char *path);
    bool Write(const char *path);
    
    TiXmlDocument *document;
    
};