
#import "SpriEngAppDelegate.h"


#include "Game.h"
#include "SprigScreen.h"
#include "SprigApplication.h"

#include <string>

using std::string;

@implementation SpriEngAppDelegate

@synthesize window = _window;
@synthesize glView = _glView;

Game _game;


-(Orientation) getOrientation
{      
    switch ([[UIDevice currentDevice] orientation]) 
    {
        case UIDeviceOrientationLandscapeLeft:
            return OrientationLandscapeLeft;
        case UIDeviceOrientationLandscapeRight:
            return OrientationLandScapeRight;
        case UIDeviceOrientationPortrait:
            return OrientationPortraitNormal;
        case UIDeviceOrientationPortraitUpsideDown:
            return OrientationPortraitUpsideDown;
        case UIDeviceOrientationFaceUp:
            return OrientationFaceUp;
        case UIDeviceOrientationFaceDown:
            return OrientationFaceDown;
        case UIDeviceOrientationUnknown:
        default:
            return OrientationUnknown;
    }
}

-(void) checkOrientation
{
    Orientation orientation = [self getOrientation];
    
    if(orientation == OrientationLandscapeLeft)
    {
        _glView.transform = CGAffineTransformMakeRotation(M_PI / 180 * 90);
    }
    else if([self getOrientation] == OrientationLandScapeRight)
    {
        _glView.transform = CGAffineTransformMakeRotation(M_PI / 180 * -90);
    }
    else if([self getOrientation] == OrientationPortraitNormal)
    {
        _glView.transform = CGAffineTransformMakeRotation(0);
    }
    else if([self getOrientation] == OrientationPortraitUpsideDown)
    {
        _glView.transform = CGAffineTransformMakeRotation(M_PI);
    }
    
}

#pragma mark GLView Delegate


- (void)setupView:(GLView *)theView
{	    
    
//    EnvironmentData data;
//    data.basePath = std::string([[[NSBundle mainBundle] bundlePath] UTF8String]); 
//    data.screenRect = Rectangle(_glView.bounds.size.width, _glView.bounds.size.height);
//    
//    UITapGestureRecognizer *singleTap = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleSingleTap:)] autorelease];
//    singleTap.numberOfTapsRequired = 1;
//    [theView addGestureRecognizer:singleTap];
//    
//    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(checkOrientation) name:@"UIDeviceOrientationDidChangeNotification" object:nil];
//    
//    Screen::getInstance()->orientation = [self getOrientation];
//    [self checkOrientation];
//    
//	  _game.Init(data);
    
    Application::getInstance()->start();    
}


- (void)handleSingleTap:(UIGestureRecognizer *)sender
{
    CGPoint translate = [sender locationInView:_glView];
    
    _game.input.singleTap(translate.x, translate.y);
}

- (void)drawView:(GLView *)theView
{
	//_game.Update();
}


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
	[_glView start];
	
    // Override point for customization after application launch.
	
    [self.window makeKeyAndVisible];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    
}


- (void)applicationWillTerminate:(UIApplication *)application {
   
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    
}


- (void)dealloc {
    [_glView release];
	[_window release];
    [super dealloc];
}


@end

