
package com.geniusscansdk.reactnative;

import android.app.Activity;
import android.content.Intent;

import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.BaseActivityEventListener;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.geniusscansdk.scanflow.PluginBridge;
import com.geniusscansdk.scanflow.PromiseResult;

import java.util.Map;

public class RNGeniusScanModule extends ReactContextBaseJavaModule {
  private final ReactApplicationContext reactContext;
  private Promise mScanPromise;

  public RNGeniusScanModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
    // Add the listener for `onActivityResult`
    reactContext.addActivityEventListener(mActivityEventListener);
  }

  @Override
  public String getName() {
    return "RNGeniusScan";
  }

  // We don't work directly with Promise here as it is a React Native Bridge module
  private void resolvePromiseWithPromiseResult(Promise promise, PromiseResult promiseResult) {
    if (promiseResult.isError) {
      promise.reject(promiseResult.errorCode, promiseResult.errorMessage);
    } else if (promiseResult.result == null) {
      promise.resolve(null);
    } else {
      promise.resolve(Arguments.makeNativeMap(promiseResult.result));
    }
  }

  private final ActivityEventListener mActivityEventListener = new BaseActivityEventListener() {

    @Override
    public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent intent) {
      PromiseResult promiseResult = PluginBridge.getPromiseResultFromActivityResult(activity, requestCode, resultCode, intent);
      if (promiseResult != null) {
        resolvePromiseWithPromiseResult(mScanPromise, promiseResult);
        mScanPromise = null;
      }
    }
  };

  @SuppressWarnings("unused")
  @ReactMethod
  public void scanWithConfiguration(ReadableMap scanOptions, Promise promise) {
    mScanPromise = promise;
    PluginBridge.scanWithConfiguration(getCurrentActivity(), scanOptions.toHashMap());
  }

  @SuppressWarnings("unused")
  @ReactMethod
  public void generateDocument(ReadableMap document, ReadableMap configuration, Promise promise) {
    PromiseResult promiseResult = PluginBridge.generateDocument(getCurrentActivity(), document.toHashMap(), configuration.toHashMap());
    resolvePromiseWithPromiseResult(promise, promiseResult);
  }

  @SuppressWarnings("unused")
  @ReactMethod
  public void setLicenceKey(String licenseKey, Promise promise) {
    PromiseResult promiseResult = PluginBridge.setLicenseKey(this.reactContext, licenseKey);
    resolvePromiseWithPromiseResult(promise, promiseResult);
  }
}