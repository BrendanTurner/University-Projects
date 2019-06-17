#pragma once
#include<SFML\Graphics.hpp>
#include "GameObject.h"

class PlayerObject : public GameObject
{
public:
	PlayerObject(sf::View* view, sf::Image* image, int posX, int posY);
	~PlayerObject();

	void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo);
	void onMessage(const std::string message);
	void onCollision(const std::string direction, const float correction, ColliderType type);
	void onDraw(sf::RenderWindow* window);
	sf::View* m_view;
	void setSpeed(float speed);
private:
	float m_speed = basePlayerSpeed;
	ObjectState m_state;
	DirectionState m_direction;
	void playerIdle(unsigned short frameNo);
	void playerWalk(unsigned short frameNo);
	void playerPush(unsigned short frameNo);
};