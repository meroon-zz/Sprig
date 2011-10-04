
#import <Foundation/Foundation.h>
#import "GLView.h"



@interface SpriEngAppDelegate : NSObject <UIApplicationDelegate, GLViewDelegate> {
    UIWindow *_window;
	GLView *_glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet GLView *glView;

@end
