#import <React/RCTConvert.h>
#import <React/RCTUtils.h>
#import <GSSDKCore/GSSDKCore.h>
#import <GSSDKCore/GSSDKCore-Swift.h>
#import <GSSDKScanFlow/GSSDKScanFlow.h>
#import <GSSDKScanFlow/GSKScanFlowResult+Dictionary.h>
#import <GSSDKScanFlow/GSKScanFlowConfiguration+Dictionary.h>
#import <React/RCTBridgeModule.h>
#import <GSSDKCore/GSSDKCore.h>

@interface RNGeniusScan : NSObject <RCTBridgeModule>

@property (nonatomic, strong) GSKScanFlow *scanner;
- (void)presentViewController:(UIViewController *)viewController rejecter:(RCTPromiseRejectBlock)reject;
@end

@implementation RNGeniusScan

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

- (void)presentViewController:(UIViewController *)viewController rejecter:(RCTPromiseRejectBlock)reject {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *root = RCTPresentedViewController();
        @try {
            [root presentViewController:viewController animated:YES completion:nil];
        }
        @catch (NSException *exception) {
            reject(exception.name, exception.reason, nil);
        }
    });
}

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(setLicenceKey:(NSString *)licenceKey resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {
    NSError *error = nil;
    BOOL validLicence = [GSK initWithLicenseKey:licenceKey error:&error];

    if (validLicence) {
        resolve(nil);
    } else {
        reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], @"License key is not valid or has expired.", error);
    }
}

RCT_EXPORT_METHOD(scanWithConfiguration:(NSDictionary *)scanOptions
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject
                  ) {
    NSError *error = nil;
    GSKScanFlowConfiguration *configuration = [GSKScanFlowConfiguration configurationWithDictionary:scanOptions error:&error];
    if (!configuration) {
        reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], error.localizedDescription, error);
        return;
    }

    self.scanner = [GSKScanFlow scanFlowWithConfiguration:configuration];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *root = RCTPresentedViewController();
        @try {
            [self.scanner startFromViewController:root onSuccess:^(GSKScanFlowResult * _Nonnull result) {
                resolve([result dictionary]);
            } failure:^(NSError *error) {
              reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], error.localizedDescription, error);
            }];
        }
        @catch (NSException *exception) {
            reject(exception.name, exception.reason, nil);
        }
    });
}

RCT_EXPORT_METHOD(generateDocument:(NSDictionary *)documentDictionary
                  withConfiguration:(NSDictionary *)configurationDictionary
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject
                  ) {
    NSError *error = nil;
    GSKDocumentGeneratorConfiguration *configuration = [[GSKDocumentGeneratorConfiguration alloc] initWithDictionary:configurationDictionary error:&error];
    if (!configuration) {
        reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], error.localizedDescription, error);
        return;
    }

    GSKPDFDocument *document = [[GSKPDFDocument alloc] initWithDictionary:documentDictionary error:&error];
    if (!document) {
        reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], error.localizedDescription, error);
        return;
    }

    BOOL success = [[GSKDocumentGenerator alloc] generate:document configuration:configuration error:&error];
    if (success) {
        resolve(nil);
    } else {
        reject([NSString stringWithFormat:@"%@ error %d", error.domain, error.code], @"Document generation failed.", error);
    }
}

@end
