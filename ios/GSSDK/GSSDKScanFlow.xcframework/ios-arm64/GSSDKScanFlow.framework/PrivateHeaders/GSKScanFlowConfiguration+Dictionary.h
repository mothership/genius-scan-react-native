//
//  GSKScanFlowConfiguration+Dictionary.h
//  GSSDKScanFlow
//
//  Created by Bruno Virlet on 5/9/19.
//

#import <GSSDKScanFlow/GSSDKScanFlow.h>

NS_ASSUME_NONNULL_BEGIN

@interface GSKScanFlowConfiguration (Dictionary)

/**
 This method creates a configuration from a dictionary.

 This is particularly useful for interfacing with React Native but this
 shouldn't be used in native projects.

 @param dictionary The configuration dictionary
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 */
+ (instancetype _Nullable)configurationWithDictionary:(NSDictionary *)dictionary error:(NSError * _Nullable *)error;

@end

NS_ASSUME_NONNULL_END
