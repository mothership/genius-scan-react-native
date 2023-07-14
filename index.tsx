import {
  requireNativeComponent,
  UIManager,
  Platform,
  NativeModules,
  type ViewStyle, Dimensions, LayoutRectangle, NativeModule, findNodeHandle
} from "react-native"
import React, { Ref, useEffect, useImperativeHandle, useRef, useState, forwardRef } from "react"
import { MapMarker } from "@models/map/MapMarker"
import MapboxGL, { CameraBoundsWithPadding } from "@rnmapbox/maps"
import { Text } from "@components/Text"
import { COLORS } from "@styles/color"
import Polyline from "@mapbox/polyline"
import { MapRefType, MapView } from "@components/Map"

const LINKING_ERROR =
  `The package 'react-native-genius-scan' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';


export type GeniusScanOnEnableTakePictureEvent = {
  enable: boolean;
};

export type GeniusScanOnImageCapturedEvent = {
  imageBase64: string;
};

type GeniusScanProps = {
  onEnableTakePicture: (enable: boolean) => void;
  onImageCaptured: (imagePath: string) => void;
  style: ViewStyle;
};

const ComponentName = 'GeniusScanView';

const RNGeniusScanView =
  UIManager.getViewManagerConfig(ComponentName) != null
    ? requireNativeComponent<GeniusScanProps>(ComponentName)
    : () => {
        throw new Error(LINKING_ERROR);
      };


export interface GeniusScanViewRefType {
  takePicture: () => void
}

export const GeniusScanner = forwardRef(
  (props: GeniusScanProps,
    ref: Ref<GeniusScanViewRefType>,
  ): JSX.Element => {
    // Refs
    const scanRef = useRef(null)

    const [enableTakePicture, setEnableTakePicture] = useState(false)
    const [debouncedEnableTakePicture, setDebouncedEnableTakePicture] = useState(false)

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

    useEffect(() => {
      props.onEnableTakePicture(enableTakePicture)
    }, [enableTakePicture])

    useImperativeHandle(ref, () => ({ takePicture }))

    const _onEnableTakePicture = (event: { nativeEvent: GeniusScanOnEnableTakePictureEvent }) => {
      if (!props.onEnableTakePicture) {
        return;
      }

      // console.log(`Detected ${event.nativeEvent.enable}`)

      // process raw event...
      setEnableTakePicture(event.nativeEvent.enable)
    };

    const _onImageCaptured = (event: { nativeEvent: GeniusScanOnImageCapturedEvent }) => {
      if (!props.onImageCaptured) {
        return;
      }

      // process raw event...
      props.onImageCaptured(event.nativeEvent.imagePath);
    };

    // Exposed public functions
    const takePicture = (): void => {
      NativeModules.GeniusScanView.takePicture(findNodeHandle(scanRef.current))
    }

    return (
      <RNGeniusScanView
        ref={scanRef} {...props}
        // @ts-ignore
        onEnableTakePicture={_onEnableTakePicture}
        // @ts-ignore
        onImageCaptured={_onImageCaptured}
      />
    )
  },
)

export const GeniusScanModule = NativeModules.RNGeniusScan
  ? NativeModules.RNGeniusScan
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export type GeniusScanSingleScan = {
  enhancedUrl: string;
  originalUrl: string;
};

export type GeniusScanResult = {
  multiPageDocumentUrl: string;
  pdfUrl: string;
  scans: GeniusScanSingleScan[];
};

export function scanWithConfiguration(
  scanOptions: Record<string, unknown>
): Promise<GeniusScanResult> {
  return GeniusScanModule.scanWithConfiguration(scanOptions);
}

export function setLicenceKey(apiKey: string): Promise<void> {
  return GeniusScanModule.setLicenceKey(apiKey);
}
