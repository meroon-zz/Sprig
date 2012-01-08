//
//  SprigSpriteAtlas.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigSpriteAtlas.h"
#include "SprigXMLFile.h"
#include "SprigResource.h"
#include "tinyxml.h"

SpriteAtlas::SpriteAtlas()
{
    Reset();
}

SpriteAtlas::~SpriteAtlas()
{
    
}


Rectangle *parseClipRect(TiXmlElement *element)
{
    //string key = string(element->Attribute("name"));
    Rectangle *clipRect = new Rectangle;
    
    element->QueryFloatAttribute("x", &clipRect->x);
    element->QueryFloatAttribute("y", &clipRect->y);
    element->QueryFloatAttribute("height", &clipRect->width); //height and width are swapped because of a bug in zwoptex exporting sparrow XML
    element->QueryFloatAttribute("width", &clipRect->height);
    
    return clipRect;
}


bool SpriteAtlas::LoadSheet(const char *path)
{
    XMLFile *xmlFile = (XMLFile *)ResourceManager::getInstance()->getResource(path, ResourceManager::ResourceTypeXML);
    
    if (!xmlFile)
    {
        return false;
    }
    
    TiXmlNode *atlasNode = xmlFile->document->FirstChild("TextureAtlas");
    TiXmlElement *atlas = atlasNode->ToElement();
    TiXmlElement *subTextureElement = NULL;
    Rectangle *rectangle = NULL;
    
    for(subTextureElement = atlas->FirstChildElement(); subTextureElement; subTextureElement = subTextureElement->NextSiblingElement())
    {        
        rectangle = parseClipRect(subTextureElement);
        
        //rectangle->Print();
        
        _clipRects.push_back(rectangle);
    }
    
    Reset();
    
    //xmlFile->document->Print();
    
    return true;
}

void SpriteAtlas::Reset()
{
    _clipRectPtr = _clipRects.begin();
}

Rectangle* SpriteAtlas::CurrentRect()
{
    return *_clipRectPtr;
}

Rectangle* SpriteAtlas::NextRect()
{
    if(_clipRects.size() == 0)
        return NULL;
    
    if(++_clipRectPtr == _clipRects.end())
    {
        Reset();
    }
    
    return *_clipRectPtr;
}

void SpriteAtlas::setRectIndex(int index)
{
    _clipRectPtr = _clipRects.begin() + index;
}