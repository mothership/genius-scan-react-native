//
//  Scan.h
//  GSSDKDemo
//
//  Created by Bruno Virlet on 6/2/16.
//  Copyright © 2016 The Grizzly Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GSSDKCore/GSSDKCore.h>

@class GSKOCRResult;

/**
 The output result from the scan flow.
 */
@interface GSKScanFlowScan : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithOriginalFilePath:(NSString *)originalFilePath;

/// The original JPEG out of the camera.
///
/// Note that this image might be rotated, and needs to be read with its EXIF orientation to be properly displayed.
/// UIImage's methods will properly take care of that.
@property (nonatomic, copy, readonly) NSString *originalFilePath;

/// The enhanced, processed, image.
@property (nonatomic, strong) NSString *enhancedFilePath;

/// Convenient way to access the original image as an UIImage
- (UIImage *)originalImage;

/// Convenient way to access the processed image as an UIImage
- (UIImage *)enhancedImage;

/// The quadrangle that was applied during the scan flow
@property (nonatomic, strong) GSKQuadrangle *appliedQuadrangle;

/// The filter that was applied during the scan flow
@property (nonatomic, assign) GSKFilterType appliedFilter;

/// The rotation that was applied during the scan flow
@property (nonatomic, assign) GSKRotation appliedRotation;

/// If OCR was performed, the recognized text.
@property (nonatomic, strong) GSKOCRResult *ocrResult;

/// Deletes all the files related to this scan. Convenient to clean up after you copied
/// what you needed.
- (void)delete;

@end


