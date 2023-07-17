package com.geniusscansdk.reactnative;

import android.view.Choreographer;
import android.view.View;
import android.view.ViewGroup;
import android.view.LayoutInflater;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentActivity;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.uimanager.annotations.ReactProp;
import com.facebook.react.uimanager.annotations.ReactPropGroup;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.UIManagerHelper;

import java.util.Map;

public class GeniusScanViewManager extends SimpleViewManager<GeniusScanView> {

  public static final String REACT_CLASS = "GeniusScanView";
  public final String COMMAND_CREATE = "createFragment";
  public final int COMMAND_CREATE_ID = 1;
  private int propWidth;
  private int propHeight;

  GeniusScanFragment myFragment = null;

  ReactApplicationContext reactContext;

  public GeniusScanViewManager(ReactApplicationContext reactContext) {
    this.reactContext = reactContext;
  }

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  /**
   * Return a FrameLayout which will later hold the Fragment
   */
  @Override
  public GeniusScanView createViewInstance(ThemedReactContext reactContext) {
  System.out.println("GENIUSSCAN createViewInstance");
    //FrameLayout f = new FrameLayout(reactContext);
    //f.setBackgroundColor(0xff00ff00);
    //return f;
    GeniusScanView root = (GeniusScanView) LayoutInflater.from(reactContext)
                .inflate(R.layout.geniusscan_fragment_container, null);
        return root;
  }

  @ReactMethod
  public void takePicture(int reactTag) {
  System.out.println("GENIUSSCAN takePicture");
    reactContext.runOnUiQueueThread(new Runnable() {
      @Override
      public void run() {
        View v = UIManagerHelper.getUIManagerForReactTag(reactContext, reactTag).resolveView(reactTag);
                if (v != null && v instanceof GeniusScanView) {
                  ((GeniusScanView)v).takePicture();
                }
      }
    });
  }

  public Map getExportedCustomBubblingEventTypeConstants() {
  System.out.println("GENIUSSCAN getExportedCustomBubblingEventTypeConstants");
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

  /**
   * Map the "create" command to an integer
   */
  @Nullable
  @Override
  public Map<String, Integer> getCommandsMap() {
  System.out.println("GENIUSSCAN getCommandsMap");
    return MapBuilder.of(COMMAND_CREATE, COMMAND_CREATE_ID);
  }

  /**
   * Handle "create" command (called from JS) and call createFragment method
   */
  @Override
  public void receiveCommand(
    @NonNull GeniusScanView root,
    String commandId,
    @Nullable ReadableArray args
  ) {
  System.out.println("GENIUSSCAN receiveCommand " + commandId);
    super.receiveCommand(root, commandId, args);
    int reactNativeViewId = args.getInt(0);
    if (COMMAND_CREATE.equals(commandId)) {
        createFragment(root, reactNativeViewId);
    } else {

    int commandIdInt = Integer.parseInt(commandId);
    switch (commandIdInt) {
      case COMMAND_CREATE_ID:
        createFragment(root, reactNativeViewId);
        break;
      default: {}
    }

    }
  }
/*
  @ReactPropGroup(names = {"width", "height"}, customType = "Style")
  public void setStyle(FrameLayout view, int index, Integer value) {
  System.out.println("GENIUSSCAN setStyle index " + index + " value " + value);
    if (index == 0) {
      propWidth = value;
    }

    if (index == 1) {
      propHeight = value;
    }
  }
*/
  /**
   * Replace your React Native view with a custom fragment
   */
  public void createFragment(FrameLayout root, int reactNativeViewId) {
    System.out.println("GENIUSSCAN createFragment " + reactNativeViewId);
    GeniusScanView parentView = (GeniusScanView) root.findViewById(reactNativeViewId);
    parentView.createFragment();
    /*ViewGroup parentView = (ViewGroup) root.findViewById(reactNativeViewId);
    //setupLayout(parentView);

    myFragment = new GeniusScanFragment(reactContext);
    FragmentActivity activity = (FragmentActivity) reactContext.getCurrentActivity();
    activity.getSupportFragmentManager()
            .beginTransaction()
            .replace(reactNativeViewId, myFragment, String.valueOf(reactNativeViewId))
            .commit();
  System.out.println("GENIUSSCAN createFragment commit");
  */
  }
/*
  public void setupLayout(View view) {
  System.out.println("GENIUSSCAN setupLayout");
    Choreographer.getInstance().postFrameCallback(new Choreographer.FrameCallback() {
      @Override
      public void doFrame(long frameTimeNanos) {
        manuallyLayoutChildren(view);
        view.getViewTreeObserver().dispatchOnGlobalLayout();
        Choreographer.getInstance().postFrameCallback(this);
  System.out.println("GENIUSSCAN setupLayout doFrame");
      }
    });
  }

  public void manuallyLayoutChildren(View view) {
  System.out.println("GENIUSSCAN manuallyLayoutChildren");
      // propWidth and propHeight coming from react-native props
      int width = propWidth;
      int height = propHeight;

      view.measure(
              View.MeasureSpec.makeMeasureSpec(width, View.MeasureSpec.EXACTLY),
              View.MeasureSpec.makeMeasureSpec(height, View.MeasureSpec.EXACTLY));

      view.layout(0, 0, width, height);
  }
*/
}
