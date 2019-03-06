#include "frog.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;



frog::frog()
{
	//load the following 4 sprite sheets into its own frogSprite variable
	frogSprite.loadFromFile("assets/texture/frogSprite.png");
	frogSprite3Leg.loadFromFile("assets/texture/frogSprite3Legs.png");
	frogSprite2Leg.loadFromFile("assets/texture/frogSprite2Legs.png");
	frogSprite1Leg.loadFromFile("assets/texture/frogSprite1Leg.png");
	//set the origin of the frog to the center
	frogBody.setOrigin(10, 15);
	//set the initial texture of the frogBody sprite to the sprite sheet with all 4 legs attached
	frogBody.setTexture(frogSprite);
	//set the frogBody sprite to the first frame of the sprite sheet
	frogBody.setTextureRect(frogSprites[0]);
	//set the position of the frog
	frogBody.setPosition(500, 785);
	//assign which position each frame in the sprite sheet starts and how far down and alogn they go

	//start top right(0,0) and go along 30 and down 45
	frogSprites[0] = sf::IntRect(0, 0, 30, 45);
	//start at right next to the last frame(31,0) and also go alogn 30 and down 45
	frogSprites[1] = sf::IntRect(31, 0, 30, 45);
}


frog::~frog()
{
}

//code to move frog up
void frog::translateUp()
{
	//checks the frog isnt going to be off screen
	if(frogBody.getPosition().y>(15))
	{
		//if it isnt off screen do the following:

		//if the current frame is the first frame
		if (iCurrentFrame == 0)
		{
			//change to the second frame in the sprite sheet
			frogBody.setTextureRect(frogSprites[1]);
			//and change the iCurrentFrame int to 1 for future checks
			iCurrentFrame = 1;
		}
		//if the current frame is the second frame
		else if (iCurrentFrame == 1)
		{
			//change to the second frame in the sprite sheet
			frogBody.setTextureRect(frogSprites[0]);
			//and also change the iCurrentFrame int to 0 instead for future checks
			iCurrentFrame = 0;
		}
		//either way move frog
		frogBody.move(0.f, -30.f);
	}
}

//code to move frog down
//this is the same code as above but for moving down
void frog::translateDown(sf::RenderWindow &window)
{
	if (frogBody.getPosition().y < ((window.getSize().y) - 15))
	{
		if (iCurrentFrame == 0)
		{
			frogBody.setTextureRect(frogSprites[1]);
			iCurrentFrame = 1;
		}
		else if(iCurrentFrame == 1)
		{
			frogBody.setTextureRect(frogSprites[0]);
			iCurrentFrame = 0;
		}
		frogBody.move(0.f, 30.f);
	}
}

//code to move frog left
//this is the same code as above but for moving left
void frog::translateLeft()
{
	if (frogBody.getPosition().x>(10))
	{
		if (iCurrentFrame == 0)
		{
			frogBody.setTextureRect(frogSprites[1]);
			iCurrentFrame = 1;
		}
		else if (iCurrentFrame == 1)
		{
			frogBody.setTextureRect(frogSprites[0]);
			iCurrentFrame = 0;
		}
		frogBody.move(-20.f, 0.f);
	}	
}

//code to move frog right
//this is the same code as above but for moving right
void frog::translateRight(sf::RenderWindow &window)
{
	if (frogBody.getPosition().x<((window.getSize().x) - 10))
	{
		if (iCurrentFrame == 0)
		{
			frogBody.setTextureRect(frogSprites[1]);
			iCurrentFrame = 1;
		}
		else if (iCurrentFrame == 1)
		{
			frogBody.setTextureRect(frogSprites[0]);
			iCurrentFrame = 0;
		}
		frogBody.move(20.f, 0.f);
	}
}

//code to pass the frogBody shape to the render window and draw it
void frog::draw(sf::RenderWindow & window)
{
	//this funciton simply passes the built in windows draw comand to the main window when called
	window.draw(frogBody);
}

//this is called whenever the frog collides with anything
void frog::reset()
{
	//simply sets the position back to 500 785, could have saved the inital creation coordinates for a more modular class but this never changes anyway
	frogBody.setPosition(500, 785);
}


//takes the argument livesLeft from the main window
void frog::loseLeg(int livesLeft)
{
	//switch statement with 3 outcomes
	switch (livesLeft)
	{
		//if lives left is at 3 (1 leg lost)
	case 3:
		//sets the texture sheet of frogBody to the 3 legged frog
		frogBody.setTexture(frogSprite3Leg);
		break;
		//if lives left is at 2 (2 leg lost)
	case 2:
		//sets the texture sheet of frogBody to the 2 legged frog
		frogBody.setTexture(frogSprite2Leg);
		break;
		//if lives left is at 1 (3 leg lost)
	case 1:
		//sets the texture sheet of frogBody to the 1 legged frog
		frogBody.setTexture(frogSprite1Leg);
		break;
		//function wont be called if all lives are lost because it is then game over
	}
}

//the FloatRect &boundary variable is passed into this function so it can have the
//global bounds of the created instance assigned to it
void frog::getGlobalBounds(sf::FloatRect &boundary)
{
	//getGlobalBounds() is a built in function to do as the name suggests
	boundary= frogBody.getGlobalBounds();
}

