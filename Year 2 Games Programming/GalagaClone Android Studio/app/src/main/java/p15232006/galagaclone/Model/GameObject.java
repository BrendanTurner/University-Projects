package p15232006.galagaclone.Model;

import android.graphics.Point;

/**
 * Created by p15232006 on 06/02/2018.
 */

abstract class GameObject {
    private Point screenSize;//store screensize
    private float speed;//these
    private float width=0;//are
    private float height=0;//all
    private float xPos=0;//self
    private float yPos=0;//explanatory

    //setters and getters
    public float getyPos() {return yPos;}
    public float getxPos() {return xPos;}
    public float getHeight() {return height;}
    public float getWidth() {return width;}
    public float getSpeed() {return speed;}
    public Point getScreenSize() {return screenSize;}
    public void setyPos(float yPos) {this.yPos = yPos;}
    public void setxPos(float xPos) {this.xPos = xPos;}
    public void setHeight(float height) {this.height = height;}
    public void setWidth(float width) {this.width = width;}
    public void setSpeed(float speed) {this.speed = speed;}
    public void setScreenSize(Point screenSize) {this.screenSize = screenSize;}
}
