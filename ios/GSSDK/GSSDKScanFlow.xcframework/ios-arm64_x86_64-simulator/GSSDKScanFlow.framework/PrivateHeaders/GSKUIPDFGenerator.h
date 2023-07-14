//
//  GSKUIPDFGenerator.h
//  GSSDKScanFlow
//
//  Created by Bruno Virlet on 4/26/19.
//

#import <Foundation/Foundation.h>

#import <GSSDKScanFlow/GSSDKScanFlow.h>
#import "GSKUIDocumentGeneratorProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface GSKUIPDFGenerator : NSObject<GSKUIDocumentGeneratorProtocol>

- (NSURL*)generateDocumentFromScans:(NSArray<GSKScanFlowScan*>*)scans
                  withConfiguration:(GSKScanFlowConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
