#pragma once
#include<SFML/Graphics.hpp>
class lorry
{
private:
	//reset point for when the lorry goes off screen
	float startPositionY;
	sf::Texture lorrySprite;
	sf::Sprite lorryBody;
public:
	//constructor, takes x y and whether it is facing left or right
	lorry(float x, float y, bool leftOrRight);
	~lorry();

	//functions to move left or right
	void moveRight(sf::RenderWindow &window);
	void moveLeft(sf::RenderWindow &window);

	//function to draw the lorry on screen
	void draw(sf::RenderWindow &window);

	//function to get the boundaries for the collision detection
	void getGlobalBounds(sf::FloatRect &boundary);
};

