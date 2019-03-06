package p15232006.galagaclone.Model;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Point;
import android.util.Log;

import java.util.ArrayList;

import p15232006.galagaclone.Presenter.AlienAI;

import static p15232006.galagaclone.View.GameSurfaceView.spriteScale;

/**
 * Created by p15232006 on 09/02/2018.
 */

public class Alien extends GameObject {
    private boolean explodedStart = false;//a boolean to set the alien to a state where it will begin to explode
    private boolean explodedFinish = false;//once the alien has exploded set this so it can be removed
    private boolean movingLeft=false;
    private int explosionCounter = 0;//a counter to cycle through the exploding animation
    private int iAlienState=6;//a counter to cycle through the alien sprites
    private int alientype;
    private ArrayList<Bitmap> explosion = new ArrayList<>();//store the explosion bitmaps
    private ArrayList<Bitmap> alienState = new ArrayList<>();//store the aliens bitmaps
    private Bitmap currentSprite;//the current sprite that is drawn
    private int fireCounter=5;//a counter to limit how many times you can fire

    public Alien(Point p, Bitmap b, int alienType, float xPosIn, float yPosIn, boolean Bl) {
        Matrix matrixMirrorY=new Matrix();//a matrix to mirror the sprites on the sheet for when the ship is going right
        Matrix matrixMirrorX=new Matrix();//a matrix to flip a couple of the aliens to be facing downwards
        matrixMirrorY.preScale(-1.0f,1.0f);//the mirror matrix along the y
        matrixMirrorX.preScale(1.0f,-1.0f);//the mirror matrix along the x
        setScreenSize(p);//store the screen size
        setSpeed(10);//the speed at which the alien moves
        setxPos(xPosIn);//set the start position
        setyPos(yPosIn);
        movingLeft=Bl;
        alientype=alienType;
        int spriteY=(56+(24*alienType))*(int)spriteScale;
        //all sizes and positions are scaled up by the pixel density and then doubled again compared to the source PNG
        for(int i=0;i<8;i++){//there are 8 sprites for the alien animation
            alienState.add(Bitmap.createBitmap(b,i*24*(int)spriteScale,spriteY,16*(int)spriteScale,16*(int)spriteScale));//add each bitmap to the array
        }

        for(int i=5;i>-1;i--){//and 5 extra sprites need to be duplicated and mirrored
            alienState.add(Bitmap.createBitmap(alienState.get(i),0,0,alienState.get(i).getWidth(),alienState.get(i).getHeight(),matrixMirrorY,false));//this is using the mirror matrix y
        }
        if(alienType==2||alienType==3){
            for(int i = 0;i<alienState.size();i++){
                Bitmap temp=Bitmap.createBitmap(alienState.get(i),0,0,alienState.get(i).getWidth(),alienState.get(i).getHeight(),matrixMirrorX,false);//this is using the mirror matrix x
                alienState.set(i,temp);
            }
        }

        explosion.add(Bitmap.createBitmap(b, 185*(int)spriteScale, 144*(int)spriteScale, 32*(int)spriteScale, 32*(int)spriteScale));//add the 4 explosion sprites to an array
        explosion.add(Bitmap.createBitmap(b, 225*(int)spriteScale, 144*(int)spriteScale, 32*(int)spriteScale, 32*(int)spriteScale));//could have been done in a for loop
        explosion.add(Bitmap.createBitmap(b, 265*(int)spriteScale, 144*(int)spriteScale, 32*(int)spriteScale, 32*(int)spriteScale));
        explosion.add(Bitmap.createBitmap(b, 305*(int)spriteScale, 144*(int)spriteScale, 32*(int)spriteScale, 32*(int)spriteScale));
        currentSprite = alienState.get(6);//set the alien starting position
        setWidth(currentSprite.getWidth());//set the width value to that off the sprite to check collides
        setHeight(currentSprite.getHeight());//and the height
    }

    private void moveLeft(){//this will be called to move the alien left
        setxPos(getxPos()-getSpeed());//set the new x position
        if(iAlienState>0){//if the current sprite is the last sprite
            iAlienState--;//de increment
            currentSprite=alienState.get(iAlienState);//set the current sprite
        }
    }
    private void moveRight(){//same as above but for the right
        setxPos(getxPos()+getSpeed());
        if(iAlienState<alienState.size()-1){
            iAlienState++;
            currentSprite=alienState.get(iAlienState);
        }
    }
    private void moveUp(){
        setyPos(getyPos()-getSpeed());
    }//moving up and down is simpler
    private void moveDown(){
        setyPos(getyPos()+getSpeed());
    }//just set the y positions

    public void update(Context c, Bitmap b,ArrayList<Projectile> proj,Ship ship) {//update the alien
        if(getyPos()<=0) {// if the alien is off the top of the screen
            moveDown();//move down
        }
        if(getyPos()>=getScreenSize().y){//if the alien reaches the bottom of the screen
            setyPos(0);//reset to the top
        }
        if(alientype==1){//movement for alien type 1
            if(!movingLeft){//if not moving left
                moveRight();//move right
                moveRight();
                if ((getxPos() + getWidth()) > getScreenSize().x) {//if the alien reaches the edge of the screen
                    movingLeft = true;//turn around
                }
            }
            if (movingLeft) {//if moving left
                moveLeft();//move  left
                moveLeft();
                if (getxPos() < 0) {//if the alien reaches the edge of the screen
                    movingLeft = false;//turn around
                }
            }
            if(fireCounter>4){//after at least 5 updates
                if(AlienAI.shipInRange(this,ship)) {
                    proj.add(new Projectile(getxPos() + (getWidth() / 2), getyPos() + getWidth(), c, getScreenSize(), b, true));//fire a projectile
                    fireCounter = 0;//once a projectile has been fired, reset the count back to zero
                }
            }
        }
        if(alientype==2) {//movement for alien type 2
            if (!movingLeft) {//if not moving left
                moveRight();//move once right
                moveDown();//and once down
                if ((getxPos() + getWidth()) > getScreenSize().x) {//if the alien reaches the edge of the screen
                    movingLeft = true;//turn around
                    moveDown();//and move down
                }
            }
            if (movingLeft) {//if moving left
                moveLeft();//move once left
                moveDown();//and once down
                if (getxPos() < 0) {//if the alien reaches the edge of the screen
                    movingLeft = false;//turn around
                    moveDown();//and move down
                }
            }
        }
        if(alientype==3){//movement for alien type 3
            moveDown();
            moveDown();
        }
        if (explodedStart) {//if the alien has been set to explode
            if(explosionCounter==0){//if the alien hasnt changed to an explosion sprite yet
                setxPos(getxPos()-8*7);//and adjust the x and y positions to cater for the larger sprite
                setyPos(getyPos()-8*7);
            }
            if (explosionCounter < 4) {//if the current sprite isnt the last sprite of the explode animation
                currentSprite = explosion.get(explosionCounter);//set the current sprite to the current explode stage
                explosionCounter++;//then update the explode stage

            }
            if (explosionCounter >= 4) {//if the last explosion stage has been drawn
                explodedFinish = true;//set the alien to be removed
            }
        }
        fireCounter++;//increment the fire counter
    }

    public void draw(Canvas c) {//draw the alien to canvas provided
        c.drawBitmap(currentSprite, getxPos(), getyPos(), null);
    }

    public void setExplodedStart(boolean b) {//this is called when a collision has happened
        this.explodedStart = b;//set the alien to start exploding
            }

    public boolean isDestroy() {return explodedFinish;}//is the alien to be removed

}