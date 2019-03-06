package p15232006.galagaclone.Presenter;

import android.util.Log;

import p15232006.galagaclone.Model.Alien;
import p15232006.galagaclone.Model.Projectile;
import p15232006.galagaclone.Model.Ship;

/**
 * Created by p15232006 on 12/02/2018.
 */

public class Collision {
    static public void hasCollided(Projectile projectile, Ship ship){//compare projectile to the player ship
        if(projectile.isEnemy()){//if the projectile has been fired by an enemy
            if(projectile.getyPos()<ship.getyPos()+ship.getHeight()&&//check if collided on the Y position first
               projectile.getyPos()+projectile.getHeight()>ship.getyPos()){
                if(projectile.getxPos()+projectile.getWidth()>ship.getxPos()&&
                        projectile.getxPos()<ship.getxPos()+ship.getWidth()) {//then the x
                    ship.setExplodedStart(true);//set the ship to explode
                    projectile.setIsDestroy(true);//set the projectile to be destroyed
                }
            }
        }
    }

    static public void hasCollided(Projectile projectile, Alien alien){//compare projectile to an alien ship
        if(!projectile.isEnemy()){//if the projectile was fired by the player
            if(projectile.getyPos()<alien.getyPos()+alien.getHeight()&&//check if collided on the Y position first
               projectile.getyPos()+projectile.getHeight()>alien.getyPos()){
                if(projectile.getxPos()+projectile.getWidth()>alien.getxPos()&&
                        projectile.getxPos()<alien.getxPos()+alien.getWidth()) {//then the x
                    alien.setExplodedStart(true);//set the alien to explode
                    projectile.setIsDestroy(true);//set the projectile to be destroyed
                }
            }
        }
    }

    static public void hasCollided(Ship ship,Alien alien){//compare alien to ship collision
        if(ship.getyPos()<alien.getyPos()+alien.getHeight()&&
           ship.getyPos()+ship.getHeight()>alien.getyPos()){//check if collided on the Y position first
            if(ship.getxPos()<alien.getxPos()+alien.getWidth()&&
               ship.getxPos()+ship.getWidth()>alien.getxPos()){//then the x
                alien.setExplodedStart(true);//set the alien to explode
                ship.setExplodedStart(true);//set the ship to explode
            }
        }
    }


}
