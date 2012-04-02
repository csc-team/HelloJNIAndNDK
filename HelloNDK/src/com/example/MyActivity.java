package com.example;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MyActivity extends Activity {
    static {
        System.loadLibrary("example");
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        final TextView textView = (TextView) findViewById(R.id.text_field);
        textView.setText(getString());
    }

    native String getString();

}
