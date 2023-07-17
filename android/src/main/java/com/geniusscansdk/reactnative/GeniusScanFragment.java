package com.geniusscansdk.reactnative;

import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.events.RCTEventEmitter;

import com.geniusscansdk.camera.FileImageCaptureCallback;
import com.geniusscansdk.camera.ScanFragment;
import com.geniusscansdk.camera.realtime.BorderDetector;
import com.geniusscansdk.core.GeniusScanSDK;
import com.geniusscansdk.core.LicenseException;
import com.geniusscansdk.core.QuadStreamAnalyzer;
import com.geniusscansdk.core.RotationAngle;

import java.io.File;
import java.util.UUID;

public class GeniusScanFragment extends Fragment implements ScanFragment.CameraCallbackProvider {

    private ScanFragment scanFragment;
    private ReactContext reactContext;

    public GeniusScanFragment(ReactContext context) {
        super();
        reactContext = context;
    }

    public void sendEventEnableTakePicture(boolean enable) {
  System.out.println("GENIUSSCAN sendEventEnableTakePicture");
        WritableMap event = Arguments.createMap();
        event.putBoolean("enable", enable);
        reactContext
                .getJSModule(RCTEventEmitter.class)
                .receiveEvent(getId(), "enableTakePicture", event);
    }

    public void sendEventImageCaptured(String imagePath) {
  System.out.println("GENIUSSCAN sendEventImageCaptured");
        WritableMap event = Arguments.createMap();
        event.putString("imagePath", imagePath);
        reactContext
                .getJSModule(RCTEventEmitter.class)
                .receiveEvent(getId(), "imageCaptured", event);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
  System.out.println("GENIUSSCAN onCreateView");
        return inflater.inflate(R.layout.generic_fragment_container, container, true);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
  System.out.println("GENIUSSCAN onViewCreated");
        scanFragment = ScanFragment.createBestForDevice();
        FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
        transaction.replace(R.id.child_fragment_container, scanFragment).commit();

        scanFragment.setPreviewAspectFill(true);
        scanFragment.setRealTimeDetectionEnabled(true);
//        scanFragment.setFocusIndicator(focusIndicator);
        scanFragment.setAutoTriggerAnimationEnabled(false);
        scanFragment.setBorderDetectorListener(new BorderDetector.BorderDetectorListener() {
            @Override
            public void onBorderDetectionResult(QuadStreamAnalyzer.Result result) {
                if (result.status == QuadStreamAnalyzer.Status.TRIGGER) {
  System.out.println("GENIUSSCAN borded detected");
                    sendEventEnableTakePicture(true);
                } else if (result.status == QuadStreamAnalyzer.Status.NOT_FOUND) {
  System.out.println("GENIUSSCAN border not detected");
                    sendEventEnableTakePicture(false);
                }
            }

            @Override
            public void onBorderDetectionFailure(Exception e) {
  System.out.println("GENIUSSCAN onBorderDetectionFailure");
                scanFragment.setPreviewEnabled(false);
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();
  System.out.println("GENIUSSCAN onResume");
        scanFragment.initializeCamera();
    }

    public void takePicture() {
        File outputFile = new File(getContext().getExternalFilesDir(null), UUID.randomUUID().toString() + ".jpeg");
        scanFragment.takePicture(new FileImageCaptureCallback(outputFile) {
            @Override
            public void onImageCaptured(RotationAngle imageOrientation) {
  System.out.println("GENIUSSCAN onImageCaptured");
                Page page = new Page(outputFile);
                new RotateTask(page, imageOrientation).execute();
            }

            @Override
            public void onError(Exception e) {
  System.out.println("GENIUSSCAN captureFailed");
            }
        });
    }

    @Override
    public ScanFragment.Callback getCameraCallback() {
        return new ScanFragment.Callback() {
            @Override
            public void onCameraReady() {
  System.out.println("GENIUSSCAN onCameraReady");
            }

            @Override
            public void onCameraFailure() {
  System.out.println("GENIUSSCAN onCameraFailure");
            }

            @Override
            public void onShutterTriggered() {
  System.out.println("GENIUSSCAN onShutterTriggered");
            }

            @Override
            public void onPreviewFrame(byte[] bytes, int width, int height, int format) {
            }
        };
    }

    class RotateTask extends AsyncTask<Void, Void, Void> {

        private final RotationAngle rotationAngle;
        private final Page page;
        private ProgressDialog progressDialog;
        private Exception exception = null;

        RotateTask(Page page, RotationAngle rotationAngle) {
            this.rotationAngle = rotationAngle;
            this.page = page;
        }

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            progressDialog = new ProgressDialog(getContext());
            progressDialog.show();
        }

        @Override
        protected Void doInBackground(Void... params) {
            String path = page.getOriginalImage().getAbsolutePath();
            // Even if rotation angle is 0, we perform a rotation to apply exif orientation
            try {
                GeniusScanSDK.rotateImage(path, path, rotationAngle);
                // original image was rotated, let's reprocess it
                new PageProcessor().processPage(getContext(), page);
            } catch (Exception e) {
                exception = e;
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            super.onPostExecute(aVoid);
            progressDialog.dismiss();

            if (exception instanceof LicenseException) {
                new AlertDialog.Builder(getContext())
                        .setMessage(exception.getMessage())
                               .setPositiveButton("ok", null)
                        .show();
            } else if (exception != null) {
                throw new RuntimeException(exception);
            } else {
                sendEventImageCaptured(page.getEnhancedImage().getAbsolutePath());
            }
        }
    }
}
