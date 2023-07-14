//
// Genius Scan SDK
//
// Copyright 2010-2019 The Grizzly Labs
//
// Subject to the Genius Scan SDK Licensing Agreement
// sdk@thegrizzlylabs.com
//

#import <GSSDKCore/GSSDKCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface GSKView (Animation)

// There is no duration because this repeats indefinitely while searching for
// a quadrangle.
- (void)startSearchAnimation;
- (void)endSearchAnimation;

- (void)startSnapAnimationWithDuration:(NSTimeInterval)duration;
- (void)endSnapAnimation;

@end

NS_ASSUME_NONNULL_END
