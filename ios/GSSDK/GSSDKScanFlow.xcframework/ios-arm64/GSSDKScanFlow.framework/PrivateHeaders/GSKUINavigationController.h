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

@class GSKScanFlowConfiguration;

@interface GSKUINavigationController : UINavigationController

+ (instancetype)navigationControllerWithConfiguration:(GSKScanFlowConfiguration *)configuration rootViewController:(UIViewController *)rootViewController;

@end

NS_ASSUME_NONNULL_END
