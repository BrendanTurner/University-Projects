#pragma once
#include <string>
#include "SpriteComponents.h"
#include "defines.h"

bool SpriteComponent::setSprite(const sf::Image& sprite)
{
	m_texture->loadFromImage(sprite);
	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(*m_currentSpriteRect);
	return true;
}

sf::Sprite & SpriteComponent::getSprite()
{
	return *m_sprite;
}

////////////////World Objects
SpriteObjectBodyComponent::SpriteObjectBodyComponent(int sizeX,int sizeY)
{
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_currentSpriteRect = new sf::IntRect(0, 0, sizeX, sizeY);
}

void SpriteObjectBodyComponent::onUpdate(float dt)
{
}

void SpriteObjectBodyComponent::onMessage(const std::string message)
{
	int mess = std::stoi(message);
	setSpriteRect(mess);
}

void SpriteObjectBodyComponent::setSpriteRect(int spriteNo)
{
	if (spriteNo <= 16)//first row
	{
		m_currentSpriteRect->left = spriteNo * bodyWidth;
		m_currentSpriteRect->top = 0;
	}
	else if (spriteNo > 16 && spriteNo <= 25)//second row
	{
		m_currentSpriteRect->left = (spriteNo-17) * largeBodyWidth;
		m_currentSpriteRect->top = bodyHeight;
	}
	else if (spriteNo == 26)//third row, only one tall object so far will need to change this
	{
		m_currentSpriteRect->left = (spriteNo-26) * bodyWidth;
		m_currentSpriteRect->top = bodyHeight + largeBodyHeight;
	}
	m_sprite->setTextureRect(*m_currentSpriteRect);
}

/////////////Player
SpritePlayerBodyComponent::SpritePlayerBodyComponent()
{
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_currentSpriteRect = new sf::IntRect(0, 0, bodyWidth, bodyHeight);
}

void SpritePlayerBodyComponent::onUpdate(float dt)
{
}

void SpritePlayerBodyComponent::onMessage(const std::string message)
{
	if (message.compare(0, 4, "idle") == 0)
	{
		if (message == "idleUp")
		{
			m_spriteState = idleBodyUp;
		}
		if (message == "idleDown")
		{
			m_spriteState = idleBodyDown;
		}
		if (message == "idleLeft")
		{
			m_spriteState = idleBodyLeft;
		}
		if (message == "idleRight")
		{
			m_spriteState = idleBodyRight;
		}
	}
	if (message.compare(0, 4, "walk") == 0)
	{
		if (message == "walkUp")
		{
			switch (m_spriteState)
			{
			case walkBodyUp1:
				m_spriteState = walkBodyUp2;
				break;
			case walkBodyUp2:
				m_spriteState = idleBodyUp;
				break;
			default:
				m_spriteState = walkBodyUp1;
				break;
			}
		}
		if (message == "walkDown")
		{
			switch (m_spriteState)
			{
			case walkBodyDown1:
				m_spriteState = walkBodyDown2;
				break;
			case walkBodyDown2:
				m_spriteState = idleBodyDown;
				break;
			default:
				m_spriteState = walkBodyDown1;
				break;
			}
		}
		if (message == "walkLeft")
		{
			switch (m_spriteState)
			{
			case walkBodyLeft1:
				m_spriteState = walkBodyLeft2;
				break;
			case walkBodyLeft2:
				m_spriteState = idleBodyLeft;
				break;
			default:
				m_spriteState = walkBodyLeft1;
				break;
			}
		}
		if (message == "walkRight")
		{
			switch (m_spriteState)
			{
			case walkBodyRight1:
				m_spriteState = walkBodyRight2;
				break;
			case walkBodyRight2:
				m_spriteState = idleBodyRight;
				break;
			default:
				m_spriteState = walkBodyRight1;
				break;
			}
		}
	}
	setSpriteRect(m_spriteState);
}

void SpritePlayerBodyComponent::setSpriteRect(int spriteNo)
{
	m_currentSpriteRect->left = (spriteNo % spriteSheetRow) * bodyWidth;
	m_currentSpriteRect->top = (floor(spriteNo / spriteSheetRow)) * bodyHeight;
	m_sprite->setTextureRect(*m_currentSpriteRect);
}

SpritePlayerHeadComponent::SpritePlayerHeadComponent()
{
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_currentSpriteRect = new sf::IntRect(0, 0, bodyWidth, bodyHeight);
}

void SpritePlayerHeadComponent::onUpdate(float dt)
{
}

void SpritePlayerHeadComponent::onMessage(const std::string message)
{
	if (message.compare(0, 4, "idle") == 0)
	{
		if (message == "idleUp")
		{
			m_spriteState = idleHeadUp;
		}
		if (message == "idleDown")
		{
			m_spriteState = idleHeadDown;
		}
		if (message == "idleLeft")
		{
			m_spriteState = idleHeadLeft;
		}
		if (message == "idleRight")
		{
			m_spriteState = idleHeadRight;
		}
	}
	if (message.compare(0, 4, "walk") == 0)
	{
		if (message == "walkUp")
		{
			m_spriteState = idleHeadUp;
		}
		if (message == "walkDown")
		{
			m_spriteState = idleHeadDown;
		}
		if (message == "walkLeft")
		{
			m_spriteState = idleHeadLeft;
		}
		if (message == "walkRight")
		{
			m_spriteState = idleHeadRight;
		}
	}
	setSpriteRect(m_spriteState);
}

void SpritePlayerHeadComponent::setSpriteRect(int spriteNo)
{
	m_currentSpriteRect->left = (spriteNo % spriteSheetRow) * bodyWidth;
	m_currentSpriteRect->top = (floor(spriteNo / spriteSheetRow)) * bodyHeight;
	m_sprite->setTextureRect(*m_currentSpriteRect);
}

//////////////Map
SpriteMapComponent::SpriteMapComponent()
{
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_currentSpriteRect = new sf::IntRect(0, 0, mapSpriteWidth, mapSpriteHeight);
}

void SpriteMapComponent::onUpdate(float dt)
{
}

void SpriteMapComponent::onMessage(const std::string message)
{
}

void SpriteMapComponent::setSpriteRect(int spriteNo)
{
	m_currentSpriteRect->left = (spriteNo % spriteSheetRow) * mapSpriteWidth;
	m_currentSpriteRect->top = (floor(spriteNo / spriteSheetRow)) * mapSpriteHeight;
	m_sprite->setTextureRect(*m_currentSpriteRect);
}

/////////////Background
BackgroundSpriteComponent::BackgroundSpriteComponent()
{
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_currentSpriteRect = new sf::IntRect(0, 0, screenWidth, screenHeight);
}

void BackgroundSpriteComponent::onUpdate(float dt)
{
}

void BackgroundSpriteComponent::onMessage(const std::string message)
{
}

void BackgroundSpriteComponent::setSpriteRect(int spriteNo)
{
}