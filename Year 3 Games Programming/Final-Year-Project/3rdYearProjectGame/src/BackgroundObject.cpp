#pragma once
#include "BackgroundObject.h"
#include "SpriteComponents.h"


BackgroundObject::BackgroundObject()
{
}

BackgroundObject::BackgroundObject(sf::Image* image)
{
	addComponent(new BackgroundSpriteComponent);
	SpritePlayerHeadComponent* sprite = getComponent<SpritePlayerHeadComponent>();
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(0, 0);
}

void BackgroundObject::onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo)
{
}

void BackgroundObject::onMessage(const std::string message)
{
}

void BackgroundObject::onCollision(const std::string direction, const float correction, ColliderType type)
{
}

void BackgroundObject::onDraw(sf::RenderWindow * window)
{
	window->clear(m_BackgroundColour);
	if (getComponent<BackgroundSpriteComponent>())
	{
		window->draw(getComponent<BackgroundSpriteComponent>()->getSprite());
	}
}

void BackgroundObject::setColour(int red, int green, int blue, int alpha)
{
	m_BackgroundColour.r = red;
	m_BackgroundColour.g = green;
	m_BackgroundColour.b = blue;
	m_BackgroundColour.a = alpha;
}
