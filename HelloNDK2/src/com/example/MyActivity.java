package com.example;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MyActivity extends Activity {

    final static String TAG = "MyActivityTAG";


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        final String s = function("HELLO".getBytes());
        Log.d(TAG, s);

    }

    static {
        System.loadLibrary("native_lab1");
    }

    native String function(byte[] string);
}
