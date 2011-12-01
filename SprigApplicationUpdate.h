@interface ApplicationUpdate : NSObject
{
    NSTimer *_timer;
}

@property (readwrite) NSTimeInterval interval;

+(id)currentApplicationUpdate;
-(void) startMainLoop;
-(void) stopMainLoop;
-(void) onUpdate: (id) sender;

@end

