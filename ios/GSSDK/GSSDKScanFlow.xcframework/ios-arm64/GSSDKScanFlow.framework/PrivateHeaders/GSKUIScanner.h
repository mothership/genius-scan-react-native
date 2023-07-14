//
//  GSKUIScannerUI.h
//  GSSDKScannerUI
//
//  Created by Bruno Virlet on 4/26/19.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The source for a scan flow
 */
typedef NS_ENUM(NSUInteger, GSKUIScannerSource) {
    /** Scan from the camera */
    GSKUIScannerSourceCamera,
    /** Import a file from the library */
    GSKUIScannerSourceLibrary,
};

/**
 Enables configuration of the GSKUIScanner scan flow.

 Set the desired configuration on an instance of GSKUIScannerConfiguration and pass it to the initializer of GSKUIScanner to build the desired scan flow.
 */
@interface GSKUIScannerConfiguration : NSObject

/**
 Specifies the source for the scanned documents (eg. the camera or the photo library).
 */
@property (nonatomic, assign) GSKUIScannerSource source;

@end

/**
 The result of a scan flow
 */
@interface GSKUIScannerResult : NSObject

/**
 The PDF generated at the end of the scan flow
 */
@property (nonatomic, strong) NSURL *pdfURL;

/**
 The individual scans taken during the scan flow.

 Each scan object contains both the original and the enhanced scans.
 */
@property (nonatomic, strong) NSArray<GSKUIScan *> *scans;
@end

/**
 A high-level scanner module.

 You present it and when the user is done, you obtain a result object containing the scanned documents.

 The scan flow can be customized with a GSKUIScannerConfiguration.
 */
@interface GSKScannerUI : NSObject

/**
 Instantiates a GSKUIScanner with the provided configuration.

 @param configuration The provided configuration
 */
+ (instancetype)scannerWithConfiguration:(GSKUIScannerConfiguration *)configuration;

/**
 Present the scan flow.

 @param viewController The view controller to present the scan flow from.
 @param completionBlock A completion block that will be called upon completion of the scan flow. It received a GSKUIScannerResult object as
 a parameter. This object gives you access to the scanned documents.
 */
- (void)startFromViewController:(UIViewController *)viewController onComplete:(void (^_Nonnull)(GSKUIScannerResult *))completionBlock;

@end

NS_ASSUME_NONNULL_END
