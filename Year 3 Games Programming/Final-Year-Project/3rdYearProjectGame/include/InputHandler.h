#pragma once
#include <SFML/Window.hpp>
#include<vector>
#include<map>
#include "inputCommands.h"
class InputHandler
{
public:
	std::vector<GameObject*> mv_objectsRequiringInput;
	std::map<int, InputCommand*> m_keyCommands;
	InputHandler();
	void handleInputs(const std::vector<bool>& keyBuffer);
	void setCommand(sf::Keyboard::Key key,std::string command);
};