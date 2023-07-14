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

@interface GSKUIDocumentGenerator : NSObject<GSKUIDocumentGeneratorProtocol>

//----------------------------------------------------------------------------------------------------------------------
// MARK: - Properties
//----------------------------------------------------------------------------------------------------------------------

/**
 Determines the document format.
 */

@property (nonatomic, assign, readonly) GSKScanFlowMultiPageFormat multiPageFormat;

//----------------------------------------------------------------------------------------------------------------------
// MARK: - Initialization
//----------------------------------------------------------------------------------------------------------------------

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithMultiPageFormat:(GSKScanFlowMultiPageFormat) multiPageFormat;

//----------------------------------------------------------------------------------------------------------------------
// MARK: - GSKUIDocumentGeneratorProtocol
//----------------------------------------------------------------------------------------------------------------------

- (NSURL*)generateDocumentFromScans:(NSArray<GSKScanFlowScan*>*)scans
                  withConfiguration:(GSKScanFlowConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
