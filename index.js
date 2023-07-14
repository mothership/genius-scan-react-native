"use strict";
exports.__esModule = true;
exports.setLicenceKey = exports.scanWithConfiguration = exports.GeniusScanModule = exports.GeniusScanner = void 0;
var react_native_1 = require("react-native");
var react_1 = require("react");
var LINKING_ERROR = "The package 'react-native-genius-scan' doesn't seem to be linked. Make sure: \n\n" +
    react_native_1.Platform.select({ ios: "- You have run 'pod install'\n", "default": '' }) +
    '- You rebuilt the app after installing the package\n' +
    '- You are not using Expo Go\n';
var ComponentName = 'GeniusScanView';
var RNGeniusScanView = react_native_1.UIManager.getViewManagerConfig(ComponentName) != null
    ? (0, react_native_1.requireNativeComponent)(ComponentName)
    : function () {
        throw new Error(LINKING_ERROR);
    };
exports.GeniusScanner = (0, react_1.forwardRef)(function (props, ref) {
    // Refs
    var scanRef = (0, react_1.useRef)(null);
    var _a = (0, react_1.useState)(false), enableTakePicture = _a[0], setEnableTakePicture = _a[1];
    var _b = (0, react_1.useState)(false), debouncedEnableTakePicture = _b[0], setDebouncedEnableTakePicture = _b[1];
    // useEffect(
    //   () => {
    //     // Update debounced value after delay
    //     let handler: string | number | NodeJS.Timeout | undefined
    //     if (enableTakePicture) {
    //       setDebouncedEnableTakePicture(enableTakePicture)
    //     } else {
    //       handler = setTimeout(() => {
    //         setDebouncedEnableTakePicture(enableTakePicture)
    //       }, 500)
    //     }
    //
    //     // Cancel the timeout if value changes (also on delay change or unmount)
    //     // This is how we prevent debounced value from updating if value is changed ...
    //     // .. within the delay period. Timeout gets cleared and restarted.
    //     return () => {
    //       clearTimeout(handler)
    //     }
    //   },
    //   [enableTakePicture], // Only re-call effect if value or delay changes
    // )
    (0, react_1.useEffect)(function () {
        props.onEnableTakePicture(enableTakePicture);
    }, [enableTakePicture]);
    (0, react_1.useImperativeHandle)(ref, function () { return ({ takePicture: takePicture }); });
    var _onEnableTakePicture = function (event) {
        if (!props.onEnableTakePicture) {
            return;
        }
        // console.log(`Detected ${event.nativeEvent.enable}`)
        // process raw event...
        setEnableTakePicture(event.nativeEvent.enable);
    };
    var _onImageCaptured = function (event) {
        if (!props.onImageCaptured) {
            return;
        }
        // process raw event...
        props.onImageCaptured(event.nativeEvent.imagePath);
    };
    // Exposed public functions
    var takePicture = function () {
        react_native_1.NativeModules.GeniusScanView.takePicture((0, react_native_1.findNodeHandle)(scanRef.current));
    };
    return (<RNGeniusScanView ref={scanRef} {...props} 
    // @ts-ignore
    onEnableTakePicture={_onEnableTakePicture} 
    // @ts-ignore
    onImageCaptured={_onImageCaptured}/>);
});
exports.GeniusScanModule = react_native_1.NativeModules.RNGeniusScan
    ? react_native_1.NativeModules.RNGeniusScan
    : new Proxy({}, {
        get: function () {
            throw new Error(LINKING_ERROR);
        }
    });
function scanWithConfiguration(scanOptions) {
    return exports.GeniusScanModule.scanWithConfiguration(scanOptions);
}
exports.scanWithConfiguration = scanWithConfiguration;
function setLicenceKey(apiKey) {
    return exports.GeniusScanModule.setLicenceKey(apiKey);
}
exports.setLicenceKey = setLicenceKey;
