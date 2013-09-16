#import <UIKit/UIKit.h>
#import "GLView.h"

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *viewController;
@property (nonatomic, retain) IBOutlet GLView *glView;

@end
