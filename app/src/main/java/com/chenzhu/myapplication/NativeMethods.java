package com.chenzhu.myapplication;

import android.app.Activity;
import android.widget.Toast;

public class NativeMethods {
    static {
        System.loadLibrary("native-lib");
    }

    Activity activity;
    NativeMethods(Activity activity){
        this.activity=activity;
    }

    public native String  NativeHttpGet(String url);
    public native String  NativeHttpPost(String url,String jsonRequest);
   /**
    * @param  savePath   应该是有后缀名的 如：aa.txt ,debug.apk  ....
    ***/
    public native String  NativeHttpDownLoad(String url,String savePath);

    public void  callBackFromNDK(final int type, final String result){
         activity. runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(activity,"------------->it is over:"+type+"result:"+result,Toast.LENGTH_LONG).show();
            }
        });
    }

    public void  callProgressFromNDK(final double  progress){
       System.out.println("---->>>"+progress);
       if (progress==100){
           activity. runOnUiThread(new Runnable() {
               @Override
               public void run() {
                   Toast.makeText(activity,"下载完成",Toast.LENGTH_LONG).show();
               }
           });
       }
    }

}
