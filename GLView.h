#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@protocol GLViewDelegate
- (void)drawView:(UIView *)theView;
- (void)setupView:(UIView *)theView;
@end


@interface GLView : UIView 
{
    
@private
	
    GLint backingWidth;
    GLint backingHeight;
    
    EAGLContext *context;    
    GLuint viewRenderbuffer, viewFramebuffer;
    GLuint depthRenderbuffer;
    
    NSTimer *timer;
    NSTimeInterval frameRate;
    
    id <GLViewDelegate> delegate;
}

@property (assign) NSTimeInterval frameRate;
@property (assign) id <GLViewDelegate> delegate;

- (void)start;
- (void)stop;
- (void)drawView;

@end
