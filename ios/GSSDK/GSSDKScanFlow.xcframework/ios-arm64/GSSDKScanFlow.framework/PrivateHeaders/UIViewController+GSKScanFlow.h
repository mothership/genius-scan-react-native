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

@interface UIViewController (GSKScanFlow)

@property (nonatomic, readonly) UIStatusBarStyle gsk_statusBarStyleBasedOnConstrast;
@property (nonatomic, readonly) UIInterfaceOrientationMask gsk_supportedInterfaceOrientations;

@end

NS_ASSUME_NONNULL_END
