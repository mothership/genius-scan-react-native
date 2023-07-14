//
// Genius Scan SDK
//
// Copyright 2010-2022 The Grizzly Labs
//
// Subject to the Genius Scan SDK Licensing Agreement
// sdk@thegrizzlylabs.com
//



#ifndef GSKUIDocumentGeneratorProtocol_h
#define GSKUIDocumentGeneratorProtocol_h

@protocol GSKUIDocumentGeneratorProtocol <NSObject>

- (NSURL*)generateDocumentFromScans:(NSArray<GSKScanFlowScan*>*)scans
                  withConfiguration:(GSKScanFlowConfiguration *)configuration;

@end

#endif /* GSKUIDocumentGeneratorProtocol_h */
