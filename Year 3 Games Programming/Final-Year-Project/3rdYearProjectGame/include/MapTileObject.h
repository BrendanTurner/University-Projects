#pragma once
#include"GameObject.h"
class MapTileObject : public GameObject
{
public:
	MapTileObject(int tileNo, int spriteNo, bool hasCollision, sf::Image* image);
	~MapTileObject();

	void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo);
	void onMessage(const std::string message);
	void onCollision(const std::string direction, const float correction, ColliderType type);
	void onDraw(sf::RenderWindow* window);
	//remove these later
	int m_tileNo;
	int m_spriteNo;
	bool m_colision;
	//////////////////
private:
};