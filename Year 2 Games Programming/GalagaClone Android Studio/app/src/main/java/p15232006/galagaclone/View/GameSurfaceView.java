package p15232006.galagaclone.View;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.os.Process;
import android.os.SystemClock;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;

import java.util.ArrayList;

import p15232006.galagaclone.Model.Alien;
import p15232006.galagaclone.Model.AlienFleet;
import p15232006.galagaclone.Model.Background;
import p15232006.galagaclone.Model.Projectile;
import p15232006.galagaclone.Model.Ship;
import p15232006.galagaclone.Presenter.Collision;
import p15232006.galagaclone.R;

/**
 * Created by p15232006 on 06/02/2018.
 */

public class GameSurfaceView extends SurfaceView implements Runnable{
    Paint textPaint=new Paint();//paint for the text
    SurfaceHolder holder;
    private boolean ok = false;//boolean to control pause and resume
    private Thread t = null;//thread for the game logic
    private float touchX;//store the Coords from a touch input for x pos
    private float touchY;//same for y
    private int currentLevel=0;//store the current level number
    private float score=100;// store the score// starts at 100 and decreases over time
    private long lastFrameTime=0;//the time it was last frame
    private Bitmap galagaSpriteSheet;//the sprite sheet to be passed to everything else
    public static float spriteScale;//each device will have a different pixel density, this stores the scale for use when geting each sprite
    Background background;//initialize the background object
    Point screenSize;//store the screen size
    //Game Objects
    Ship ship;//initialize the player ship
    ArrayList<Projectile> projectiles =new ArrayList<Projectile>();//initialize the array to store projectiles
    ArrayList<Alien> aliens =new ArrayList<Alien>();//initialize the array to store the aliens
    AlienFleet fleet =new AlienFleet();//new alien fleet constructor object

    //constructor
    public GameSurfaceView(Context context, Point screenS,int currentLevelIn) {
        super(context);
        textPaint.setColor(Color.YELLOW);//colour of the paint
        textPaint.setTextSize(100);//size of the text
        currentLevel=currentLevelIn;//current level is passed in form the game activity
        spriteScale=context.getResources().getDisplayMetrics().density*2;// the sprites have to be twice the size so this takes the density of the device screen and doubles it
        holder = getHolder();
        screenSize=screenS;//hold the screensize to position everything
        galagaSpriteSheet= BitmapFactory.decodeResource(context.getResources(), R.drawable.galaga_sheet);//load in the image
        galagaSpriteSheet =Bitmap.createScaledBitmap(galagaSpriteSheet,galagaSpriteSheet.getWidth()*2,galagaSpriteSheet.getHeight()*2,false);//scale the image
        background=new Background(context,screenSize);//create the background object
        ship = new Ship(screenSize,galagaSpriteSheet);//create the ship object
        switch (currentLevel) {//compare the current level to
            case 0://if 0 add the level 1 aliens
                aliens = fleet.level1Construct(screenSize, galagaSpriteSheet);//populate the aliens array with the fleet made from the alien fleet class
                break;
            case 1://if 1 then add level 2 aliens
                aliens = fleet.level2Construct(screenSize, galagaSpriteSheet);//populate the aliens array with the fleet made from the alien fleet class
                break;
            case 2://and if 2 add the level 3 aliens
                aliens = fleet.level3Construct(screenSize, galagaSpriteSheet);//populate the aliens array with the fleet made from the alien fleet class
                break;
        }
    }

    private void UpdateCanvas(Canvas canvas){
        long elapsedTime=SystemClock.elapsedRealtime();//set the elapsed time
        if(elapsedTime-lastFrameTime>=20) {//compare it to last frame update, if its greater then 20(50fps), then update a frame
            score -=0.02;//decrease the score gradualy until the game is over
            background.update();//update the background so it can scroll
            ship.update(getContext(), galagaSpriteSheet, touchX, touchY, projectiles);//update the ship
            for (int i = 0; i < aliens.size(); i++) {//for each alien
                aliens.get(i).update(getContext(), galagaSpriteSheet, projectiles,ship);//update the alien
                if (aliens.get(i).isDestroy()) {//check if each alien is destroyed
                    aliens.remove(i);//if so then remove
                    score += 10;//each alien
                }
            }
            if (aliens.size() == 0) {//if all the aliens are dead
                currentLevel++;//set the current level to to the next
                Intent intentStart = new Intent(getContext(), GameOverActivity.class);//create an intent to go to the end level activity
                intentStart.putExtra("levelWon", currentLevel);//pass through the current level
                intentStart.putExtra("score",(int)score);
                getContext().startActivity(intentStart);//start the end game activity
            }
            for (int i = 0; i < projectiles.size(); i++) {//for each projectile
                projectiles.get(i).update();//update each projectile
            }
            for (int i = 0; i < projectiles.size(); i++) {//for each projectile
                Collision.hasCollided(projectiles.get(i), ship);//check a collision with the ship
                for (int j = 0; j < aliens.size(); j++) {//and for each alien
                    Collision.hasCollided(projectiles.get(i), aliens.get(j));//check each projectile with each ship
                }
            }
            for (int i = 0; i < projectiles.size(); i++) {//for each projectile
                if (projectiles.get(i).isDestroy()) {//if they are destroyed
                    projectiles.remove(i);//then remove them
                }
            }
            for (int i =0;i<aliens.size();i++){//for each alien
                Collision.hasCollided(ship,aliens.get(i));//check if it has collided with the ship
            }
            if (ship.getLives() == 0) {//if all lives are lost
                currentLevel = 0;
                Intent intentStart = new Intent(getContext(), GameOverActivity.class);//create an intent to go to the end level activity
                intentStart.putExtra("score",(int)score);
                getContext().startActivity(intentStart);//start the end game activity
            }
            lastFrameTime=elapsedTime;
            this.DrawCanvas(canvas);//paint canvas
        }
    }

    protected void DrawCanvas(Canvas canvas){
        //draw everything
        background.draw(canvas);
        ship.draw(canvas);
        for(int i=0;i<projectiles.size();i++){//loop through all projectiles that exist and draw them
            projectiles.get(i).draw(canvas);
        }
        for(int i=0;i<aliens.size();i++){//same with aliens
            aliens.get(i).draw(canvas);
        }
        canvas.drawText("score:"+String.valueOf((int)score),100,100,textPaint);
    }

    public void run(){
        //remove conflict between UI thread and game thread

        android.os.Process.setThreadPriority(Process.THREAD_PRIORITY_BACKGROUND);
        stopUpdate();//call this once to stop the game registering taping start game as an input at the begining

        while (ok){//while not paused
            //perform canvas drawing
            if(!holder.getSurface().isValid()) {//if surface is not valid
                continue;//skip anything below it
            }
            Canvas c = holder.lockCanvas();//lock canvas
            this.UpdateCanvas(c);//update everything on the canvas
            holder.unlockCanvasAndPost(c);//unlock canvas
        }
    }

    public void pressUpdate(float xPos,float yPos){//if a touch has been registered on screen
        touchX=xPos;//store the x position of the touch
        touchY=yPos;//and the y
    }

    public void stopUpdate(){//when a touch is no longer registered
        touchX=screenSize.x/2;//reset the variable back to neutral(in this case the middle of the screen)
        touchY=ship.getyPos();//reset the y variable to the ships y(this is only used for firering when a touch is above the ship)
    }

    public void pause(){
        ok = false;
        while(true){
            try{
                t.join();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
            break;
        }
        t = null;
    }
    public void resume(){
        ok = true;
        t = new Thread(this);
        t.start();
    }

    public boolean isOk() {
        return ok;
    }
}
