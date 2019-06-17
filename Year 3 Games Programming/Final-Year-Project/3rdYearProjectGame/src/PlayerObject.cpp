#pragma once
#include <iostream>
#include "PlayerObject.h"
#include "SpriteComponents.h"
#include "CollisionComponent.h"
#include "defines.h"


PlayerObject::PlayerObject(sf::View* view, sf::Image* image,int posX, int posY)
{
	addComponent(new SpritePlayerHeadComponent);
	SpritePlayerHeadComponent* spriteHead = getComponent<SpritePlayerHeadComponent>();
	spriteHead->setSpriteRect(1);
	spriteHead->setSprite(*image);
	spriteHead->getSprite().setPosition(posX - headOffsetY, posY - headOffsetX);

	addComponent(new SpritePlayerBodyComponent);
	SpritePlayerBodyComponent* spriteBody = getComponent<SpritePlayerBodyComponent>();
	spriteBody->setSpriteRect(27);
	spriteBody->setSprite(*image);
	spriteBody->getSprite().setPosition(posX, posY);

	addComponent(new CollisionComponent);
	CollisionComponent* collider = getComponent<CollisionComponent>();
	addComponent(new InteractComponent);
	getComponent<InteractComponent>()->setType(empty);
	collider->setSprite(&spriteBody->getSprite());
	collider->setType(player);
	m_view = view;
	m_view->setCenter(spriteBody->getSprite().getPosition());
	m_direction = down;
	spriteHead->onMessage("idleDown");
	spriteBody->onMessage("idleDown");
	m_hasMoved = true;
}

void PlayerObject::onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo)
{
	m_animationcounter++;
	SpritePlayerBodyComponent* sprite = getComponent<SpritePlayerBodyComponent>();
	switch (m_state)
	{
	case idle:
		playerIdle(frameNo);
		break;
	case walk:
		playerWalk(frameNo);
		break;
	case pushing:
		playerPush(frameNo);
		break;
	}
	m_view->setCenter(sprite->getSprite().getPosition());
	m_state = idle;
}
void PlayerObject::onMessage(const std::string message)
{
	if (message.compare(0, 6, "player") == 0)
	{
		if (m_state == idle)
		{
			m_state = walk;
		}
		if (message == "playerUp")
		{
			if (m_direction == left)m_direction = upLeft;
			else if (m_direction == right)m_direction = upRight;
			else m_direction = up;
		}
		else if (message == "playerDown")
		{
			if (m_direction == left)m_direction = downLeft;
			else if (m_direction == right)m_direction = downRight;
			else m_direction = down;
		}
		if (message == "playerLeft")
		{
			if (m_direction == up)m_direction = upLeft;
			else if (m_direction == down)m_direction = downLeft;
			else m_direction = left;
		}
		else if (message == "playerRight")
		{
			if (m_direction == up)m_direction = upRight;
			else if (m_direction == down)m_direction = downRight;
			else m_direction = right;
		}
	}
}

void PlayerObject::onCollision(const std::string direction, const float correction, ColliderType type)
{
	switch (type)
	{
	case rigid: case map:
		{
			SpritePlayerBodyComponent* spriteBody = getComponent<SpritePlayerBodyComponent>();
			SpritePlayerHeadComponent* spriteHead = getComponent<SpritePlayerHeadComponent>();
			if (direction == "right")
			{
				spriteBody->getSprite().move(-correction, 0.f);
				spriteHead->getSprite().move(-correction, 0.f);
			}
			else if (direction == "left")
			{
				spriteBody->getSprite().move(correction, 0.f);
				spriteHead->getSprite().move(correction, 0.f);
			}
			else if (direction == "top")
			{
				spriteBody->getSprite().move(0.f, correction);
				spriteHead->getSprite().move(0.f, correction);
			}
			else if (direction == "bottom")
			{
				spriteBody->getSprite().move(0.f, -correction);
				spriteHead->getSprite().move(0.f, -correction);
			}
			m_view->setCenter(spriteBody->getSprite().getPosition());
			m_state = pushing;
			break;
		}
	}
}

void PlayerObject::onDraw(sf::RenderWindow * window)
{
	window->draw(getComponent<SpritePlayerBodyComponent>()->getSprite());
	window->draw(getComponent<SpritePlayerHeadComponent>()->getSprite());
}

void PlayerObject::setSpeed(float speed)
{
	m_speed = speed;
}

void PlayerObject::playerIdle(unsigned short frameNo)
{
	InteractComponent* interact = getComponent<InteractComponent>();
	SpritePlayerBodyComponent* spriteBody = getComponent<SpritePlayerBodyComponent>();
	SpritePlayerHeadComponent* spriteHead = getComponent<SpritePlayerHeadComponent>();
	if (m_direction == up || m_direction == upLeft || m_direction == upRight)
	{
		spriteHead->onMessage("idleUp");
		spriteBody->onMessage("idleUp");
	}
	else if (m_direction == down || m_direction == downLeft || m_direction == downRight)
	{
		spriteHead->onMessage("idleDown");
		spriteBody->onMessage("idleDown");
	}
	if (m_direction == left || m_direction == upLeft || m_direction == downLeft)
	{
		spriteHead->onMessage("idleLeft");
		spriteBody->onMessage("idleLeft");
	}
	else if (m_direction == right || m_direction == upRight || m_direction == downRight)
	{
		spriteHead->onMessage("idleRight");
		spriteBody->onMessage("idleRight");
	}
	interact->setType(empty);
}

void PlayerObject::playerWalk(unsigned short frameNo)
{
	SpritePlayerBodyComponent* spriteBody = getComponent<SpritePlayerBodyComponent>();
	SpritePlayerHeadComponent* spriteHead = getComponent<SpritePlayerHeadComponent>();
	if (m_direction == up || m_direction == upLeft || m_direction == upRight)//move up code here
	{
		if (m_animationcounter>=walkFrameRate)
		{
			spriteBody->onMessage("walkUp");
			spriteHead->onMessage("walkUp");
			m_animationcounter = 0;
		}
		spriteBody->getSprite().move(0.f, -m_speed);
		spriteHead->getSprite().move(0.f, -m_speed);
	}
	else if (m_direction == down || m_direction == downLeft || m_direction == downRight)//else if so it can either go up or down, not both
	{
		if (m_animationcounter >= walkFrameRate)
		{
			spriteBody->onMessage("walkDown");
			spriteHead->onMessage("walkDown");
			m_animationcounter = 0;
		}
		spriteBody->getSprite().move(0.f, m_speed);
		spriteHead->getSprite().move(0.f, m_speed);
	}
	if (m_direction == left || m_direction == upLeft || m_direction == downLeft)//move left code here
	{
		if (m_animationcounter >= walkFrameRate)
		{
			spriteBody->onMessage("walkLeft");
			spriteHead->onMessage("walkLeft");
			m_animationcounter = 0;
		}
		spriteBody->getSprite().move(-m_speed, 0.f);
		spriteHead->getSprite().move(-m_speed, 0.f);
	}
	else if (m_direction == right || m_direction == upRight || m_direction == downRight)//else if so it can either go left or right, not both
	{
		if (m_animationcounter >= walkFrameRate)
		{
			spriteBody->onMessage("walkRight");
			spriteHead->onMessage("walkRight");
			m_animationcounter = 0;
		}
		spriteBody->getSprite().move(m_speed, 0.f);
		spriteHead->getSprite().move(m_speed, 0.f);
	}
}

void PlayerObject::playerPush(unsigned short frameNo)
{
	SpritePlayerBodyComponent* spriteBody = getComponent<SpritePlayerBodyComponent>();
	SpritePlayerHeadComponent* spriteHead = getComponent<SpritePlayerHeadComponent>();
	InteractComponent* interact = getComponent<InteractComponent>();
	sf::FloatRect rect = getComponent<SpritePlayerBodyComponent>()->getSprite().getGlobalBounds();
	if (m_direction == up || m_direction == upLeft || m_direction == upRight)
	{
		spriteBody->onMessage("pushUp");
		spriteHead->onMessage("pushUp");
		rect.top -= interactHeight;
		rect.height = interactHeight;
	}
	else if (m_direction == down || m_direction == downLeft || m_direction == downRight)
	{
		spriteBody->onMessage("pushDown");
		spriteHead->onMessage("pushDown");
		rect.top += bodyHeight + interactHeight;
		rect.height = interactHeight;
	}
	else if (m_direction == left)
	{
		spriteBody->onMessage("pushLeft");
		spriteHead->onMessage("pushLeft");
		rect.left -= interactWidth;
		rect.width = interactWidth;
	}
	else if (m_direction == right)
	{
		spriteBody->onMessage("pushRight");
		spriteHead->onMessage("pushRight");
		rect.left += bodyWidth + interactWidth;
		rect.width = interactWidth;
	}
	interact->setRect(rect);
	interact->setType(push);
}
