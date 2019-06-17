#pragma once
#include "WorldObjects.h"
#include "SpriteComponents.h"
#include "CollisionComponent.h"
#include "defines.h"

void worldObject::onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo)
{
	m_hasMoved = false;
	trigger(storyTriggers);
	m_state = idle;
}

void worldObject::onMessage(const std::string message)
{
}

void worldObject::onCollision(const std::string direction, const float correction, ColliderType type)
{
	switch (type)
	{
	case push:
	{
		if (m_atrib == pushable)
		{
			m_state = pushed;
			if (direction == "right")m_direction = left;
			else if (direction == "left")m_direction = right;
			else if (direction == "top")m_direction = down;
			else if (direction == "bottom")m_direction = up;
		}
		break;
	}
	case rigid: case map:
	{
		switch (m_atrib)
		{
		case pitTrap:
		{
		m_state = triggered;
		break;
		}
		case pushable:
		{
			SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
			if (direction == "right")
			{
				sprite->getSprite().move(-correction, 0.f);
			}
			else if (direction == "left")
			{
				sprite->getSprite().move(correction, 0.f);
			}
			else if (direction == "top")
			{
				sprite->getSprite().move(0.f, correction);
			}
			else if (direction == "bottom")
			{
				sprite->getSprite().move(0.f, -correction);
			}
			break;
		}
		}
		break;
	}
	case player:
	{
		if (m_atrib == completeLavaDungeon || m_atrib == completeForestDungeon || m_atrib == completeGraveyardDungeon || m_atrib == completeIceDungeon || m_atrib == pitTrap)
		{
			m_state = triggered;
		}
	}
	}
}

void worldObject::onDraw(sf::RenderWindow * window)
{
	window->draw(getComponent<SpriteObjectBodyComponent>()->getSprite());
}

void worldObject::trigger(std::map<std::string, bool>* storyTriggers)
{
	if (m_state!=idle)m_animationcounter++;
	else
	{
		if (m_animationcounter>0)m_animationcounter--;
	}
	switch (m_state)
	{
	case pushed:
	{
		if (m_animationcounter >= pushWait)
		{
			SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
			if (m_direction == right)sprite->getSprite().move(interactWidth, 0.f);
			else if (m_direction == left)sprite->getSprite().move(-interactWidth, 0.f);
			else if (m_direction == up)sprite->getSprite().move(0.f, -interactHeight);
			else if (m_direction == down)sprite->getSprite().move(0.f, interactHeight);
			m_hasMoved = true;
		}
		break;
	}
	case triggered:
	{
		switch (m_atrib)
		{
		case pitTrap:
		{
			if (m_animationcounter >= grassPitWait)
			{
				CollisionComponent* collider = getComponent<CollisionComponent>();
				SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
				sprite->setSpriteRect(10);
				collider->setType(pit);
				m_atrib = none;
			}
			break;
		}
		case completeLavaDungeon:
		{
			if (m_animationcounter >= pressurePlateWait)
			{
				if ((storyTriggers->at("Dungeon3-1st") ? 1 : 0) + (storyTriggers->at("Dungeon3-2nd") ? 1 : 0) + (storyTriggers->at("Dungeon3-3rd") ? 1 : 0) + (storyTriggers->at("Dungeon3-4th") ? 1 : 0) == 0)
				{
					if (!storyTriggers->at("Dungeon1"))
					{
						storyTriggers->at("Dungeon1") = true;
						storyTriggers->at("Dungeon3-1st") = true;
					}
					else if (!storyTriggers->at("Dungeon2"))
					{
						storyTriggers->at("Dungeon2") = true;
						storyTriggers->at("Dungeon3-2nd") = true;
					}
					else if (!storyTriggers->at("Dungeon3"))
					{
						storyTriggers->at("Dungeon3") = true;
						storyTriggers->at("Dungeon3-3rd") = true;
					}
					else if (!storyTriggers->at("Dungeon4"))
					{
						storyTriggers->at("Dungeon4") = true;
						storyTriggers->at("Dungeon3-4th") = true;
					}
					m_atrib = none;
				}
			}
			break;
		}
		case completeGraveyardDungeon:
		{
			if (m_animationcounter >= pressurePlateWait)
			{
				if ((storyTriggers->at("Dungeon2-1st") ? 1 : 0) + (storyTriggers->at("Dungeon2-2nd") ? 1 : 0) + (storyTriggers->at("Dungeon2-3rd") ? 1 : 0) + (storyTriggers->at("Dungeon2-4th") ? 1 : 0) == 0)
				{
					if (!storyTriggers->at("Dungeon1"))
					{
						storyTriggers->at("Dungeon1") = true;
						storyTriggers->at("Dungeon2-1st") = true;
					}
					else if (!storyTriggers->at("Dungeon2"))
					{
						storyTriggers->at("Dungeon2") = true;
						storyTriggers->at("Dungeon2-2nd") = true;
					}
					else if (!storyTriggers->at("Dungeon3"))
					{
						storyTriggers->at("Dungeon3") = true;
						storyTriggers->at("Dungeon2-3rd") = true;
					}
					else if (!storyTriggers->at("Dungeon4"))
					{
						storyTriggers->at("Dungeon4") = true;
						storyTriggers->at("Dungeon2-4th") = true;
					}
					m_atrib = none;
				}
			}
			break;
		}
		case completeForestDungeon:
		{
			if (m_animationcounter >= pressurePlateWait)
			{
				if ((storyTriggers->at("Dungeon1-1st") ? 1 : 0) + (storyTriggers->at("Dungeon1-2nd") ? 1 : 0) + (storyTriggers->at("Dungeon1-3rd") ? 1 : 0) + (storyTriggers->at("Dungeon1-4th") ? 1 : 0) == 0)
				{
					if (!storyTriggers->at("Dungeon1"))
					{
						storyTriggers->at("Dungeon1") = true;
						storyTriggers->at("Dungeon1-1st") = true;
					}
					else if (!storyTriggers->at("Dungeon2"))
					{
						storyTriggers->at("Dungeon2") = true;
						storyTriggers->at("Dungeon1-2nd") = true;
					}
					else if (!storyTriggers->at("Dungeon3"))
					{
						storyTriggers->at("Dungeon3") = true;
						storyTriggers->at("Dungeon1-3rd") = true;
					}
					else if (!storyTriggers->at("Dungeon4"))
					{
						storyTriggers->at("Dungeon4") = true;
						storyTriggers->at("Dungeon1-4th") = true;
					}
					m_atrib = none;
				}
			}
			break;
		}
		case completeIceDungeon:
		{
			if (m_animationcounter >= pressurePlateWait)
			{
				if ((storyTriggers->at("Dungeon4-1st")?1:0)+ (storyTriggers->at("Dungeon4-2nd")?1:0)+(storyTriggers->at("Dungeon4-3rd")?1:0)+(storyTriggers->at("Dungeon4-4th")?1:0)==0)
				{
					if (!storyTriggers->at("Dungeon1"))
					{
						storyTriggers->at("Dungeon1") = true;
						storyTriggers->at("Dungeon4-1st") = true;
					}
					else if (!storyTriggers->at("Dungeon2"))
					{
						storyTriggers->at("Dungeon2") = true;
						storyTriggers->at("Dungeon4-2nd") = true;
					}
					else if (!storyTriggers->at("Dungeon3"))
					{
						storyTriggers->at("Dungeon3") = true;
						storyTriggers->at("Dungeon4-3rd") = true;
					}
					else if (!storyTriggers->at("Dungeon4"))
					{
						storyTriggers->at("Dungeon4") = true;
						storyTriggers->at("Dungeon4-4th") = true;
					}
					m_atrib = none;
				}
			}
			break;
		}
		}
		break;
	}
	}
}

ShrubObject::ShrubObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth,bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(0);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
	m_atrib = pushable;
}

LightStoneObject::LightStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(2);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

HeavyStoneObject::HeavyStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(3);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

SignObject::SignObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(5);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

GrassObject::GrassObject(sf::Image * image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(7);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(grass);
}

GrassCoveredPitObject::GrassCoveredPitObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(9);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(grass);
	m_atrib = pitTrap;
}

StumpObject::StumpObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(11);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

BreakableStoneObject::BreakableStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(13);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

PressurePlate::PressurePlate(sf::Image* image, int posX, int posY, ObjectAtrib atrib)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(14);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(trigg);
	m_atrib = atrib;
}

FirePitObject::FirePitObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(15);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

WoodBenchObject::WoodBenchObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, bodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(16);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

LargeLightStoneObject::LargeLightStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(17);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

LargeHeavyStoneObject::LargeHeavyStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(18);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

PierObject::PierObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(21);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(empty);//special case dunno what id do here
}

LargeStumpObject::LargeStumpObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(22);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

LargeBreakableStoneObject::LargeBreakableStoneObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(23);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

TentObject::TentObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(24);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}

CattleBonesObject::CattleBonesObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(largeBodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(25);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(empty);
}

CactusObject::CactusObject(sf::Image* image, int posX, int posY)
{
	addComponent(new SpriteObjectBodyComponent(bodyWidth, largeBodyHeight));
	SpriteObjectBodyComponent* sprite = getComponent<SpriteObjectBodyComponent>();
	sprite->setSpriteRect(26);
	sprite->setSprite(*image);
	sprite->getSprite().setPosition(posX, posY);
	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	collider->setSprite(&sprite->getSprite());
	collider->setType(rigid);
}