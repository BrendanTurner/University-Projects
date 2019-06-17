#pragma once
#include "Scene.h"
#include "PlayerObject.h"
#include "WorldObjects.h"
#include "TriggerObjects.h"
#include "customJsonWriter.h"
#include "defines.h"
#include "JSON\json.h"


#include <fstream>

void Scene::draw(sf::RenderWindow * window)
{
	m_background->onDraw(window);
	for (int i = 0; i < (int)mv_mapTiles.size(); i++)mv_mapTiles[i]->onDraw(window);
	for (int i = 0; i < (int)mv_gameObjects.size(); i++)mv_gameObjects[i]->onDraw(window);
}

TransitionComponent* Scene::update(float dt, unsigned short frameNo)
{
	for (int i = 0; i < (int)mv_gameObjects.size(); i++) mv_gameObjects[i]->onUpdate(m_storyTriggers, frameNo);
	for (int i = 0; i < (int)mv_mapTiles.size(); i++) mv_mapTiles[i]->onUpdate(m_storyTriggers, frameNo);
	return m_collisionManager->handleCollisions();
}

void Scene::checkTriggers()
{
	if (m_storyTriggers->at("Dungeon1"))
	{
		if (m_storyTriggers->at("Dungeon2"))
		{
			if (m_storyTriggers->at("Dungeon3"))
			{
				if (m_storyTriggers->at("Dungeon4")){}
				else
				{
					if (m_storyTriggers->at("Dungeon1-1st"))
					{
						if (m_storyTriggers->at("Dungeon2-2nd"))
						{
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = FGV;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = FGI;
						}
						else if (m_storyTriggers->at("Dungeon3-2nd"))
						{
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = FVG;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = FVI;
						}
						else if (m_storyTriggers->at("Dungeon4-2nd"))
						{
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = FIG;
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = FIV;
						}
					}
					if (m_storyTriggers->at("Dungeon2-1st"))
					{
						if (m_storyTriggers->at("Dungeon1-2nd"))
						{
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = GFV;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = GFI;
						}
						else if (m_storyTriggers->at("Dungeon3-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = GVF;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = GVI;
						}
						else if (m_storyTriggers->at("Dungeon4-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = GIF;
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = GIV;
						}
					}
					if (m_storyTriggers->at("Dungeon3-1st"))
					{
						if (m_storyTriggers->at("Dungeon1-2nd"))
						{
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = VFG;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = VFI;
						}
						else if (m_storyTriggers->at("Dungeon2-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = VGF;
							if (m_storyTriggers->at("Dungeon4-3rd"))m_dungeonProg = VGI;
						}
						else if (m_storyTriggers->at("Dungeon4-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = VIF;
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = VIG;
						}
					}
					if (m_storyTriggers->at("Dungeon4-1st"))
					{
						if (m_storyTriggers->at("Dungeon1-2nd"))
						{
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = IFG;
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = IFV;
						}
						else if (m_storyTriggers->at("Dungeon2-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = IGF;
							if (m_storyTriggers->at("Dungeon3-3rd"))m_dungeonProg = IGV;
						}
						else if (m_storyTriggers->at("Dungeon3-2nd"))
						{
							if (m_storyTriggers->at("Dungeon1-3rd"))m_dungeonProg = IVF;
							if (m_storyTriggers->at("Dungeon2-3rd"))m_dungeonProg = IVG;
						}
					}
				}
			}
			else
			{
				if (m_storyTriggers->at("Dungeon1-1st"))
				{
					if (m_storyTriggers->at("Dungeon2-2nd"))m_dungeonProg = FG;
					else if (m_storyTriggers->at("Dungeon3-2nd"))m_dungeonProg = FV;
					else if (m_storyTriggers->at("Dungeon4-2nd"))m_dungeonProg = FI;
				}
				if (m_storyTriggers->at("Dungeon2-1st"))
				{
					if (m_storyTriggers->at("Dungeon1-2nd"))m_dungeonProg = GF;
					else if (m_storyTriggers->at("Dungeon3-2nd"))m_dungeonProg = GV;
					else if (m_storyTriggers->at("Dungeon4-2nd"))m_dungeonProg = GI;
				}
				if (m_storyTriggers->at("Dungeon3-1st"))
				{
					if (m_storyTriggers->at("Dungeon1-2nd"))m_dungeonProg = VF;
					else if (m_storyTriggers->at("Dungeon2-2nd"))m_dungeonProg = VG;
					else if (m_storyTriggers->at("Dungeon4-2nd"))m_dungeonProg = VI;
				}
				if (m_storyTriggers->at("Dungeon4-1st"))
				{
					if (m_storyTriggers->at("Dungeon1-2nd"))m_dungeonProg = IF;
					else if (m_storyTriggers->at("Dungeon2-2nd"))m_dungeonProg = IG;
					else if (m_storyTriggers->at("Dungeon3-2nd"))m_dungeonProg = IV;
				}
			}
		}
		else
		{
			if (m_storyTriggers->at("Dungeon1-1st"))m_dungeonProg = F;
			else if (m_storyTriggers->at("Dungeon2-1st"))m_dungeonProg = G;
			else if (m_storyTriggers->at("Dungeon3-1st"))m_dungeonProg = V;
			else if (m_storyTriggers->at("Dungeon4-1st"))m_dungeonProg = I;
		}
	}
}

bool Scene::loadScene(sf::View* view, MapEntrance entrance)
{
	checkTriggers();
	setSceneVariables();
	
	////////////////////////////////////////////////////

	//////////////maptiles load here////////////////////
	m_currentImage = &m_spriteManager->getImage(m_tileSet);
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	Json::Value map;
	Json::Value mapTileNo;
	Json::Value spriteNoNode;
	Json::Value collisionNode;

	jsonData.open(m_tileData);
	reader.parse(jsonData, root);
	map = root["map"];
	mv_mapTiles.resize(map.size());
	for (int i = 0; i < (int)map.size(); i++)
	{
		mapTileNo = map[i]["MapTileNo"];
		spriteNoNode = map[i]["SpriteNo"];
		collisionNode = map[i]["Collision"];
		mv_mapTiles[i] = new MapTileObject(mapTileNo.asInt(), spriteNoNode.asInt(), collisionNode.asBool(), m_currentImage);
		if (collisionNode.asBool())m_collisionManager->mv_mapTilesWithColliders.push_back(mv_mapTiles[i]);
	}
	jsonData.close();
	////////////////////////////////////////////////////

	///////////game objects load here///////////////////
	Json::Value objects;
	Json::Value object;
	Json::Value posXin;
	Json::Value posYin;
	int posX;
	int posY;

	jsonData.open(m_objectData);
	reader.parse(jsonData, root);
	objects = root["objects"];
	mv_gameObjects.resize(objects.size());
	for (int i = 0; i < (int)objects.size(); i++)
	{
		object = objects[i]["Object"];
		posXin = objects[i]["PosX"];
		posYin = objects[i]["PosY"];

		posX = posXin.asInt()*bodyWidth;
		posY = posYin.asInt()*bodyHeight;
		//////////world objects
		if (object.asString() == "shrub")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new ShrubObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "stoneLight")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new LightStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "stoneHeavy")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new HeavyStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "sign")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new SignObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "grass")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new GrassObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "grassPit")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new GrassCoveredPitObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "stump")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new StumpObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "stoneBreak")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new BreakableStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "PressurePlate")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new PressurePlate(m_currentImage, posX, posY, m_dungeon);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "firePit")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new FirePitObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "woodBench")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new WoodBenchObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "largeStoneLight")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new LargeLightStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "largeStoneHeavy")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new LargeHeavyStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "pier")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new PierObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "largeStump")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new LargeStumpObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "largeStoneBreak")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new LargeBreakableStoneObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "tent")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TentObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "cattleBones")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new CattleBonesObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "cactus")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new CactusObject(m_currentImage, posX, posY);
			m_collisionManager->mv_staticObjects.push_back(mv_gameObjects[i]);
		}
		/////////trigger objects and transition zones
		else if (object.asString() == "transitionZoneSWVolcano")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, SouthWest, volcano);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneSVolcano")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, South, volcano);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneSEVolcano")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, SouthEast, volcano);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNWGraveyard")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, NorthWest, graveyard);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNGraveyard")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, North, graveyard);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNEGraveyard")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, NorthEast, graveyard);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneENForest")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, EastNorth, forest);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneEForest")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, East, forest);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneESForest")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, EastSouth, forest);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWNIce")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, WestNorth, ice);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWIce")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, West, ice);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWSIce")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, WestSouth, ice);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWNTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, WestNorth, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, West, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneWSTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, WestSouth, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNWTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, NorthWest, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, North, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneNETown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, NorthEast, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneENTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, EastNorth, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneETown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, East, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneESTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, EastSouth, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneSWTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, SouthWest, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneSTown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, South, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
		else if (object.asString() == "transitionZoneSETown")
		{
			m_currentImage = &m_spriteManager->getImage(m_objectSet);
			mv_gameObjects[i] = new TransitionZone(posX, posY, SouthEast, town);
			m_collisionManager->mv_triggerObjects.push_back(mv_gameObjects[i]);
		}
	}
	jsonData.close();
	switch (entrance)
	{
	case Middle:
	{
		posX = (spriteTileRow - 1) / 2 * bodyWidth;
		posY = (spriteTileColumn - 1) / 2 * bodyHeight;
		break;
	}
	case North:
	{
		posX = (spriteTileRow - 1) / 2 * bodyWidth;
		posY = 1 * bodyHeight;
		break;
	}
	case NorthWest:
	{
		posX = 3 * bodyWidth;
		posY = 1 * bodyHeight;
		break;
	}
	case NorthEast:
	{
		posX = (spriteTileRow - 4)*bodyWidth;
		posY = 1 * bodyHeight;
		break;
	}
	case East:
	{
		posX = (spriteTileRow - 2)*bodyWidth;
		posY = (spriteTileColumn - 1) / 2 * bodyHeight;
		break;
	}
	case EastNorth:
	{
		posX = (spriteTileRow - 2)*bodyWidth;
		posY = 3 * bodyHeight;
		break;
	}
	case EastSouth:
	{
		posX = (spriteTileRow - 2)*bodyWidth;
		posY = (spriteTileColumn - 4)*bodyHeight;
		break;
	}
	case West:
	{
		posX = 1 * bodyWidth;
		posY = (spriteTileColumn - 1) / 2 * bodyHeight;
		break;
	}
	case WestNorth:
	{
		posX = 1 * bodyWidth;
		posY = 3 * bodyHeight;
		break;
	}
	case WestSouth:
	{
		posX = 1 * bodyWidth;
		posY = (spriteTileColumn - 4)*bodyHeight;
		break;
	}
	case South:
	{
		posX = (spriteTileRow - 1) / 2 * bodyWidth;
		posY = (spriteTileColumn - 2)*bodyHeight;
		break;
	}
	case SouthWest:
	{
		posX = 3 * bodyWidth;
		posY = (spriteTileColumn - 2)*bodyHeight;
		break;
	}
	case SouthEast:
	{
		posX = (spriteTileRow - 4)*bodyWidth;
		posY = (spriteTileColumn - 2)*bodyHeight;
		break;
	}
	}
	m_currentImage = &m_spriteManager->getImage("playerSprites001");
	mv_gameObjects.push_back(new PlayerObject(view, m_currentImage, posX, posY));
	m_inputHandler->mv_objectsRequiringInput.push_back(mv_gameObjects.back());
	m_collisionManager->mv_dynamicObjects.push_back(mv_gameObjects.back());
	////////////////////////////////////////////////////////////
	return true;
}