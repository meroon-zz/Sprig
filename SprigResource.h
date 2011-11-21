//
//  SprigResource.h
//  Sprig
//
//  Created by Cam Warnock on 11-11-20.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <string>
#include <map>



class IResource
{
    
public:
    
    virtual ~IResource() {};
    virtual const char * getID() = 0;
    virtual bool Read(const char *path) = 0;
    virtual bool Write(const char *path) = 0;
    
    bool isLoaded;
};


typedef std::map<const char *, IResource*> ResourceMap;

class ResourceManager
{
    
public:
    
    enum ResourceType { PNGImageResourceType };
    
    static ResourceManager* getInstance();
    IResource *getResource(const char *path, ResourceType type);
    void removeResource(const char *path);
    void removeAll();
    
private:
    
    IResource* getResourceType(ResourceType type);
    
    ResourceMap _resources;
    static  ResourceManager *_instance;
};