// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from sdk-core.djinni

#import "GSKLoggerSeverity.h"
#import <Foundation/Foundation.h>


/** A interface for a logger object. Implement this to inject your own logger or use the default logger available in the SDK. */
@protocol GSKLogger <NSObject>

- (void)log:(nonnull NSString *)message
   severity:(GSKLoggerSeverity)severity;

@end