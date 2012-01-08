#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>

#import "GLView.h"
#import "Constants.h"

@interface GLView()
	@property (nonatomic, retain) EAGLContext *context;
	@property (nonatomic, assign) NSTimer *timer;
	- (BOOL) createFramebuffer;
	- (void) destroyFramebuffer;
@end


#pragma mark -

@implementation GLView

@synthesize context;
@synthesize timer;
@synthesize frameRate;
@synthesize delegate;

+ (Class)layerClass 
{
    return [CAEAGLLayer class];
}
- (id)initWithCoder:(NSCoder*)coder {
	
    if ((self = [super initWithCoder:coder])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		
		if (!context || ![EAGLContext setCurrentContext:context]) {
			[self release];
			return nil;
        }
        
        self.frameRate = kActiveFrameRate;
    }
    
    return self;
}



- (void)drawView 
{
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    [delegate drawView:self];
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}
- (void)layoutSubviews 
{		
    NSLog(@"Laying out the subviews");
    
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
    [self drawView];
}
- (BOOL)createFramebuffer 
{
    
    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
    
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    
    NSLog(@"Creating framebuffer: backingWidth = %d  backingHeight = %d" , backingWidth, backingHeight);
    
    if (kUseDepthBuffer) 
    {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) 
    {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    [delegate setupView:self];
    return YES;
}
- (void)destroyFramebuffer 
{
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(depthRenderbuffer) 
    {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}
- (void)start 
{		
    self.timer = [NSTimer scheduledTimerWithTimeInterval:(1.0 / frameRate) target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}

- (void)stop 
{	
    self.timer = nil;
}

- (void)setTimer:(NSTimer *)newTimer 
{
    [timer invalidate];
    timer = newTimer;
}

- (void)setFrameRate:(NSTimeInterval)rate 
{
    frameRate = rate;
	
    if (timer) 
    {
        [self stop];
        [self start];
    }
}
- (void)dealloc 
{
    [self stop];
    
    if ([EAGLContext currentContext] == context) 
        [EAGLContext setCurrentContext:nil];
    
    [context release];  
    [super dealloc];
}

@end