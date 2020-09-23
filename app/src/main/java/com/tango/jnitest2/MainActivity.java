package com.tango.jnitest2;

import android.os.Bundle;
import android.widget.TextView;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.Toast;


//   <uses-permission android:name="android.permission.INTERNET"></uses-permission>
//   <uses-permission android:name="android.permission.CHANGE_NETWORK_STATE"></uses-permission>
//    <uses-permission android:name="android.permission.CHANGE_WIFI_STATE"></uses-permission>
//    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"></uses-permission>
//    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE"></uses-permission>



public class MainActivity extends AppCompatActivity {

    private Button button1;
    private Button button2;
    private TextView textView;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        button1 = findViewById(R.id.button1);
        //注册监听器
        button1.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                textView.setText("button1");
                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(stringFromJNI());
            }
        });

        button2 = findViewById(R.id.button2);
        //注册监听器
        button2.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                textView.setText("button2");
                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(stringFromJNI());
            }
        });

        textView = (TextView) findViewById(R.id.textView);




        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        textView.setText("hello1");
        //socketSend();
        
        //timer.schedult(timerTask,0,1000);


        //tv.setText(stringFromJNI()+addValue(1,2));
       //tv.setText(stringFromJNI()+stringFromJNI2());
    }



    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromJNI2();
    public native int addValue(int a,int b);
    public native int socketSend( );
}
