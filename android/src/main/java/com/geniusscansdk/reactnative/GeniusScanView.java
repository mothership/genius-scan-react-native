package com.geniusscansdk.reactnative;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.FragmentTransaction;

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

public class GeniusScanView  extends FrameLayout {

  private ScanFragment scanFragment;

  boolean toggle = false;

  public GeniusScanView(@NonNull ThemedReactContext context) {
    super(context);
    this.setPadding(16,16,16,16);
    this.setBackgroundColor(Color.parseColor("#5FD3F3"));

    // add default text view
    Button text = new Button(context);
    text.setText("Test event");
    text.setOnClickListener(new OnClickListener() {
      @Override
      public void onClick(View v) {
        sendEventEnableTakePicture(toggle);
        toggle = !toggle;
      }
    });
    this.addView(text);


//    scanFragment = ScanFragment.createBestForDevice();
//    FragmentTransaction transaction = getContext().getCurren.beginTransaction();
//    transaction.replace(R.id.child_fragment_container, scanFragment).commit();
//
//    scanFragment.setPreviewAspectFill(false);
//    scanFragment.setRealTimeDetectionEnabled(true);
////        scanFragment.setFocusIndicator(focusIndicator);
//    scanFragment.setAutoTriggerAnimationEnabled(true);
//    scanFragment.setBorderDetectorListener(new BorderDetector.BorderDetectorListener() {
//      @Override
//      public void onBorderDetectionResult(QuadStreamAnalyzer.Result result) {
//        if (result.status == QuadStreamAnalyzer.Status.TRIGGER) {
//
//          Log.i("GENIUSSCAN", "BORDER DETECTED");
////                    takePicture();
//        } else if (result.status == QuadStreamAnalyzer.Status.NOT_FOUND) {
//          Log.i("GENIUSSCAN", "BORDER NOT DETECTED");
//        }
////                updateUserGuidance(result);
//      }
//
//      @Override
//      public void onBorderDetectionFailure(Exception e) {
//        scanFragment.setPreviewEnabled(false);
//        Log.i("GENIUSSCAN", "BORDER FAILED");
//      }
//    });

  }

  public void takePicture() {
    int i = new Random().nextInt(9);
    this.setBackgroundColor(Color.parseColor("#" + i + "" + i + "" + i + "" + i + "" + i + "" + i + ""));
//    new AlertDialog.Builder(getContext())
//            .setMessage("Take picture")
//            .setCancelable(false)
//            .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
//              @Override
//              public void onClick(DialogInterface dialog, int which) {
//
//              }
//            })
//            .show();
//    File outputFile = new File(getContext().getExternalFilesDir(null), UUID.randomUUID().toString() + ".jpeg");
//    scanFragment.takePicture(new FileImageCaptureCallback(outputFile) {
//      @Override
//      public void onImageCaptured(RotationAngle imageOrientation) {
//        Page page = new Page(outputFile);
//        new RotateTask(page, imageOrientation).execute();
//      }
//
//      @Override
//      public void onError(Exception e) {
//        Toast.makeText(getContext(), "Capture failed", Toast.LENGTH_SHORT).show();
//        Log.e("GENIUSSCAN", "Capture failed", e);
//      }
//    });
  }

  public void sendEventEnableTakePicture(boolean enable) {
    WritableMap event = Arguments.createMap();
    event.putBoolean("enable", enable);
    ReactContext reactContext = (ReactContext)getContext();
    reactContext
            .getJSModule(RCTEventEmitter.class)
            .receiveEvent(getId(), "enableTakePicture", event);
  }

  public void sendEventImageCaptured(String imagePath) {
    WritableMap event = Arguments.createMap();
    event.putString("imagePath", imagePath);
    ReactContext reactContext = (ReactContext)getContext();
    reactContext
            .getJSModule(RCTEventEmitter.class)
            .receiveEvent(getId(), "imageCaptured", event);
  }
}
