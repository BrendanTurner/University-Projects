#include <SFML/Graphics.hpp>
#include <iostream>
#include"frog.h"
#include"car.h"
#include"lorry.h"
#include <string>
using namespace std;

int main()
{
	// Create a window with the constructor 1000 by 800 called "frogger game"
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Frogger Game");
	//set frame rate to 40
	window.setFramerateLimit(40);

	//create a timer to use for the traffic movement
	sf::Clock timer;
	//int that will decrease for how many lives are left
	int lives = 4;
	
	//load font and texts
	//create a font variable
	sf::Font poshText;
	//load a font into the font variable
	poshText.loadFromFile("assets/font/ITCEDSCR.TTF");
	//create a text object called livesLeft
	sf::Text livesLeft;
	//set livesLeft to the us ethe font variable we made just before
	livesLeft.setFont(poshText);
	//set the string of the text object to say "legs Left:" followed by whatever number is currently stored in lives
	livesLeft.setString("Legs left:"+std::to_string( (lives)));
	//set the character size of the text object to 40
	livesLeft.setCharacterSize(40);
	//set the position to be slightly in from the top left corner
	livesLeft.setPosition(2, 2);
	//set colour of the text to black( its white as default)
	livesLeft.setColor(sf::Color::Black);
		
	//create onjects
	//all functions below are creating instances of the car and lorry class
	//taking an x, y, and whetehr its goign to face left or right as an argument
	car car1(800,597.5f, true);
	car car5(400, 597.5f, true);
	car car9(0, 597.5f, true);
	lorry lorry1(800,467.5f, true);
	lorry lorry3(350, 467.5f, true);
	lorry lorry5(-100, 467.5f, true);

	car car2(0, 96.f, false);
	car car6(400, 96.f, false);
	car car10(800, 96.f, false);
	lorry lorry2(0, 232.5f, false);
	lorry lorry4(450, 232.5f, false);
	lorry lorry6(900, 232.5f, false);
	//frog has no arguments
	frog frog1;

	//the safe zones
	//rectangle shape called grassVerge1
	sf::RectangleShape grassVerge1;
	//set size of grassVerge
	grassVerge1.setSize(sf::Vector2f(1000.f, 75.5f));
	//set origin of grassverge1( may have been easier to leave as the default 0,0)
	grassVerge1.setOrigin(grassVerge1.getSize().x / 2.0f, grassVerge1.getSize().y / 2.0f);
	//set position of verge
	grassVerge1.setPosition(500.f,32.f);
	//set colour to green
	grassVerge1.setFillColor(sf::Color::Green);


	//same as above code but with the bottom verge instead
	sf::RectangleShape grassVerge2;
	grassVerge2.setSize(sf::Vector2f(1000.f, 75.5f));
	grassVerge2.setOrigin(grassVerge2.getSize().x / 2.0f, grassVerge2.getSize().y / 2.0f);
	grassVerge2.setPosition(500.f, 768.f);
	grassVerge2.setFillColor(sf::Color::Green);

	//same as above code but with the middle verge instead
	sf::RectangleShape grassVerge3;
	grassVerge3.setSize(sf::Vector2f(1000.f, 75.f));
	grassVerge3.setOrigin(grassVerge3.getSize().x / 2.0f, grassVerge3.getSize().y / 2.0f);
	grassVerge3.setPosition(500.f, 400.f);
	grassVerge3.setFillColor(sf::Color::Green);

	// Run until the user closes the window
	while (window.isOpen())
	{


		// Check all user events

		sf::Event event;
		while (window.pollEvent(event))
		{

			// User has pressed the close button
			if (event.type == sf::Event::Closed)
			{
				//calls the window.close built in function
				window.close();
			}

			
			//event check key press
			if (event.type == sf::Event::KeyPressed)
			{
				//if the key pressed is up
				if (event.key.code == sf::Keyboard::Up)
					//then call the function that moves up
					frog1.translateUp();
				//if the key pressed is down
				if (event.key.code == sf::Keyboard::Down)
					//then call the function that moves down
					frog1.translateDown(window);
				//if the key pressed is left
				if (event.key.code == sf::Keyboard::Left)
					//then call the function that moves left
					frog1.translateLeft();
				//if the key pressed is right
				if (event.key.code == sf::Keyboard::Right)
					//then call the function that moves right
					frog1.translateRight(window);
			}
		}

		//traffic movement
		//create a time variable that gets is data from the timer created earlier
		sf::Time elapsedTime = timer.getElapsedTime();
		//if the time variable has increased since last check (larger then 0.01 which it will be reset to after all traffic has been moved) then do the following:
		if (elapsedTime.asSeconds() > 0.01)
		{
			//traffic right
			//calls the functions in the respective classes for lorry and car to move right for each vehicle created
			car1.moveRight(window);
			car5.moveRight(window);
			car9.moveRight(window);
			lorry1.moveRight(window);
			lorry3.moveRight(window);
			lorry5.moveRight(window);
			//traffic left
			//calls the functions in the respective classes for lorry and car to move left for each vehicle created
			car2.moveLeft(window);
			car6.moveLeft(window);
			car10.moveLeft(window);
			lorry2.moveLeft(window);
			lorry4.moveLeft(window);
			lorry6.moveLeft(window);
			//restarts the time so the next check will no if its increased again
			timer.restart();
		}
		//collision
		//a load of floatRects to store the boundaries of the frog and all traffic
		sf::FloatRect frogBoundary;
		sf::FloatRect car1Boundary;
		sf::FloatRect car2Boundary;
		sf::FloatRect car5Boundary;
		sf::FloatRect car6Boundary;
		sf::FloatRect car9Boundary;
		sf::FloatRect car10Boundary;

		sf::FloatRect lorry1Boundary;
		sf::FloatRect lorry2Boundary;
		sf::FloatRect lorry3Boundary;
		sf::FloatRect lorry4Boundary;
		sf::FloatRect lorry5Boundary;
		sf::FloatRect lorry6Boundary;
		
		//calls the funtion in the respective classes to get the global boundaries
		lorry1.getGlobalBounds(lorry1Boundary);
		lorry2.getGlobalBounds(lorry2Boundary);
		lorry3.getGlobalBounds(lorry3Boundary);
		lorry4.getGlobalBounds(lorry4Boundary);
		lorry5.getGlobalBounds(lorry5Boundary);
		lorry6.getGlobalBounds(lorry6Boundary);

		car1.getGlobalBounds(car1Boundary);
		car2.getGlobalBounds(car2Boundary);
		car5.getGlobalBounds(car5Boundary);
		car6.getGlobalBounds(car6Boundary);
		car9.getGlobalBounds(car9Boundary);
		car10.getGlobalBounds(car10Boundary);

		frog1.getGlobalBounds(frogBoundary);

		//a lot of redundant repeated code here
		//if the frog  boundary intersects or collides with one of the traffic then do the following:
		if (frogBoundary.intersects(car1Boundary))
		{
			//call the reset frog function to move it back to the bottom of the window
			frog1.reset();
			//lose a life(leg)
			lives--;
			//call the lose leg function to change the frog sprite to visibly show the leg missing
			frog1.loseLeg(lives);
			//re write the string of the text object to display the updated number of lives
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(car2Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(car5Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(car6Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(car9Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(car10Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry1Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry2Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry3Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry4Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry5Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (frogBoundary.intersects(lorry6Boundary))
		{
			frog1.reset();
			lives--;
			frog1.loseLeg(lives);
			livesLeft.setString("Lives left:" + std::to_string((lives)));
		}
		if (lives <=0)
			window.close();
		if (frogBoundary.intersects(grassVerge1.getGlobalBounds()))
			window.close();

		//clear the window with a cyan colour
		window.clear(sf::Color(104,104,104));

		//draw everything here...
		//window.draw(...);
		// draw the verges first
		window.draw(grassVerge1);
		window.draw(grassVerge2);
		window.draw(grassVerge3);
		//then draw the frog as it will go on top of the verge
		frog1.draw(window);
		//then all the vehicles so they would apear on top of the frog if a pause or something was implemenented after each life is lost( this isnt the case)
		car1.draw(window);
		car2.draw(window);
		car5.draw(window);
		car6.draw(window);
		car9.draw(window);
		car10.draw(window);
		lorry1.draw(window);
		lorry2.draw(window);
		lorry3.draw(window);
		lorry4.draw(window);
		lorry5.draw(window);
		lorry6.draw(window);
		// draw the text object in the top left corner( can be done anytiem after the top grass verge(grassVerge1)
		window.draw(livesLeft);

		//end the current frame
		//finaly display everything that has been drawn to the buffer
		window.display();
		
		
	}
	return 0;
}