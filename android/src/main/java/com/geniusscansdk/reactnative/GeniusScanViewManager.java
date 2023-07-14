package com.geniusscansdk.reactnative;

import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.UIManagerHelper;

import java.util.Map;

public class GeniusScanViewManager extends SimpleViewManager<GeniusScanView> {
  public static final String REACT_CLASS = "GeniusScanView";

  private final ReactApplicationContext mReactContext;

  public GeniusScanViewManager(ReactApplicationContext reactApplicationContext) {
    mReactContext = reactApplicationContext;
  }

  @Override
  @NonNull
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  @NonNull
  public GeniusScanView createViewInstance(ThemedReactContext reactContext) {
    return new GeniusScanView(reactContext);
  }

  @ReactMethod
  public void takePicture(int reactTag) {
    mReactContext.runOnUiQueueThread(new Runnable() {
      @Override
      public void run() {
        View v = UIManagerHelper.getUIManagerForReactTag(mReactContext, reactTag).resolveView(reactTag);
        if (v != null && v instanceof GeniusScanView) {
          ((GeniusScanView)v).takePicture();
        }
      }
    });
  }

  public final int COMMAND_CREATE_FRAGMENT = 1;

  @Nullable
  @Override
  public Map<String, Integer> getCommandsMap() {
    return MapBuilder.of(
            "createFragment", COMMAND_CREATE_FRAGMENT
            );
  }

  @Override
  public void receiveCommand(@NonNull GeniusScanView root, String commandId, @Nullable ReadableArray args) {
    super.receiveCommand(root, commandId, args);
    int reactNativeViewId = args.getInt(0);
    int commandIdInt = Integer.parseInt(commandId);

    switch (commandIdInt) {
      case COMMAND_CREATE_FRAGMENT:
        createFragment(root, reactNativeViewId);
        break;
      default: {}
    }
  }

  private void createFragment(@NonNull GeniusScanView root, int reactNativeViewId) {

  }

  public Map getExportedCustomBubblingEventTypeConstants() {
    return MapBuilder.builder().put(
            "enableTakePicture",
            MapBuilder.of(
                    "phasedRegistrationNames",
                    MapBuilder.of("bubbled", "onEnableTakePicture")
            )
    ).put(
            "imageCaptured",
            MapBuilder.of(
                    "phasedRegistrationNames",
                    MapBuilder.of("bubbled", "onImageCaptured")
            )
    ).build();
  }
}
