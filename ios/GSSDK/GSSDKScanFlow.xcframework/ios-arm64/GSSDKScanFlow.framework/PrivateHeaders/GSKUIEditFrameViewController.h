//
//  GSCEditFrameViewController.h
//  GSSDKDemo
//
//  Created by Patrick Nollet on 17/10/2016.
//  Copyright © 2016 The Grizzly Labs. All rights reserved.
//

#import <GSSDKCore/GSSDKCore.h>

#import <GSSDKScanFlow/GSSDKScanFlow.h>

@class GSKUIEditFrameViewController;
@class GSKScanFlowScan;

@protocol GSKUIEditFrameViewControllerDelegate

- (void)editFrameViewControllerDidCancel:(GSKUIEditFrameViewController *)editFrameViewController;
- (void)editFrameViewControllerDidFinish:(GSKUIEditFrameViewController *)editFrameViewController;
- (void)editFrameViewController:(GSKUIEditFrameViewController *)editFrameViewController didFailedWithError:(NSError *)error;

@end

@interface GSKUIEditFrameViewController : GSKEditFrameViewController

@property (nonatomic, strong) GSKScanFlowConfiguration *configuration;

@property (nonatomic, weak) id<GSKUIEditFrameViewControllerDelegate> delegate;

@end
