#pragma once

#include "SprigRectangle.h"

enum Orientation
{
    OrientationUnknown = 0x00,
    OrientationLandscapeLeft = 0x01,
    OrientationLandScapeRight = 0x02,
    OrientationPortraitNormal = 0x04,
    OrientationPortraitUpsideDown = 0x08,
    OrientationFaceUp = 0x10,
    OrientationFaceDown = 0x12,
    OrientationLandscape = OrientationLandscapeLeft | OrientationLandScapeRight,
    OrientationPortrait = OrientationPortraitNormal | OrientationPortraitUpsideDown
};

class Screen
{
  
public:

    Screen() : orientation(OrientationLandscapeLeft) {};
    
    Orientation orientation;
    
    Rectangle dimensions;
    
    float getWidth();
    float getHeight();
};