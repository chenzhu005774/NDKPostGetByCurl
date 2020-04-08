package com.chenzhu.myapplication;
import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button button;
    Button button1;
    Button button2;

    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE};


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button =findViewById(R.id.bottom);
        button1 =findViewById(R.id.bottom1);
        button2 =findViewById(R.id.bottom2);


        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.LOLLIPOP) {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, PERMISSIONS_STORAGE, 100);
            }
        }


        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
              new NativeMethods(MainActivity.this).NativeHttpGet("http://www.weather.com.cn/data/sk/101270101.html");
            }
        });

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new NativeMethods(MainActivity.this).NativeHttpPost("http://www.weather.com.cn/data/sk/101270101.html","{\"aa\": \"123123\"}");
            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                new NativeMethods(MainActivity.this).NativeHttpDownLoad("http://192.168.1.23:8080/love.mp4","/sdcard/love.mp4");
            }
        });
   }

}
