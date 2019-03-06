package p15232006.galagaclone.Model;

import android.graphics.Bitmap;
import android.graphics.Point;

import java.util.ArrayList;

import static p15232006.galagaclone.View.GameSurfaceView.spriteScale;

/**
 * Created by p15232006 on 13/02/2018.
 */

public class AlienFleet {
    ArrayList<Alien> fleet=new ArrayList<>();//store a premade fleet
    private Point screenSize;//store the screensize
    public AlienFleet() {
    }

    public ArrayList<Alien> level1Construct(Point p, Bitmap b){//level 1
        for(int i=1;i<9;i++) {//loop through
            fleet.add(new Alien(p, b, 2, i*+20*spriteScale,i*-20*spriteScale,false));//and place 8 type 2 aliens on the left
            fleet.add(new Alien(p,b,2,p.x-(i*+20*spriteScale),i*-20*spriteScale,true));//and on the right
        }
        return fleet;

    }

    public ArrayList<Alien> level2Construct(Point p, Bitmap b){//level 2
        for(int i=1;i<9;i++) {//loop through
            fleet.add(new Alien(p, b, 2, i*+20*spriteScale,i*-20*spriteScale,false));//and place 8 type 2 aliens on the left
            fleet.add(new Alien(p,b,2,p.x-(i*+20*spriteScale),i*-20*spriteScale,true));//and on the right
        }
        for (int i=1;i<4;i++) {//loop through
            fleet.add(new Alien(p, b, 1, i*p.x / 4, -40 * spriteScale, false));//and place 3 type 1 aliens across the screen
        }
        return fleet;

    }

    public ArrayList<Alien> level3Construct(Point p, Bitmap b){//level 3
        for(int i=1;i<9;i++) {//loop through
            fleet.add(new Alien(p, b, 2, i*+20*spriteScale,i*-20*spriteScale,false));//and place 8 type 2 aliens on the left
            fleet.add(new Alien(p,b,2,p.x-(i*+20*spriteScale),i*-20*spriteScale,true));//and on the right
        }
        for (int i=1;i<4;i++) {//loop through
            fleet.add(new Alien(p, b, 1, i*p.x / 4, -40 * spriteScale, false));//and place 3 type 1 aliens across the screen
        }
        for (int i=1;i<5;i++) {//loop through across
            for (int j = 1; j < 4; j++) {//and down
                fleet.add(new Alien(p, b, 3, i * p.x / 5, j * -60 * spriteScale, false));//and place 3 type alien, 4 places across the screen
            }
        }
        return fleet;

    }
}
