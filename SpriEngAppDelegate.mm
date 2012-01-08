
#import "SpriEngAppDelegate.h"


#include "Game.h"
#include "SprigScreen.h"
#include "SprigApplication.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

@implementation SpriEngAppDelegate

@synthesize window = _window;
@synthesize glView = _glView;

Game _game;

-(Orientation) getOrientation
{      
    //NSLog(@"the orientation: %@", [[UIDevice currentDevice] orientation]);
    
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
            return OrientationLandScapeRight;
    }
}

-(void) checkOrientation
{
    Orientation currentOrientation = Application::getInstance()->screen.orientation;
    Orientation newOrientation = [self getOrientation];
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    
    if(currentOrientation != newOrientation)
    {        
        if(newOrientation == OrientationLandscapeLeft)
        {
            _glView.transform = CGAffineTransformMakeRotation(M_PI / 2);
        }
        else if(newOrientation == OrientationLandScapeRight)
        {
            _glView.transform = CGAffineTransformMakeRotation(-M_PI / 2);
        }
        else if(newOrientation == OrientationPortraitNormal)
        {
            _glView.transform = CGAffineTransformMakeRotation(0);
        }
        else if(newOrientation == OrientationPortraitUpsideDown)
        {
            _glView.transform = CGAffineTransformMakeRotation(M_PI);
        }
        
        _glView.frame = CGRectMake(0, 0, screenBounds.size.width, screenBounds.size.height);
        
        NSLog(@"Changed orientation: %@", NSStringFromCGRect(_glView.frame));
        
        Application::getInstance()->screen.orientation = newOrientation;
        
        [_glView setNeedsLayout];
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

    //_glView.backgroundColor = [UIColor redColor];
    
    NSLog(@"setting up view");
    
    
    
    
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
    
    Application::getInstance()->start();  
    
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(checkOrientation) name:@"UIDeviceOrientationDidChangeNotification" object:nil];
    [self checkOrientation];
    
	[_glView start];
	
	
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

