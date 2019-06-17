#pragma once
#include "GameObject.h"
#include "MapTileObject.h"
#include "BackgroundObject.h"
#include "InputHandler.h"
#include "ImageManager.h"
#include "CollisionManager.h"
class Scene
{
public:
	std::vector<GameObject*> mv_gameObjects;
	std::vector<MapTileObject*>mv_mapTiles;
	std::string m_tileSet;
	std::string m_objectSet;
	std::string m_tileData;
	std::string m_objectData;
	sf::Image* m_currentImage;
	ObjectAtrib m_dungeon;
	DungeonProgression m_dungeonProg=N;
	BackgroundObject* m_background;
	ImageManager * m_spriteManager;
	InputHandler* m_inputHandler;
	CollisionManager* m_collisionManager;
	void draw(sf::RenderWindow* window);
	TransitionComponent* update(float dt, unsigned short frameNo);
	virtual void setSceneVariables() = 0;
	void checkTriggers();
	bool loadScene(sf::View* view, MapEntrance entrance);
	virtual void saveScene() = 0;
	std::map<std::string, bool>* m_storyTriggers;
};