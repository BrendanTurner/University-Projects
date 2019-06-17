#pragma once
#include "TriggerObjects.h"
#include "SpriteComponents.h"
#include "CollisionComponent.h"
#include "TransitionComponent.h"
#include "defines.h"

void TriggerObject::onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo)
{
	trigger(storyTriggers);
	m_state = idle;
}

void TriggerObject::onMessage(const std::string message)
{
}

void TriggerObject::onCollision(const std::string direction, const float correction, ColliderType type)
{
	if (type == player)
	{
		if (m_atrib == sceneChange)
		{
			m_state = triggered;
		}
	}
}

void TriggerObject::onDraw(sf::RenderWindow * window)
{
}

void TriggerObject::trigger(std::map<std::string, bool>* storyTriggers)
{
	if (m_state != idle)m_animationcounter++;
	else
	{
		if (m_animationcounter>0)m_animationcounter--;
	}
	 if (m_state == triggered)
	{
		if (m_animationcounter >= sceneTransWait)
		{
			CollisionComponent* collider = getComponent<CollisionComponent>();
			collider->setType(changeScene);
			InteractComponent* interact = getComponent<InteractComponent>();
			interact->setType(changeScene);
		}
	}
}

TransitionZone::TransitionZone(int posX, int posY, MapEntrance exit, MapName destination)
{
	addComponent(new TransitionComponent(exit,destination));
	addComponent(new InteractComponent);
	InteractComponent* interact = getComponent<InteractComponent>();
	interact->setRect(sf::FloatRect(posX, posY, largeBodyWidth, largeBodyHeight));
	interact->setType(trigg);
	addComponent(new CollisionComponent);
	CollisionComponent*collider = getComponent<CollisionComponent>();
	collider->setRect(sf::FloatRect(posX, posY, largeBodyWidth, largeBodyHeight));
	collider->setType(trigg);
	m_atrib = sceneChange;
}
