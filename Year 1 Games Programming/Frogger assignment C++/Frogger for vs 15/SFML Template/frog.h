#pragma once
#include<SFML/Graphics.hpp>

class frog
{
private:
	//4 sprite sheets, for each leg(life) that is lost
	sf::Texture frogSprite;
	sf::Texture frogSprite3Leg;
	sf::Texture frogSprite2Leg;
	sf::Texture frogSprite1Leg;
	sf::Sprite frogBody;
	//2 frames for the frog to move
	sf::IntRect frogSprites[2];
	//int for which frame is active
	int iCurrentFrame = 0;

public:
	//constructor requires no arguments
	frog();
	~frog();

	//functions for movign left, right, up and down
	void translateUp();
	void translateDown(sf::RenderWindow &window);
	void translateLeft();
	void translateRight(sf::RenderWindow &window);

	//function to draw the frog to screen
	void draw(sf::RenderWindow &window);

	//function to reset frog
	void reset();

	//function to chage sprite sheet if a life(leg) is lost
	void loseLeg(int livesLeft);

	//get boundaries for the collision detection
	void getGlobalBounds(sf::FloatRect &boundary);
};

