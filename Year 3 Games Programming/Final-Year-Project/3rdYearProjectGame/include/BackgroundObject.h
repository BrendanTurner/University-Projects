#pragma once
#include "GameObject.h"

class BackgroundObject : public GameObject
{
public:
	BackgroundObject();
	BackgroundObject(sf::Image* image);
	~BackgroundObject();

	void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo);
	void onMessage(const std::string message);
	void onCollision(const std::string direction, const float correction, ColliderType type);
	void onDraw(sf::RenderWindow* window);
	void setColour(int r, int g, int b, int alpha);
private:
	sf::Color m_BackgroundColour = sf::Color(0, 0, 0, 225);
};
