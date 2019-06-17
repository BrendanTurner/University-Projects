#pragma once
#include "Game.h"
#include "ForestScene.h"
#include "VolcanoScene.h"
#include "GraveyardScene.h"
#include "IceScene.h"
#include "TownScene.h"
#include "customJsonWriter.h"
#include "defines.h"
#include "JSON\json.h"

#include <fstream>
#include <iostream>

class PlayerGameObject;

Game::Game()
{
	initialize(viewWidth,viewHeight);
}

void Game::update(float dt, unsigned short frameNo)
{
	m_exit = m_currentScene->update(dt, frameNo);
}

void Game::draw()
{
	//m_window->setView(*m_view);
	m_currentScene->draw(m_window);
	m_window->display();
}

void Game::exit()
{
	saveTriggers();
	endScene();
}

void Game::initialize(const int& width, const int& height)
{
	m_exit = nullptr;
	m_view = new sf::View(sf::Vector2f(), sf::Vector2f(width,height));
	m_currentScene = new TownScene;
	m_inputHandler = new InputHandler;
	m_currentScene->m_inputHandler = m_inputHandler;
	m_currentScene->m_storyTriggers = &m_storyTriggers;
	m_window = nullptr;
	loadTriggers();
	loadKeys();
	m_currentScene->loadScene(m_view,Middle);//temporary...will load from triggers or something
	
}

void Game::loadTriggers()
{
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	Json::Value storyTriggers;
	Json::Value triggerNode;
	Json::Value nameNode;
	jsonData.open("assets/data/storyTriggers.json");
	reader.parse(jsonData, root);
	storyTriggers = root["storyTriggers"];
	for (int i = 0; i < (int)storyTriggers.size(); i++)
	{
		nameNode = storyTriggers[i]["Name"];
		triggerNode = storyTriggers[i]["Trigger"];
		m_storyTriggers[nameNode.asString()] = triggerNode.asBool();
	}
	jsonData.close();
}

void Game::saveTriggers()
{
	std::string name;
	std::fstream jsonData;
	std::ofstream jsonDataOut;
	Json::Value root;
	Json::Value nameNode;
	Json::Reader reader;
	Json::customJsonWriter writer;
	jsonData.open("assets/data/storyTriggers.json");
	reader.parse(jsonData, root);
	for (int i = 0; i < (int)root["storyTriggers"].size(); i++)
	{
		name = root["storyTriggers"][i]["Name"].asString();
		root["storyTriggers"][i]["Trigger"] = m_storyTriggers[name];
	}
	
	jsonData.close();
	jsonDataOut.open("assets/data/storyTriggers.json");
	writer.write(jsonDataOut, root);
	jsonDataOut.close();
}

void Game::loadKeys()
{
	int key;
	std::string command;
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	Json::Value keyNode;
	Json::Value commandNode;
	Json::Value inputs;

	jsonData.open("assets/data/input.json");
	reader.parse(jsonData, root);
	inputs = root["Inputs"];
	for (int i = 0; i < (int)inputs.size(); i++)
	{
		keyNode = inputs[i]["Key"];
		key = keyNode.asInt();
		commandNode = inputs[i]["Command"];
		command = commandNode.asString();
		m_inputHandler->setCommand((sf::Keyboard::Key)key, command);
	}
	jsonData.close();
}

void Game::newScene(TransitionComponent* entrance)
{
	switch (entrance->getDestination())
	{
	case town:
		m_currentScene = new TownScene;
		break;
	case forest:
		m_currentScene = new ForestScene;
		break;
	case volcano:
		m_currentScene = new VolcanoScene;
		break;
	case graveyard:
		m_currentScene = new GraveyardScene;
		break;
	case ice:
		m_currentScene = new IceScene;
		break;
	}
	m_currentScene->m_inputHandler = m_inputHandler;
	m_currentScene->m_storyTriggers = &m_storyTriggers;
	m_currentScene->loadScene(m_view,entrance->getEntrance());
	m_exit = nullptr;
}

void Game::endScene()
{
	m_currentScene->saveScene();
	delete m_currentScene;
}
