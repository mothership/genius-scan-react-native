#import <React/RCTViewManager.h>

//@interface RCT_EXTERN_MODULE(GeniusScanViewManager, RCTViewManager)
@interface RCT_EXTERN_REMAP_MODULE(GeniusScanView, GeniusScanViewManager, RCTViewManager)

RCT_REMAP_VIEW_PROPERTY(onEnableTakePicture, reactOnEnableTakePicture, RCTBubblingEventBlock)
RCT_REMAP_VIEW_PROPERTY(onImageCaptured, reactOnImageCaptured, RCTBubblingEventBlock)

RCT_EXTERN_METHOD(takePicture:(nonnull NSNumber *)reactTag)
@end
