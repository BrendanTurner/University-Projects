package p15232006.galagaclone.View;

import android.graphics.Point;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

import p15232006.galagaclone.R;

public class GameActivity extends AppCompatActivity {
    private GameSurfaceView gsv;//initialize a game surface view
    Point screenSize = new Point();//initialize a point to store the screen size
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        int currentLevel=getIntent().getIntExtra("nextLevel",0);//get the current level from previous intent(if possible)
        super.onCreate(savedInstanceState);
        int mUIFlag = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                |View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                |View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                |View.SYSTEM_UI_FLAG_LOW_PROFILE
                |View.SYSTEM_UI_FLAG_FULLSCREEN
                |View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                |View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
        //set the flags on the view
        getWindow().getDecorView().setSystemUiVisibility(mUIFlag);
        this.getWindowManager().getDefaultDisplay().getSize(screenSize);//get screen size and store in the point

        gsv = new GameSurfaceView(this,screenSize,currentLevel);//create the game surface view passign in the context and the recently aquired screen size(and the current level number which defaults to zero first time around)
        setContentView(gsv);//set the game surface view to be the current view
        gsv.resume();//have to call resume to start
    }

    public boolean onTouchEvent(MotionEvent event){//check for touch events
        float xPos;//to store the touch input x
        float yPos;//and y
        int eventaction = event.getAction();//to store the action
        switch(eventaction){//switch statement
            case MotionEvent.ACTION_DOWN://if action is a press
                if(!gsv.isOk()){
                gsv.resume();
                }
                //finger touches the screen
                xPos = event.getX();yPos = event.getY();//store the co-ordinates
                gsv.pressUpdate(xPos,yPos);//and update the gamesurface view
                break;
            case MotionEvent.ACTION_MOVE://if action is move
                //finger moves on the screen
                xPos = event.getX();yPos = event.getY();//do the same
                gsv.pressUpdate(xPos,yPos);//as before
                break;
            case MotionEvent.ACTION_UP://finger leaves screen
                gsv.stopUpdate();//tell the surface view no more presses
                break;
        }
        //tell the system that we handled the event and
        // no further processing is required
        //gsv.pressUpdate(xPos,yPos);
        return true;
    }

    @Override
    public void onBackPressed() {//when back is pressed
        gsv.pause();//simply pause the game instead
        Toast.makeText(this,"Game Paused",Toast.LENGTH_SHORT).show();//display it has been paused

    }

    @Override
    protected void onUserLeaveHint() {
        gsv.pause();//simply pause the game instead
        }
}
