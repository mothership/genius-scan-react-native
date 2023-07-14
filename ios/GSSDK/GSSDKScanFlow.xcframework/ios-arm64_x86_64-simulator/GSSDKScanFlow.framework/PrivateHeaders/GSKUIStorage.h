//
//  Storage.h
//  GSSDKDemo
//
//  Created by Bruno Virlet on 10/24/16.
//  Copyright © 2016 The Grizzly Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GSKScanFlowScan;

@interface GSKUIStorage : NSObject

+ (instancetype)sharedStorage;

- (void)addScan:(GSKScanFlowScan *)scan;
- (void)deleteLastScan;

- (void)clear;

@property (nonatomic, readonly) NSArray<GSKScanFlowScan *> *scans;

@end
