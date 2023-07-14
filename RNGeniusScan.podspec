
Pod::Spec.new do |s|
  s.name         = "RNGeniusScan"
  s.version      = "1.0.0"
  s.summary      = "GeniusScan plugin for React Native"
  s.description  = <<-DESC
                  RNGeniusScan
                   DESC
  s.homepage     = ""
  s.license      = "MIT"
  s.author           = { 'The Grizzly Labs' => 'contact@thegrizzlylabs.com' }
  s.homepage         = "http://thegrizzlylabs.com"
  s.source_files  = ["ios/RNGeniusScan.{h,m}", "ios/GeniusScanViewManager.{m,swift}", "ios/GeniusScan-Bridging-Header.h", "ios/GeniusScanView.swift"]
  s.requires_arc = true
  s.source = { git: 'git@github.com:thegrizzlylabs/geniusscan-sdk-demo.git' }
  s.platform     = :ios, "11.0"

  s.dependency "React"

  s.preserve_paths = 'ios/GSSDK/GSSDKCore.xcframework', 'ios/GSSDK/GSSDKScanFlow.xcframework', 'ios/GSSDK/GSSDKOCR.xcframework'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-framework GSSDKCore -framework GSSDKScanFlow -framework GSSDKOCR' }
  s.vendored_frameworks = 'ios/GSSDK/GSSDKCore.xcframework', 'ios/GSSDK/GSSDKScanFlow.xcframework', 'ios/GSSDK/GSSDKOCR.xcframework'
end
