package p15232006.galagaclone.Model;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Point;

import static p15232006.galagaclone.View.GameSurfaceView.spriteScale;

/**
 * Created by p15232006 on 06/02/2018.
 */

public class Projectile extends GameObject {
    private Bitmap projectile;//the projectile sprite
    private boolean destroy = false;//set whether the projectile has been flaged to be destroyed
    private boolean isEnemy;//freindly or foe projectile

    public Projectile(float xIn, float yIn, Context c, Point p, Bitmap b, boolean e) {
        Matrix matrixMirror=new Matrix();//matrix to mirror the projectile for when its fired form an alien
        matrixMirror.preScale(1.0f,-1.0f);
        isEnemy=e;//is or isnt enemy projectile
        setScreenSize(p);//screensize
        setSpeed(40);//set the speed
        setxPos(xIn);//the start position
        setyPos(yIn);
        //all sizes and positions are scaled up by the pixel density and then doubled again compared to the source PNG
        projectile = Bitmap.createBitmap(b, 358*7, 4*(int)spriteScale, 4*(int)spriteScale, 8*(int)spriteScale);//creat the sprite
        if(isEnemy){//if its an enemy projectile
            projectile=Bitmap.createBitmap(projectile,0,0,projectile.getWidth(),projectile.getHeight(),matrixMirror,false);//mirror it along y axis
        }
        setWidth(projectile.getWidth());//set the width and height values to that of the sprite for collisions
        setHeight(projectile.getHeight());
    }

    public void update() {//update projectile
        if(isEnemy){//if its an enemy projectile
            setyPos(getyPos()+getSpeed());//add to the y value
        }
        if(!isEnemy){//if not
            setyPos(getyPos()-getSpeed());//subtract
        }
        if (getyPos() < -getHeight()) {//if it goes out of bounds at top
            destroy = true;//set to destroy
        }
        if(getyPos()>getScreenSize().y){//and same at bottom
            destroy=true;
        }
    }

    public void draw(Canvas c) {//draw the projectile to the canvas provided
        c.drawBitmap(projectile, getxPos() + (getWidth() / 2), getyPos() + (getHeight() / 2), null);
    }

    public boolean isDestroy() {
        return destroy;
    }//is it set to destroy

    public void setIsDestroy(boolean b){
        this.destroy=b;
    }//set to destroy

    public boolean isEnemy(){
        return isEnemy;
    }//is it an enemy projectile


}
