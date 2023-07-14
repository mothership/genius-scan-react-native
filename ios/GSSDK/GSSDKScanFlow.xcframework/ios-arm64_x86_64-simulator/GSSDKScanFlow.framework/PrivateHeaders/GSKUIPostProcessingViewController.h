//
//  GSCPostProcessingViewController.h
//  GSSDKDemo
//
//  Created by Patrick Nollet on 17/10/2016.
//  Copyright © 2016 The Grizzly Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <GSSDKCore/GSSDKCore.h>

#import <GSSDKScanFlow/GSSDKScanFlow.h>

@class GSKScanFlowScan;
@class GSKQuadrangle;
@class GSKUIPostProcessingViewController;

@protocol GSKUIPostProcessingViewControllerDelegate

- (void)postProcessingViewControllerDidCancel:(GSKUIPostProcessingViewController *)postProcessingViewController;
- (void)postProcessingViewControllerDidFinish:(GSKUIPostProcessingViewController *)postProcessingViewController;
- (void)postProcessingViewController:(GSKUIPostProcessingViewController *)postProcessingViewController didFailWithError:(NSError *)error;

@end

@interface GSKUIPostProcessingViewController : UIViewController <UIScrollViewDelegate>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithProcessor:(GSKScanProcessor *)processor;

@property (nonatomic, strong) GSKScanFlowScan *scan;

@property (nonatomic, copy) NSString *backButtonTitle;
@property (nonatomic, copy) NSString *nextButtonTitle;

@property (nonatomic, strong) GSKScanFlowConfiguration *configuration;

@property (nonatomic, weak) id<GSKUIPostProcessingViewControllerDelegate> delegate;

@end
