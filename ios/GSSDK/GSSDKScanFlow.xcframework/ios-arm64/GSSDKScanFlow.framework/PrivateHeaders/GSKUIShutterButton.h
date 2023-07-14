//
// Genius Scan SDK
//
// Copyright 2010-2019 The Grizzly Labs
//
// Subject to the Genius Scan SDK Licensing Agreement
// sdk@thegrizzlylabs.com
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface GSKUIShutterButton : UIButton

- (void)startSearchAnimation;
- (void)endSearchAnimation;
- (void)startSnapAnimationWithDuration:(NSTimeInterval)duration;
- (void)endSnapAnimation;

@end

NS_ASSUME_NONNULL_END
