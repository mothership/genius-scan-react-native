//
//  GSKScanFlow.h
//  GSSDKScanFlow
//
//  Created by Bruno Virlet on 4/26/19.
//

#import <Foundation/Foundation.h>
#import <GSSDKOCR/GSSDKOCR.h>
#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const GSKScanFlowErrorDomain;

typedef NS_ENUM(NSInteger, GSKScanFlowError) {
    /// User has canceled the scan flow
    GSKScanFlowUserCancelationError = 999,
    /// A general error due to a bad input parameter. Verify that your input match the API requirements.
    GSKScanFlowBadInputError = 1000,
};


@class GSKScanFlowScan;

/**
 The source for a scan flow
 */
typedef NS_ENUM(NSUInteger, GSKScanFlowSource) {
    /** Scan from the camera */
    GSKScanFlowSourceCamera,
    /** Import a file from an URL */
    GSKScanFlowSourceImageURL,
    /** Import a file from the library */
    GSKScanFlowSourceLibrary,
};

/**
 The different possible filters for the scanner UI.

 The possible values match the GSKFilterType values except "automatic".
 */
typedef NS_ENUM(NSInteger, GSKScanFlowFilterType) {
    GSKScanFlowFilterAutomatic = 0,
    GSKScanFlowFilterNone,
    GSKScanFlowFilterBlackAndWhite,
    GSKScanFlowFilterColor,
    GSKScanFlowFilterPhoto,
    GSKScanFlowFilterMonochrome,
};

/**
 The various image processing actions available in the post-processing screen.

 This is an option set so you can combine multiple actions.
 */
typedef NS_OPTIONS(NSUInteger, GSKScanFlowPostProcessingActions) {
    /// No actions
    GSKScanFlowPostProcessingActionNone = 0,
    /// The filter action
    GSKScanFlowPostProcessingActionEditFilter = 1 << 0,
    /// The rotate scan action
    GSKScanFlowPostProcessingActionRotate = 1 << 1,
    /// The distortion (book curvature) correction
    GSKScanFlowPostProcessingActionDistortionCorrection = 1 << 2,
    /// All the actions
    GSKScanFlowPostProcessingActionAll = NSUIntegerMax,
};

/**
 The generated PDF paper size.
 */
typedef NS_ENUM(NSUInteger, GSKScanFlowPDFPageSize) {
    /// PDF page with a width of 8.27 inch (A4 width) and fitting height.
    GSKScanFlowPDFPageFit,
    /// ISO A4 (21cm x 29.7cm)
    GSKScanFlowPDFPageA4,
    /// US Letter (8.5in x 11in)
    GSKScanFlowPDFPageLetter,
};

/**
 The capture screen flash mode
 */
typedef NS_ENUM(NSUInteger, GSKScanFlowFlashMode) {
    /// Let the system determine whether to turn on the flash based on the lighting conditions.
    GSKScanFlowFlashModeAuto,
    /// Force the flash on.
    GSKScanFlowFlashModeOn,
    /// Force the flash off.
    GSKScanFlowFlashModeOff,
};

/**
 The format of the exported document.
 */
typedef NS_ENUM(NSUInteger, GSKScanFlowMultiPageFormat) {
    GSKScanFlowNone,
    GSKScanFlowPDF,
    GSKScanFlowTIFF,
};

/**
 Enables configuration of the GSKUIScanner scan flow.

 Set the desired configuration on an instance of GSKScanFlowConfiguration and pass it to the initializer of GSKUIScanner to build the desired scan flow.
 */
@interface GSKScanFlowConfiguration : NSObject

/**
 Specifies the source for the scanned documents (eg. the camera, …).

 If source is GSKScanFlowSourceImageURL, you must provide the sourceImageURL parameter.
 */
@property (nonatomic, assign) GSKScanFlowSource source;

/**
 The image URL if source is GSKScanFlowSourceImageURL.
 */
@property (nonatomic, strong) NSURL *sourceImageURL;

/**
 Multipage mode. Only apply when the source is GSKScanFlowSourceCamera.

 When the multipage mode is active, the user will have the opportunity to snap multiple scans in a row and the output document will contain all these pages.

 When multipage mode is off, the user will only scan a single page. The output document will always contain a single page.

 Defaults to YES.
 */
@property (nonatomic, assign) BOOL multiPage;

/**
 Force the use of a specific post processing.

 Defaults to GSKFilterAutomatic.
 */
@property (nonatomic, assign) GSKScanFlowFilterType defaultFilter;

/**
 Select which actions are displayed in the post processing screen

 Default is everything.
 */
@property (nonatomic, assign) GSKScanFlowPostProcessingActions postProcessingActions;

/**
 Determines the size of the pages when generating the PDF.

 Default is GSKScanFlowPDFPageFit
 */
@property (nonatomic, assign) GSKScanFlowPDFPageSize pdfPageSize;

/**
 Determines the visibility of the flash button
 */
@property (nonatomic, assign) BOOL flashButtonHidden;

/**
 Determines the default flash mode.

 Combine with flashButtonHidden if you want to only allow a specific
 flash mode.

 Defaults to GSKScanFlowFlashModeAuto
 */
@property (nonatomic, assign) GSKScanFlowFlashMode defaultFlashMode;

/**
 Determines the document format.

 Defaults to GSKScanFlowPdf.
 */
@property (nonatomic, assign) GSKScanFlowMultiPageFormat multiPageFormat;

/**
 Custom font file used during the PDF generation to embed an invisible text layer.
 
 If nil, a default font is used, which only supports Latin languages.
 */
@property (nonatomic, strong) NSURL *pdfFontFileURL;

/**
 UI background color.

 Default is black.
 */
@property (nonatomic, copy) UIColor *backgroundColor;

/**
 UI foreground color (text and icons)

 Default is white.
 */
@property (nonatomic, copy) UIColor *foregroundColor;

/**
 UI highlight color (document detection overlay)

 Default is dark blue.
 */
@property (nonatomic, copy) UIColor *highlightColor;

/**
 UI menu color

 Default is system's default (eg. blue on iOS)
 */
@property (nonatomic, copy) UIColor *menuColor;

/**
 JPEG quality used to compress captured images. Between 0 and 100, 100 being the best quality.
 
 Default is 60
 */
@property (nonatomic, assign) NSInteger jpegQuality;

/**
 Max scan dimension in pixels when generating the PDF file. All scans included in the PDF file
 will be scaled so that both their height and width are smaller than this value, while keeping
 their aspect ratio.
 
 Default is 0, which means no scaling is applied.
 */
@property (nonatomic, assign) NSInteger pdfMaxScanDimension;

/**
 The configuration for Optical Character Recognition.

 Default is nil, which means no OCR is performed.
 */
@property (nonatomic, strong) GSKOCRConfiguration *ocrConfiguration;

@end

/**
 The result of a scan flow
 */
@interface GSKScanFlowResult : NSObject

/**
 The PDF generated at the end of the scan flow
 */
@property (nonatomic, strong) NSURL *pdfURL DEPRECATED_MSG_ATTRIBUTE("Use multiPageDocumentURL instead");

/**
 * Document containing the pages that were scanned during the scan flow.
 * The format is specified by `multiPageFormat` property of the used `GSKScanFlowConfiguration`.
 * Is null if no format was specified or if generation failed.
 */
@property (nonatomic, strong, nullable) NSURL* multiPageDocumentURL;

/**
 The individual scans taken during the scan flow.

 Each scan object contains both the original and the enhanced scans.
 */
@property (nonatomic, strong) NSArray<GSKScanFlowScan *> *scans;
@end

/**
 A high-level scanner module.

 You present it and when the user is done, you obtain a result object containing the scanned documents.

 The scan flow can be customized with a GSKScanFlowConfiguration.
 */
@interface GSKScanFlow : NSObject

/**
 Instantiates a GSKUIScanner with the provided configuration.

 @param configuration The provided configuration
 */
+ (instancetype)scanFlowWithConfiguration:(GSKScanFlowConfiguration *)configuration;

/**
 Present the scan flow.

 @param viewController The view controller to present the scan flow from.
 @param completionBlock A completion block that will be called on the main thread upon completion of the scan flow. It received a GSKScanFlowResult object as a parameter. This object gives you access to the scanned documents.
 @param errorBlock A block called upon error
 */
- (void)startFromViewController:(UIViewController *)viewController onSuccess:(void (^_Nonnull)(GSKScanFlowResult *))completionBlock failure:(void (^_Nonnull)(NSError *))errorBlock;

@end

NS_ASSUME_NONNULL_END
