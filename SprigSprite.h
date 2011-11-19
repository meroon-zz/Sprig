//
//  SprigSprite.h
//  Sprig
//
//  Created by Cam Warnock on 11-11-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigGameObject.h"
#include "SprigBitmap.h"

class Sprite : public GameObject
{
    
public:
    
    Sprite();
    ~Sprite();

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void AddBitmap(Bitmap &bitmap);
    
private:
    
    void calculateMesh();
    
    unsigned int _width;
    unsigned int _height;
    
    float _x;
    float _y;
};