#pragma once
#include<SFML/Graphics.hpp>
class car
{
private:
	//reset point for when the car goes off screen
	float startPositionY;
	sf::Texture carSprite;
	sf::Sprite carBody;
public:
	//constructor, takes x y and whether it is facing left or right
	car(float x, float y, bool leftOrRight);
	~car();

	//functions to move left or right
	void moveRight(sf::RenderWindow &window);
	void moveLeft(sf::RenderWindow &window);

	//function to draw the car on screen
	void draw(sf::RenderWindow &window);

	//function to get the boundaries for the collision detection
	void getGlobalBounds(sf::FloatRect &boundary);
};

