//
//  GSKScanFlow+Dictionary.h
//  GSSDKScanFlow
//
//  Created by Bruno Virlet on 5/9/19.
//

#import <GSSDKScanFlow/GSSDKScanFlow.h>

NS_ASSUME_NONNULL_BEGIN

@interface GSKScanFlowResult (Dictionary)

/**
 A dictionary representation of the result.

 Convenient for interfacing with React Native, probably no reason to use it with native code.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSString *, id> *dictionary;

@end

NS_ASSUME_NONNULL_END
