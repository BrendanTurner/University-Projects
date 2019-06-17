#pragma once
#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "Engine.h"

class Game
{
public:
	InputHandler* m_inputHandler;
	TransitionComponent* m_exit;
	sf::RenderWindow* m_window;
	sf::View* m_view;
	Scene* m_currentScene;
	Game();
	void update(float dt, unsigned short frameNo);
	void draw();
	void exit();
	void newScene(TransitionComponent* entrance);
	void endScene();
private:
	std::map<std::string, bool> m_storyTriggers;
	void initialize(const int& width, const int& height);
	void loadTriggers();
	void saveTriggers();
	void loadKeys();
};