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



class Resource
{
    
public:
    
    Resource() : filepath(NULL), isLoaded(false) {};
    virtual ~Resource() {};
    virtual unsigned int getID();
    virtual bool Read(const char *path) = 0;
    virtual bool Write(const char *path) = 0;
    
    char *filepath;
    bool isLoaded;
};


typedef std::map<const char *, Resource*> ResourceMap;

class ResourceManager
{
    
public:
    
    enum ResourceType { ResourceTypePNGImage, ResourceTypeXML };
    
    static ResourceManager* getInstance();
    Resource *getResource(const char *path, ResourceType type);
    void removeResource(const char *path);
    void removeAll();
    
private:
    
    Resource* getResourceType(ResourceType type);
    
    ResourceMap _resources;
    static  ResourceManager *_instance;
};