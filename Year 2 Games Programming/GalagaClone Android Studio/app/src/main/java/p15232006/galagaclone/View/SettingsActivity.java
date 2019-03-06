package p15232006.galagaclone.View;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;

import p15232006.galagaclone.R;

public class SettingsActivity extends AppCompatActivity {
    SeekBar s;//initiate a seek bar
    AudioManager audioManager;//initiate an audiomanager

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setVolumeControlStream(AudioManager.STREAM_MUSIC);//set the toggleable volume stream as music in this activity
        setContentView(R.layout.activity_settings);
        s=(SeekBar)findViewById(R.id.seekBar);//link the seek bar to the seekbar in the view
        audioManager=(AudioManager)getSystemService(Context.AUDIO_SERVICE);//set the audio manager to this activity
        s.setMax(audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC));//set the max of the seekbar to the max of the music stream
        s.setProgress(audioManager.getStreamVolume(AudioManager.STREAM_MUSIC));//set the progress of the seekbar to the music stream
        s.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {//create a listener for the seekbar changing
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onProgressChanged(SeekBar seekBar,int progress,boolean fromUser) {//on progress changed
                audioManager.setStreamVolume(AudioManager.STREAM_MUSIC,progress,0);//reflect that on the music stream
            }
        });
    }

    public void back(View view){
        Intent intentStart = new Intent(this,MenuActivity.class);

        //start the intent that was created
        startActivity(intentStart);
    }
}
