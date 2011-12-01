//
//  SprigScreen.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigScreen.h"

Screen *Screen::_instance = NULL;

Screen* Screen::getInstance()
{
    if (_instance == NULL) {
        
        _instance = new Screen;
    }
    
    return _instance;
}
