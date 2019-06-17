#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
	m_sprite = nullptr;
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::onUpdate(float dt)
{
}

void CollisionComponent::onMessage(const std::string message)
{
}

sf::FloatRect & CollisionComponent::getRect()
{
	if (m_sprite != nullptr)
	{
		m_rect = m_sprite->getGlobalBounds();
	}
	return m_rect;
}

void CollisionComponent::setSprite(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

void CollisionComponent::setRect(sf::FloatRect rect)
{
	m_rect = rect;
}

void CollisionComponent::setType(ColliderType type)
{
	m_colliderType = type;
}

ColliderType CollisionComponent::getType()
{
	return m_colliderType;
}
