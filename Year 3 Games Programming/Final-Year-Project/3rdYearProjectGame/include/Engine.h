#pragma once
#include <SFML\Graphics.hpp>

class Game;

class Engine
{
public:
	bool initilizeWindow(int width, int height, std::string windowName);
	bool runEngine(Game& game);
private:
	sf::RenderWindow* m_window;
	static std::vector<bool> m_keyBuffer;
	void handleEvents(sf::Event events);

};