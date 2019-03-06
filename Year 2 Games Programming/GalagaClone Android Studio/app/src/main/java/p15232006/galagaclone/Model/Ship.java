package p15232006.galagaclone.Model;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Point;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.util.Log;

import java.util.ArrayList;

import p15232006.galagaclone.R;

import static p15232006.galagaclone.View.GameSurfaceView.spriteScale;

/**
 * Created by p15232006 on 06/02/2018.
 */

public class Ship extends GameObject{
    private boolean explodedStart=false;//a boolean to set the ship to a state where it will begin to explode
    private boolean explodedFinish=false;//once the ship has exploded set this so it can be removed
    private int explosionCounter=0;//a counter to cycle through the exploding animation
    private ArrayList<Bitmap>explosion=new ArrayList<Bitmap>();//store the explosion bitmaps
    private ArrayList<Bitmap>shipState=new ArrayList<Bitmap>();//store the ships bitmaps
    private int iShipState=6;//a counter to cycle through the ship sprites
    private Bitmap currentSprite;//the current sprite that is drawn
    private int fireCounter=5;//a counter to limit how many times you can fire
    private int lives=3;//the ship has 3 lives

    public Ship(Point p, Bitmap b) {
        Matrix matrixMirror=new Matrix();//a matrix to mirror the sprites on the sheet for when the ship is going right
        matrixMirror.preScale(-1.0f,1.0f);//the mirror matrix
        setScreenSize(p);//store the screen size
        setSpeed(20);//the speed at which the ship moves
                //all sizes and positions are scaled up by the pixel density and then doubled again compared to the source PNG
        for(int i=0;i<8;i++){//there are 8 sprites for the ship animation
            shipState.add(Bitmap.createBitmap(b,i*24*(int)spriteScale,8*(int)spriteScale,16*(int)spriteScale,16*(int)spriteScale));//add each bitmap to the array
        }

        for(int i=5;i>-1;i--){//and 5 extra sprites need to be duplicated and mirrored
            shipState.add(Bitmap.createBitmap(shipState.get(i),0,0,shipState.get(i).getWidth(),shipState.get(i).getHeight(),matrixMirror,false));//this is using the mirror matrix
        }

        currentSprite=shipState.get(6);//set the ships starting position

        explosion.add(Bitmap.createBitmap(b,193*(int)spriteScale,0,32*(int)spriteScale,32*(int)spriteScale));//add the 4 explosion sprites to an array
        explosion.add(Bitmap.createBitmap(b,231*(int)spriteScale,0,32*(int)spriteScale,32*(int)spriteScale));//could have been done in a for loop
        explosion.add(Bitmap.createBitmap(b,272*(int)spriteScale,0,32*(int)spriteScale,32*(int)spriteScale));
        explosion.add(Bitmap.createBitmap(b,312*(int)spriteScale,0,32*(int)spriteScale,32*(int)spriteScale));

        setWidth(currentSprite.getWidth());//set the width value to that off the sprite to check collides
        setHeight(currentSprite.getHeight());//and the height
        setxPos((p.x/2)-getWidth());//the initial position of the ship(center of screen
        setyPos(p.y-getHeight());//and bottom of screen
    }

    public void setExplodedStart(boolean b){//this is called when a collision has happened
        this.explodedStart=b;//set the ship to start exploding
            }

    public void update(Context c, Bitmap b,float xTouchIn,float yTouchIn,ArrayList<Projectile> proj){//update the ship
        if(xTouchIn>(getScreenSize().x/2)+100){//if the touch on the screen is 100 or more to the right of the center
            if(iShipState<shipState.size()-1){//if the current sprite is not currently the last sprite
                iShipState++;//move to the next sprite
                currentSprite=shipState.get(iShipState);//set the current sprite
            }
            setxPos(getxPos()+getSpeed());//update the position of the ship
            if((getxPos()+getWidth())>getScreenSize().x){//check its not out of bounds
                setxPos(getScreenSize().x-getWidth());//if so reset the ship to just inside bounds
            }
        }
        if(xTouchIn<(getScreenSize().x/2)-100){//repeat above code but for the other side of the screen
            if(iShipState>0){
                iShipState--;
                currentSprite=shipState.get(iShipState);
            }
            setxPos(getxPos()-getSpeed());
            if(getxPos()<0){
                setxPos(0);
            }
        }
        if(xTouchIn==getScreenSize().x/2){//if screen is not pressed(touch in is at neutral position
            currentSprite=shipState.get(6);//reset ship to idol sprite state
            iShipState=6;
        }

        if(getyPos()-getHeight()>yTouchIn){//if the y input of the touch is above the ship
            if(fireCounter%5==0) {//every 5 updates
                proj.add(new Projectile(getxPos() + (getWidth() / 2), getyPos(), c, getScreenSize(), b, false));//"fire a projectile
                fireCounter=0;//once a projectile has been fired, reset the fire counter back to zero
            }
        }
        if(explodedFinish){//after the explosion animation has finished
            lives--;//decrease lives by 1
            explodedFinish=false;//reset the booleans
            explodedStart=false;//to allow the animation to play again later
            setxPos((getScreenSize().x/2)-getWidth());//the initial position of the ship(center of screen
            setyPos(getScreenSize().y-getHeight());//and bottom of screen
            currentSprite=shipState.get(6);
            proj.clear();
        }
        if(explodedStart) {//if the ship has been set to explode
            if(explosionCounter==0){//if the ship hasnt changed to an explosion sprite yet
                setxPos(getxPos()-8*7);//and adjust the x and y positions to cater for the larger sprite
                setyPos(getyPos()-8*7);
            }
            if (explosionCounter < 4) {//if the current sprite isnt the last sprite of the explode animation
                currentSprite = explosion.get(explosionCounter);//set the current sprite to the current explode stage
                explosionCounter++;//then update the explode stage

            }
            if (explosionCounter >= 4) {//if the last explosion stage has been drawn
                explodedFinish = true;//set the ship to be removed
                explosionCounter=0;
            }
        }
        fireCounter++;//increment the fire counter

    }
    public void draw(Canvas c){//draw the ship to canvas provided
        c.drawBitmap(currentSprite,getxPos(),getyPos(),null);
    }

    public int getLives(){return lives;}

}
