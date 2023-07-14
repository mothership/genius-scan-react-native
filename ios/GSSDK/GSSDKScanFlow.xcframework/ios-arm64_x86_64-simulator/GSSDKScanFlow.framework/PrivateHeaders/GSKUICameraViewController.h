//
//  CameraViewController.h
//  GSSDKDemo
//
//  Created by Bruno Virlet on 4/3/15.
//  Copyright (c) 2015 Bruno Virlet. All rights reserved.
//

#import <GSSDKCore/GSSDKCore.h>
#import <GSSDKScanFlow/GSSDKScanFlow.h>

@class GSKUICameraViewController;
@class GSKScanFlowScan;

@protocol GSKUICameraViewControllerDelegate

- (void)cameraViewControllerDidCancel:(GSKUICameraViewController *)cameraViewController;
- (void)cameraViewControllerDone:(GSKUICameraViewController *)cameraViewController;
- (void)cameraViewControllerDidSnapPhoto:(GSKUICameraViewController *)cameraViewController;
- (void)cameraViewController:(GSKUICameraViewController *)cameraViewController didScan:(GSKScan *)scan onComplete:(void (^)(void))onComplete;
- (void)cameraViewController:(GSKUICameraViewController *)cameraViewController didFailWithError:(NSError *)error;

@end

/**
 A very simple camera view.

 The complexity is hidden in GSKCameraViewController.
 You have access to all the delegate methods of the GSKCameraSession.
 */
@interface GSKUICameraViewController : GSKCameraViewController

@property (nonatomic, readonly) UIButton *doneButton;

@property (nonatomic, strong) GSKScanFlowConfiguration *configuration;

@property (nonatomic, weak) id<GSKUICameraViewControllerDelegate> delegate;

@end
