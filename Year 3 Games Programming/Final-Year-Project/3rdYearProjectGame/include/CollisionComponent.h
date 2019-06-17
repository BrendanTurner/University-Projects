#pragma once
#include "SFML/Graphics.hpp"
#include "defines.h"
#include "Component.h"


class CollisionComponent : public Component
{
public:
	CollisionComponent();
	~CollisionComponent();
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	sf::FloatRect& getRect();
	void setSprite(sf::Sprite* sprite);
	void setRect(sf::FloatRect rect);
	void setType(ColliderType type);
	ColliderType getType();
protected:
	sf::Sprite* m_sprite;
	sf::FloatRect m_rect;
	ColliderType m_colliderType;
};

class InteractComponent : public CollisionComponent{};