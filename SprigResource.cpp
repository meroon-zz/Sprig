//
//  SprigResource.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-20.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigResource.h"
#include "SprigImageEncoding.h"





ResourceManager *ResourceManager::_instance = NULL;

ResourceManager* ResourceManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ResourceManager;
    }
    
    return  _instance;
}

IResource* ResourceManager::getResource(const char *path, ResourceType type)
{
    IResource *resource = _resources[path];
    
    if(resource == NULL)
    {
        resource = getResourceType(type);
        
        if(resource->Read(path))
        {
            _resources.insert(std::pair<const char *, IResource*>(path, resource));
            
            return resource;
        }
        else
        {
            return NULL;
        }
    }
    
    return resource;
}

IResource* ResourceManager::getResourceType(ResourceType type)
{
    IResource *resource = NULL;
    
    switch (type) {
        case PNGImageResourceType:
            return new PNGImage;
            
    }
    
    return resource;
}

void ResourceManager::removeResource(const char *path)
{
    
}

void ResourceManager::removeAll()
{
    
}