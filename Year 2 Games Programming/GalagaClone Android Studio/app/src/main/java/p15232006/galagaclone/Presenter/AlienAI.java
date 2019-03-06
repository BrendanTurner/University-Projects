package p15232006.galagaclone.Presenter;

import p15232006.galagaclone.Model.Alien;
import p15232006.galagaclone.Model.Ship;

/**
 * Created by p15232006 on 26/02/2018.
 */

public class AlienAI {
    static public boolean shipInRange(Alien alien, Ship ship){//check that the ship is below the alien
        float alienMiddle=alien.getxPos()+(alien.getWidth()/2);//find the middle of the alien
        if(alienMiddle>ship.getxPos()&&alienMiddle<ship.getxPos()+ship.getWidth()){//compare to the position of the ship
            return true;
        }
        return false;
    }
}
