#pragma once
#include<SFML\Graphics.hpp>
#include "GameObject.h"
#include "defines.h"

class TriggerObject : public GameObject
{
public:
	void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo);
	void onMessage(const std::string message);
	void onCollision(const std::string direction, const float correction, ColliderType type);
	void onDraw(sf::RenderWindow* window);
protected:
	bool m_isTriggered;
	virtual void trigger(std::map<std::string, bool>* storyTriggers);
	ObjectState m_state;
	ObjectAtrib m_atrib;
};

class TransitionZone : public TriggerObject
{
public:
	TransitionZone(int posX, int posY, MapEntrance exit, MapName destination);
};