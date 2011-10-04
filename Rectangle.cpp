//
//  Rect.cpp
//  SpriEng
//
//  Created by Cam Warnock on 11-09-22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Rectangle.h"

Rectangle::Rectangle(float width, float height)
{
    this->x = 0;
    this->y = 0;
    this->width = width;
    this->height = height;
}

Rectangle::Rectangle(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}