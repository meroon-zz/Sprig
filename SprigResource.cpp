//
//  SprigResource.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-20.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigResource.h"
#include "SprigImageEncoding.h"
#include "SprigXMLFile.h"



unsigned int Resource::getID()
{
    return 0;
}



ResourceManager *ResourceManager::_instance = NULL;

ResourceManager* ResourceManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ResourceManager;
    }
    
    return  _instance;
}

Resource* ResourceManager::getResource(const char *path, ResourceType type)
{
    Resource *resource = _resources[path];
    
    if(resource == NULL)
    {
        resource = getResourceType(type);
        
        if(resource->Read(path))
        {
            _resources.insert(ResourceMap::value_type(path, resource));
            
            return resource;
        }
        else
        {
            return NULL;
        }
    }
    
    return resource;
}

Resource* ResourceManager::getResourceType(ResourceType type)
{
    switch (type) {
        case ResourceTypePNGImage:
            return new PNGImage;
        case ResourceTypeXML:
            return new XMLFile;
    }
    
    return NULL;
}

void ResourceManager::removeResource(const char *path)
{
    
}

void ResourceManager::removeAll()
{
    
}