#pragma once
#include "Component.h"
#include "defines.h"
#include "SFML/Graphics.hpp"

class SpriteComponent : public Component
{
public:
	void onUpdate(float dt)=0;
	void onMessage(const std::string message)=0;
	bool setSprite(const sf::Image& sprite);
	sf::Sprite& getSprite();
	virtual void setSpriteRect(int spriteNo)=0;
protected:
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
	sf::IntRect* m_currentSpriteRect;
};

class SpriteMapComponent : public SpriteComponent
{
public:
	SpriteMapComponent();
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	void setSpriteRect(int spriteNo)override;
};

class SpriteObjectBodyComponent : public SpriteComponent 
{
public:
	SpriteObjectBodyComponent(int sizeX, int sizeY);
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	void setSpriteRect(int spriteNo)override;
};

class SpritePlayerBodyComponent : public SpriteComponent
{
public:
	SpritePlayerBodyComponent();
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	void setSpriteRect(int spriteNo)override;
private:
	PlayerAnimationState m_spriteState;
};

class SpritePlayerHeadComponent : public SpriteComponent
{
public:
	SpritePlayerHeadComponent();
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	void setSpriteRect(int spriteNo)override;
private:
	PlayerAnimationState m_spriteState;
};

class BackgroundSpriteComponent : public SpriteComponent
{
public:
	BackgroundSpriteComponent();
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	void setSpriteRect(int spriteNo)override;
};