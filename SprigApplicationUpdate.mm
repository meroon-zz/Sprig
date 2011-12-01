//
//  SprigApplicationUpdate.cpp
//  Sprig
//
//  Created by Cam Warnock on 11-11-30.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SprigApplicationUpdate.h"
#include "SprigApplication.h"

static id _currentApplicationUpdate;

@implementation ApplicationUpdate

@synthesize interval;

+(id)currentApplicationUpdate
{
    if(_currentApplicationUpdate == nil)
    {
        _currentApplicationUpdate = [ApplicationUpdate new];
    }
    
    return _currentApplicationUpdate;
}

-(void) startMainLoop
{
    _timer = [NSTimer scheduledTimerWithTimeInterval:(1.0 / self.interval) target:self selector:@selector(onUpdate:) userInfo:nil repeats:YES];
}

-(void) stopMainLoop
{
    _timer = nil;
}

-(void) onUpdate: (id) sender
{
    Application::getInstance()->update();
}

@end