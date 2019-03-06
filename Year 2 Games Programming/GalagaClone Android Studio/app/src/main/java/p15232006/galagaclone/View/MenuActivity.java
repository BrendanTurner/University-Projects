package p15232006.galagaclone.View;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import p15232006.galagaclone.R;

public class MenuActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
    }
    public void beginGame (View view){
        //use a toast message to inform the player that the button is clicked
        Intent intentStart = new Intent(this,GameActivity.class);

        //start the intent that was created
        startActivityForResult(intentStart,1);
    }

    public void runSettings (View view){
        //use a toast message to inform the player that the button is clicked
        Intent intentStart = new Intent(this,SettingsActivity.class);
        startActivity(intentStart);
    }
    public void home (View view){
        Intent intentStart = new Intent(this,SplashActivity.class);
        startActivity(intentStart);
    }
}
