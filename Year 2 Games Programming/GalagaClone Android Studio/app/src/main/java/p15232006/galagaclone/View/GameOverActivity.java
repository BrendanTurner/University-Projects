package p15232006.galagaclone.View;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import p15232006.galagaclone.R;

public class GameOverActivity extends AppCompatActivity {
    int score;//store the score
    private int currentLevel;//store the current level number
    TextView scoreText;//initiate a text view

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_over);
        scoreText =(TextView)findViewById(R.id.score);//set the text view to the score text view widget in the game over xml
        currentLevel=getIntent().getIntExtra("levelWon",0);//get the current level number that was passed from the previous intent
        score=getIntent().getIntExtra("score",0);//pass the score in form previous intent
        scoreText.setText(String.valueOf(score));//set the text in the xml with the score
        if(currentLevel>0&&currentLevel<3) {//if its above 0 and below 3, there are only 3 levels so you cant click next level after the 3rd
            Button nextLevelButton = (Button)findViewById(R.id.nextLevel);// then make the next level button visible
            nextLevelButton.setVisibility(View.VISIBLE);
        }
    }

    public void beginGame (View view){
        //use a toast message to inform the player that the button is clicked
        Intent intentStart = new Intent(this,GameActivity.class);

        //start the intent that was created
        startActivity(intentStart);
    }

    public void home (View view){
        Intent intentStart = new Intent(this,SplashActivity.class);
        startActivity(intentStart);
    }

    public void nextLevel(View view){
        //finishActivity(1);
        Intent intentStart = new Intent(this,GameActivity.class);//start a new intent back to the game activity
        intentStart.putExtra("nextLevel",currentLevel);//pass through the new level number
        startActivityForResult(intentStart,1);//start the game activity
    }
}
