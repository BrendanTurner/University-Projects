#include "lorry.h"
#include<SFML/Graphics.hpp>

//constructor
lorry::lorry(float x, float y, bool leftOrRight)
{
	// load the sprite and store in the lorrySprite variable
	lorrySprite.loadFromFile("assets/texture/lorrySprite.png");
	//set the texture of the lorryBody sprite to be the texture loaded in the line before
	lorryBody.setTexture(lorrySprite);
	//set position fo the lorry to whatever the x and y arguments were in the constructor
	lorryBody.setPosition(x, y);
	//save the y position so the lorry can be reset when it goes off screen
	startPositionY = y;
	//check the leftOrRight boolean (true or false)
	if (!leftOrRight)
	{
		//and flips the sprite acordingly different
		lorryBody.setScale(-1,1);
	}
}


lorry::~lorry()
{
}

//RenderWindow &window is passed in to the function to move and draw
//the created instance of this class in the main window
//in the next 3 functions
void lorry::moveRight(sf::RenderWindow &window)
{
	//checks the lorry is still on screen
	if ((lorryBody.getPosition().x) <= (window.getSize().x))
		//if it is then it keeps moving right
		lorryBody.move(5, 0);
	//checks if the lorry is off screen
	else if ((lorryBody.getPosition().x) > (window.getSize().x))
		//if it is then it is reset back to the start position
		//including the y coordinates store from creation
		lorryBody.setPosition(-300, startPositionY);
}

//same as above but for moving left
void lorry::moveLeft(sf::RenderWindow &window)
{
	if ((lorryBody.getPosition().x) >= 0)
		lorryBody.move(-5, 0);
	else if ((lorryBody.getPosition().x) < 0)
		lorryBody.setPosition(1300, startPositionY);
}

void lorry::draw(sf::RenderWindow & window)
{
	//this funciton simply passes the built in windows draw comand to the main window when called
	window.draw(lorryBody);
}

//the FloatRect &boundary variable is passed into this function so it can have the
//global bounds of the created instance assigned to it
void lorry::getGlobalBounds(sf::FloatRect &boundary)
{
	//getGlobalBounds() is a built in function to do as the name suggests
	boundary = lorryBody.getGlobalBounds();
}
