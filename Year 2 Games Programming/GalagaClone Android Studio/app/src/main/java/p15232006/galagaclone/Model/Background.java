package p15232006.galagaclone.Model;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Point;

import p15232006.galagaclone.R;

/**
 * Created by p15232006 on 12/02/2018.
 */

public class Background {
    private float xPos=0;//start position
    private float yPos=0;
    private Bitmap background;//store the backgroudn image
    private Point screenSize;//store the screensize

    public Background( Context c, Point p) {
        screenSize=p;//set the screensize
        background = BitmapFactory.decodeResource(c.getResources(), R.drawable.background);//create the background
        background = Bitmap.createScaledBitmap(background,p.x,p.y,false);//scale it to the screen
    }

    public void draw(Canvas canvas){//draw 3 backgrounds
        canvas.drawBitmap(background,xPos,yPos,null);//one starts on the screen
        canvas.drawBitmap(background,xPos,yPos+screenSize.y,null);//one starts beneath the screen
        canvas.drawBitmap(background,xPos,yPos-screenSize.y,null);//one starts above
    }
    public void update(){//move the background
        yPos++;//incrementing this moves all 3
        if(yPos>screenSize.y){//ones the initial background has completely left the screen
            yPos=0;//reset all the positions
        }
    }
}
