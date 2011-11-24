//
//  SprigInput.h
//  Sprig
//
//  Created by Cam Warnock on 11-11-23.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

class Input
{

public:  

    void singleTap(float x, float y);

    bool GetPressed();
    
    void Reset();
    
    float GetLastX();
    float GetLastY();
    
private:
    
    bool _wasPressed;
    float _lastX, _lastY;
    
};