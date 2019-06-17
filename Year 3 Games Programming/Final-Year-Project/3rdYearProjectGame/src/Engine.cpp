#pragma once
#include <SFML\Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Engine.h"
#include "Game.h"

std::vector<bool> Engine::m_keyBuffer;

bool Engine::initilizeWindow(int width, int height, std::string windowName)
{
	m_window= new sf::RenderWindow(sf::VideoMode(width, height), windowName);
	m_keyBuffer.resize(sf::Keyboard::KeyCount);
	std::fill(m_keyBuffer.begin(), m_keyBuffer.end(), false);
	return true;
}

bool Engine::runEngine(Game & game)
{
	double timePerFrame = 1.0 / frameRate;
	unsigned short currentFrame = 0;//current frame per second that we are on
	game.m_window = m_window;
	std::chrono::high_resolution_clock::time_point lastTimePoint = std::chrono::high_resolution_clock::now();
	while (m_window->isOpen())
	{
		std::chrono::high_resolution_clock::time_point newTimePoint = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTimePoint - lastTimePoint);
		if (deltaTime.count()>=timePerFrame)//!every frame
		{
			currentFrame++;
			if (currentFrame > 60)currentFrame = 1;
			std::cout << deltaTime.count() << std::endl;
			game.m_inputHandler->handleInputs(m_keyBuffer);
			game.update(deltaTime.count(),currentFrame);
			game.draw();
			if (game.m_exit != nullptr)
			{
				game.endScene();
				game.newScene(game.m_exit);
			}
			lastTimePoint = newTimePoint;
		}
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)m_window->close();
			handleEvents(event);
		}
	}
	game.exit();
	return false;
}

void Engine::handleEvents(sf::Event events)
{
	if (events.type == sf::Event::KeyPressed)
	{
		if (events.key.code != sf::Keyboard::Unknown)
		{
			m_keyBuffer[events.key.code] = true;
		}
	}
	if (events.type == sf::Event::KeyReleased)
	{
		if (events.key.code != sf::Keyboard::Unknown)
		{
			m_keyBuffer[events.key.code] = false;
		}
	}
}
