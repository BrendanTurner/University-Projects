package p15232006.galagaclone.View;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import p15232006.galagaclone.R;

public class SplashActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);
    }
    public void startGame (View view){
        //create an intent to run from the press of the button
        Intent intentStart = new Intent(this,MenuActivity.class);

        //start the intent that was created
        startActivity(intentStart);
    }
}
