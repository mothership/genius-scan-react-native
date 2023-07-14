
# Genius Scan SDK for React Native

## Description

This React Native component allows you to access the [Genius Scan SDK](https://geniusscansdk.com) core features from a React Native application. The component relies on the GSSDKScannerUI library which provides a all-in-one scanner module with simple configurable input.

  - Automatic document detection
  - Document perspective correction
  - Image enhancement with 4 different modes (Black & white, Monochrome, Color, Photo)
  - Batch scanning of several pages in row
  - OCR to extract raw text from images and generate PDF with invisible text layer

## Licence

This component is based on the Genius Scan SDK for which you need to [setup a licence](#api).
You can already try the "demo" version for free by not setting a licence key, the only limitation being that the app will exit after 60 seconds.

To buy a license:
1. [Sign up](https://sdk.geniusscan.com/apps) to our developer console
2. Submit a quote request for each application

You can learn more about [licensing](https://geniusscansdk.com/license/licensing) on our website and contact us at sdk@geniusscan.com for further questions.

## Demo application

As an example, you can check our [demo application](https://github.com/thegrizzlylabs/geniusscan-sdk-demo/tree/master/react-native-genius-scan-demo)

## Getting started

From your React Native root folder:

```
$ npm install @thegrizzlylabs/react-native-genius-scan --save
```

If you use ReactNative below 0.60, you will also need to link the plugin:

```
$ react-native link @thegrizzlylabs/react-native-genius-scan
```

### Additional steps on Android

- To your app `android/app/build.gradle`, change minSdkVersion to `21`.

### Additional steps for iOS

- Add the required permission to your `Info.plist`
```
NSCameraUsageDescription - "We use the camera for <provide a good reason why you are using the camera>"
```
- In your `Podfile`, add the following line:
```
platform :ios, '11.0'
```

#### With ReactNative 0.60 and above

Run `pod install` from the ios folder

#### With ReactNative below 0.60

Open your Xcode project file (ios/*****.xcodeproj), and:
- Add GSSDK.framework and GSSDKScannerUI.framework, located in `node_modules/@thegrizzlylabs/react-native-genius-scan/ios`, to your project "Embedded Libraries"
- Add the path `${PROJECT_DIR}/../node_modules/@thegrizzlylabs/react-native-genius-scan/ios/GSSDK` to your project "Framework Search path" (in the Build Settings)

## Usage

### Set the licence key

Initialize the SDK with a valid licence key:

```javascript
RNGeniusScan.setLicenceKey('REPLACE_WITH_YOUR_LICENCE_KEY')
```

`setLicenseKey` returns a promise that is resolved if the licence key is valid and rejected if it is not. Note that, for testing purpose, you can also use the plugin without a licence key, but it will only work for 60 seconds.

**It is recommended to show a message to users asking them to update the application in case the license has expired.**

### Start the scanner module

```javascript
val result = await RNGeniusScan.scanWithConfiguration(configuration)
```

The method `scanWithConfiguration` takes a `configuration` parameter which can take the following options:

- `source`: `camera` or `image` (defaults to camera)
- `sourceImageUrl`: an absolute image url, required if `source` is `image`. Example: `file:///var/…/image.png`
- `multiPage`: boolean (defaults to true). If true, after a page is scanned, a prompt to scan another page will be displayed. If false, a single page will be scanned.
- `multiPageFormat`: `pdf`, `tiff`, `none` (defaults to `pdf`)
- `defaultFilter`: `none`, `blackAndWhite`, `monochrome`, `color`, `photo` (by default, the filter is chosen automatically)
- `pdfPageSize`: `fit`, `a4`, `letter`, defaults to fit.
- `pdfMaxScanDimension`: max dimension in pixels when images are scaled before PDF generation, for example 2000 to fit both height and width within 2000px. Defaults to 0, which means no scaling is performed.
- `pdfFontFileUrl`: Custom font file used during the PDF generation to embed an invisible text layer. If null, a default font is used, which only supports Latin languages.
- `jpegQuality`: JPEG quality used to compress captured images. Between 0 and 100, 100 being the best quality. Default is 60.
- `postProcessingActions`: an array with the desired actions to display during the post processing screen (defaults to all actions). Possible actions are `rotate`, `editFilter` and `correctDistortion`.
- `flashButtonHidden`: boolean (default to false)
- `defaultFlashMode`: `auto`, `on`, `off` (default to `off`)
- `foregroundColor`: string representing a color, must start with a `#`. The color of the icons, text (defaults to '#ffffff').
- `backgroundColor`: string representing a color, must start with a `#`. The color of the toolbar, screen background (defaults to black)
- `highlightColor`: string representing a color, must start with a `#`. The color of the image overlays (default to blue)
- `menuColor`: string representing a color, must start with a `#`. The color of the menus (defaults to system defaults.)
- `ocrConfiguration`: text recognition options. Text recognition will run on a background thread for every captured image. No text recognition will be applied if this parameter is not present.
    - `languages`: list of language codes (eg `["eng"]`) for which to run text recognition. They should match the provided language files. Note that text recognition will take longer if multiple languages are specified.
    - `languagesDirectoryUrl`: folder containing the language files used for text recognition. Language files can be downloaded from https://github.com/tesseract-ocr/tessdata_fast.

It returns a promise with `result` object containing:

- `multiPageDocumentUrl`: a document containing all the scanned pages (example: "file://<filepath>.pdf")
- `scans`: an array of scan objects. Each scan object has:
    - `originalUrl`: the original file as scanned from the camera. "file://<filepath>.jpeg"
    - `enhancedUrl`: the cropped and enhanced file, as processed by the SDK. "file://<filepath>.{jpeg|png}"
    - `ocrResult`: the result of text recognition for this scan
        - `text`: the raw text that was recognized
        - `hocrTextLayout`: the recognized text in [hOCR](https://en.wikipedia.org/wiki/HOCR) format (with position, style…)

### (Optional) Generate a PDF document from multiple pages

If you'd like to rearrange the pages returned by the ScanFlow or add some more pages, you can do so and generate a PDF document from these pages:

```javascript
await RNGeniusScan.generateDocument(document, configuration)
```

The `document` parameter is a map containing the following values:

- `pages`: an array of page objects. Each page object has:
    - `imageUrl`: the URL of the image file for this page, e.g. `file://<filepath>.{jpeg|png}`
    - `hocrTextLayout`: the text layout in hOCR format

The `configuration` parameter provides the following options:

- `outputFileUrl`: the URL where the document should be generated, e.g. `file://<filepath>.pdf`
- `pdfFontFileUrl`: Custom font file used during the PDF generation to embed an invisible text layer. If null, a default font is used, which only supports Latin languages.


## Examples

### Scanning a document from the camera

```javascript
import RNGeniusScan from '@thegrizzlylabs/react-native-genius-scan';

RNGeniusScan.setLicenceKey('REPLACE_WITH_YOUR_LICENCE_KEY')
.then(() => {
	return RNGeniusScan.scanWithConfiguration({ source: 'camera'})
})
.then((result) => {
	// Do something with the result
})
.catch((error) => {
	// Handle error
})
```

### Cropping and filtering an existing scan

```javascript
import RNGeniusScan from '@thegrizzlylabs/react-native-genius-scan';

const imageUri = 'file://xxxxx' // imageUri from an existing file

RNGeniusScan.setLicenceKey('REPLACE_WITH_YOUR_LICENCE_KEY')
.then(() => {
	return RNGeniusScan.scanWithConfiguration({ source: 'image', sourceImageUrl: imageUri })
})
.then((result) => {
	// Do something with the enhanced image
})
.catch((error) => {
	// Handle error
})
```

# FAQ

## How do I get the UI translated to another language?

The device's locale determines the languages used by the plugin for all strings: user guidance, menus, dialogs…

The plugin supports a wide variety of languages: English (default), Arabic, Chinese (Simplified), Chinese (Traditional), Danish, Dutch, French, German, Hebrew, Indonesian, Italian, Japanese, Korean, Portuguese, Russian, Spanish, Swedish, Turkish, Vietnamese.

NB: iOS applications must be [localized in XCode by adding each language to the project](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPInternational/LocalizingYourApp/LocalizingYourApp.html#//apple_ref/doc/uid/10000171i-CH5-SW2).

## What should I do if my license is invalid?

Make sure that the license key is correct, that is has not expired, and that it is used with the App ID it was generated for. To learn more about the procurement and replacement of license keys, refer to the [Licensing FAQ](https://geniusscansdk.com/license/licensing).

## Troubleshooting
  
Refer to the troubleshooting guides of the native libraries to resolve common configuration and build problems:

- [iOS](https://geniusscansdk.com/docs/v4/ios/troubleshooting/)
- [Android](https://geniusscansdk.com/docs/v4/android/troubleshooting/)

# Changelog

See [changelog](https://geniusscansdk.com/docs/changelog/)
