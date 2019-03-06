#include "car.h"
#include<SFML/Graphics.hpp>

//constructor
car::car(float x,float y,bool leftOrRight)
{
	// load the sprite and store in the carSprite variable
	carSprite.loadFromFile("assets/texture/carSprite.png");
	//set the texture of the carBody sprite to be the texture loaded in the line before
	carBody.setTexture(carSprite);
	//set position fo the car to whatever the x and y arguments were in the constructor
	carBody.setPosition(x, y);
	//save the y position so the car can be reset when it goes off screen
	startPositionY = y;
	//check the leftOrRight boolean (true or false)
	if (!leftOrRight)
	{
		//and flips the sprite acordingly
		carBody.setScale(-1, 1);
	}
}


car::~car()
{
}

//RenderWindow &window is passed in to the function to move and draw
//the created instance of this class in the main window
//in the next 3 functions
void car::moveRight(sf::RenderWindow &window)
{
	//checks the car is still on screen
	if ((carBody.getPosition().x) <= (window.getSize().x))
		//if it is then it keeps moving right
		carBody.move(5, 0);
	//checks if the car is off screen
	else if ((carBody.getPosition().x) > (window.getSize().x))
		//if it is then it is reset back to the start position
		//including the y coordinates store from creation
		carBody.setPosition(-150, startPositionY);
}

//same as above but for moving left
void car::moveLeft(sf::RenderWindow &window)
{
	if ((carBody.getPosition().x) >= 0)
		carBody.move(-5, 0);
	else if ((carBody.getPosition().x) < 0)
		carBody.setPosition(1150, startPositionY);
}


void car::draw(sf::RenderWindow & window)
{
	//this funciton simply passes the built in windows draw comand to the main window when called
	window.draw(carBody);
}

//the FloatRect &boundary variable is passed into this function so it can have the
//global bounds of the created instance assigned to it
void car::getGlobalBounds(sf::FloatRect &boundary)
{
	//getGlobalBounds() is a built in function to do as the name suggests
	boundary= carBody.getGlobalBounds();
}
