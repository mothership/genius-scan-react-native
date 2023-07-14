//
// Genius Scan SDK
//
// Copyright 2010-2022 The Grizzly Labs
//
// Subject to the Genius Scan SDK Licensing Agreement
// sdk@thegrizzlylabs.com
//

#import <Foundation/Foundation.h>

#import <GSSDKScanFlow/GSSDKScanFlow.h>
#import "GSKUIDocumentGeneratorProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface GSKUITIFFGenerator : NSObject<GSKUIDocumentGeneratorProtocol>

- (NSURL*)generateDocumentFromScans:(NSArray<GSKScanFlowScan*>*)scans
                  withConfiguration:(GSKScanFlowConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
