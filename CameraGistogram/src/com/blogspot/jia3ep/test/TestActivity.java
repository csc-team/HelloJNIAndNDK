package com.blogspot.jia3ep.test;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;

import java.io.IOException;

//import android.hardware.Camera.PreviewCallback;

//----------------------------------------------------------------------

class HistogramView extends View {
    int[] mBlueHistogram;
    int[] mGreenHistogram;
    int[] mRedHistogram;

    Paint mPaintBlue;
    Paint mPaintGreen;
    Paint mPaintRed;

    public long histogram_cpp_;

    public native void decodeYUV420SP(long cppobj, byte[] yuv, int width, int height);

    private native void calculateHistogram(long cppobj, int[] r_histogram, int[] g_histogram, int[] b_histogram);

    private native void doneCppSide(long cppobj);

    private native long initCppSide();

    private native int getMaxHeight(long cppobj);

    private native int getHeight(long cppobj);

    private native int getWidth(long cppobj);

    public HistogramView(Context context) {
        super(context);
        histogram_cpp_ = initCppSide();

        mPaintRed = new Paint();
        mPaintRed.setStyle(Paint.Style.FILL);
        mPaintRed.setColor(Color.RED);
        mPaintRed.setAntiAlias(true);

        mPaintGreen = new Paint();
        mPaintGreen.setStyle(Paint.Style.FILL);
        mPaintGreen.setColor(Color.GREEN);
        mPaintGreen.setAntiAlias(true);

        mPaintBlue = new Paint();
        mPaintBlue.setStyle(Paint.Style.FILL);
        mPaintBlue.setColor(Color.BLUE);
        mPaintBlue.setAntiAlias(true);

        mRedHistogram = new int[256];
        mGreenHistogram = new int[256];
        mBlueHistogram = new int[256];
    }

    @Override
    protected void onDraw(Canvas canvas) {
        int canvasWidth = canvas.getWidth();
        int canvasHeight = canvas.getHeight();
        int newImageWidth = canvasWidth;
        int marginWidth = (canvasWidth - newImageWidth) / 2;

        calculateHistogram(histogram_cpp_, mRedHistogram, mGreenHistogram, mBlueHistogram);

        // Draw intensity histogram
        final float barWidth = ((float) newImageWidth) / 256;
        final float norm = getMaxHeight(histogram_cpp_) / (canvasHeight / 2);
        float prev_blue_h = canvasHeight;
        float prev_red_h = canvasHeight;
        float prev_green_h = canvasHeight;
        float prev_x = marginWidth;
        for (int bin = 0; bin < 256; bin++) {
            final float new_blue_h = canvasHeight - mBlueHistogram[bin] / norm;
            canvas.drawLine(prev_x, prev_blue_h, prev_x + barWidth, new_blue_h, mPaintBlue);

            final float new_red_h = canvasHeight - mRedHistogram[bin] / norm;
            canvas.drawLine(prev_x, prev_red_h, prev_x + barWidth, new_red_h, mPaintRed);

            final float new_green_h = canvasHeight - mGreenHistogram[bin] / norm;
            canvas.drawLine(prev_x, prev_green_h, prev_x + barWidth, new_green_h, mPaintGreen);

            prev_x += barWidth;
            prev_blue_h = new_blue_h;
            prev_red_h = new_red_h;
            prev_green_h = new_green_h;
        } // bin

        super.onDraw(canvas);
    } // end onDraw method    
}

//----------------------------------------------------------------------

class Preview extends SurfaceView implements SurfaceHolder.Callback {
    Camera camera_;
    boolean finished_;
    SurfaceHolder holder_;
    HistogramView histogram_view_;

    Preview(Context context, HistogramView hv) {
        super(context);
        histogram_view_ = hv;

        finished_ = false;

        // Install a SurfaceHolder.Callback so we get notified when the
        // underlying surface is created and destroyed.
        holder_ = getHolder();
        holder_.addCallback(this);
        holder_.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        // Now that the size is known, set up the camera parameters and begin
        // the preview.
        Camera.Parameters parameters = camera_.getParameters();
        parameters.setPreviewSize(320, 240);
        parameters.setPreviewFrameRate(25);
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_AUTO);
        camera_.setParameters(parameters);
        camera_.startPreview();
    }

    public void surfaceCreated(SurfaceHolder holder) {
        camera_ = Camera.open();
        try {
            camera_.setPreviewDisplay(holder);
            camera_.setPreviewCallback(new PreviewCallback() {
                public void onPreviewFrame(byte[] data, Camera camera) {
                    if (finished_)
                        return;

                    // Initialize the draw-on-top companion
                    Camera.Parameters params = camera.getParameters();
                    histogram_view_.decodeYUV420SP(histogram_view_.histogram_cpp_, data, params.getPreviewSize().width, params.getPreviewSize().height);
                    histogram_view_.invalidate();
                }
            });

        } catch (IOException exception) {
            camera_.release();
            camera_ = null;
        }
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        // Surface will be destroyed when we return, so stop the preview.
        // Because the CameraDevice object is not a shared resource, it's very
        // important to release it when the activity is paused.
        finished_ = true;
        camera_.setPreviewCallback(null);
        camera_.stopPreview();
        camera_.release();
        camera_ = null;
    }
}

//----------------------------------------------------------------------

public class TestActivity extends Activity {
    static {
        System.loadLibrary("test");
    }

    private Preview preview_;
    private HistogramView histogram_view_;

    private native String get_text_from_cpp();

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        setTitle(get_text_from_cpp());

        histogram_view_ = new HistogramView(this);
        preview_ = new Preview(this, histogram_view_);
        setContentView(preview_);
        addContentView(histogram_view_, new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
    }
}