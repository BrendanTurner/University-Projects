#pragma once
#include"InputHandler.h"

InputHandler::InputHandler()
{
	
}

void InputHandler::handleInputs(const std::vector<bool>& keyBuffer)
{
	for (const auto& mapEntry : m_keyCommands)
	{
		if (keyBuffer[mapEntry.first])
		{
			for (int i = 0; i < (int)mv_objectsRequiringInput.size(); i++)
			{
				mapEntry.second->execute(*mv_objectsRequiringInput[i]);
			}
		}
	}
}

void InputHandler::setCommand(sf::Keyboard::Key key, std::string command)
{
	if (command == "playerUp")m_keyCommands[key] = new PlayerUp;
	if (command == "playerDown")m_keyCommands[key] = new PlayerDown;
	if (command == "playerLeft")m_keyCommands[key] = new PlayerLeft;
	if (command == "playerRight")m_keyCommands[key] = new PlayerRight;
}
