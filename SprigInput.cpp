//
//  SprigInput.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigInput.h"
#include "Constants.h"

void Input::Reset()
{
    _wasPressed = false;
}

void Input::singleTap(float x, float y)
{    
    _lastX = x;
    _lastY = y;
    
    _wasPressed = true;
}

bool Input::GetPressed()
{
    return _wasPressed;
}

float Input::GetLastX()
{
    return  _lastX;
}

float Input::GetLastY()
{
    return _lastY;
}