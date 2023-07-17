package com.geniusscansdk.reactnative;

import android.os.Handler;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Color;
import android.util.Log;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentTransaction;
import androidx.fragment.app.FragmentActivity;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.events.RCTEventEmitter;
import com.geniusscansdk.camera.FileImageCaptureCallback;
import com.geniusscansdk.camera.ScanFragment;
import com.geniusscansdk.camera.realtime.BorderDetector;
import com.geniusscansdk.core.QuadStreamAnalyzer;
import com.geniusscansdk.core.RotationAngle;

import java.io.File;
import java.util.Random;
import java.util.UUID;

public class GeniusScanView extends FrameLayout {

  private GeniusScanFragment geniusScanFragment;

    public GeniusScanView(@NonNull Context context) {
        super(context);
        //createFragment();
    }

    public GeniusScanView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        //createFragment();
    }

    public GeniusScanView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        //createFragment();
    }

    public GeniusScanView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        //createFragment();
    }

  public void createFragment() {
  System.out.println("GENIUSSCAN GeniusScanView createFragment");

  //new Handler().postDelayed(new Runnable() {
      System.out.println("GENIUSSCAN GeniusScanView createFragment run");
      ReactContext reactContext = (ReactContext)getContext();
      geniusScanFragment = new GeniusScanFragment(reactContext);
      FragmentActivity activity = (FragmentActivity) reactContext.getCurrentActivity();
      activity.getSupportFragmentManager().beginTransaction().replace(R.id.container, geniusScanFragment).commit();
  //}, 200);

  }

  public void takePicture() {
    geniusScanFragment.takePicture();
  }
}
