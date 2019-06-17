#pragma once
#include "MapTileObject.h"
#include "SpriteComponents.h"
#include "CollisionComponent.h"

#include "defines.h"

MapTileObject::MapTileObject(int tileNo, int spriteNo, bool hasCollision,sf::Image* image)
{
	m_tileNo = tileNo;
	m_spriteNo = spriteNo;
	m_colision = hasCollision;
	addComponent(new SpriteMapComponent);
	SpriteMapComponent* sprite = getComponent<SpriteMapComponent>();
	int x = (tileNo % mapTileRow) * mapSpriteWidth;
	int y = (floor(tileNo / mapTileRow)) * mapSpriteHeight;
	sprite->getSprite().setPosition(x, y);
	sprite->setSpriteRect(spriteNo);
	sprite->setSprite(*image);

	if (hasCollision)
	{
		addComponent(new CollisionComponent);
		CollisionComponent* collider = getComponent<CollisionComponent>();
		collider->setSprite(&sprite->getSprite());
		collider->setType(map);
	}
	
}

void MapTileObject::onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo)
{
	m_hasMoved = false;
}

void MapTileObject::onMessage(const std::string message)
{
}

void MapTileObject::onCollision(const std::string direction, const float correction, ColliderType type)
{
}

void MapTileObject::onDraw(sf::RenderWindow * window)
{
	window->draw(getComponent<SpriteMapComponent>()->getSprite());
}
