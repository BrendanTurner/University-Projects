#include "VolcanoScene.h"
#include "PlayerObject.h"
#include "WorldObjects.h"
#include "TriggerObjects.h"
#include "customJsonWriter.h"
#include "defines.h"
#include "JSON\json.h"


#include <fstream>


VolcanoScene::VolcanoScene()
{
	m_spriteManager = new ImageManager;
	m_collisionManager = new CollisionManager;
}

VolcanoScene::~VolcanoScene()
{
}

void VolcanoScene::setSceneVariables()
{
	m_dungeon = completeLavaDungeon;
	switch (m_dungeonProg)
	{
	case N:
	{
		m_background = new BackgroundObject();// if not using an image
		//m_background = new BackgroundObject(&m_spriteManager->getImage("image"));//if using an image
		m_tileSet = "terrainLava";
		m_objectSet = "overworldObjectsLava";
		m_tileData = "assets/data/mapTiles/volcano/mapTilesVolcano.json";
		m_objectData = "assets/data/mapObjects/volcano/mapObjectsVolcano.json";
		m_background->setColour(255, 0, 0, 255);
		break;
	}
	case F:
	{
		m_background = new BackgroundObject();// if not using an image
		m_tileData = "assets/data/mapTiles/volcano/mapTilesVolcano.json";
		m_objectData = "assets/data/mapObjects/volcano/mapObjectsVolcanoF.json";
		m_tileSet = "terrainLava";
		m_objectSet = "overworldObjectsLava";
		m_background->setColour(255, 0, 0, 255);
		break;
	}
	case G:
	{
		m_background = new BackgroundObject();// if not using an image
		m_tileData = "assets/data/mapTiles/volcano/mapTilesVolcano.json";
		m_objectData = "assets/data/mapObjects/volcano/mapObjectsVolcanoG.json";
		m_tileSet = "terrainLava";
		m_objectSet = "overworldObjectsLava";
		m_background->setColour(255, 0, 0, 255);
		break;
	}
	case V:
	{
		m_background = new BackgroundObject();// if not using an image
		m_tileData = "assets/data/mapTiles/volcano/mapTilesVolcano.json";
		m_objectData = "assets/data/mapObjects/volcano/mapObjectsVolcanoV.json";
		m_tileSet = "terrainBarren";
		m_objectSet = "overworldObjectsBarren";
		m_background->setColour(136, 128, 64, 255);
		break;
	}
	case I:
	{
		m_background = new BackgroundObject();// if not using an image
		m_tileData = "assets/data/mapTiles/volcano/mapTilesVolcano.json";
		m_objectData = "assets/data/mapObjects/volcano/mapObjectsVolcanoI.json";
		m_tileSet = "terrainLava";
		m_objectSet = "overworldObjectsLava";
		m_background->setColour(255, 0, 0, 255);
		break;
	}
	case FG:
	{
		break;
	}
	case FV:
	{
		break;
	}
	case FI:
	{
		break;
	}
	case GF:
	{
		break;
	}
	case GV:
	{
		break;
	}
	case GI:
	{
		break;
	}
	case VF:
	{
		break;
	}
	case VG:
	{
		break;
	}
	case VI:
	{
		break;
	}
	case IF:
	{
		break;
	}
	case IG:
	{
		break;
	}
	case IV:
	{
		break;
	}
	case FGV:
	{
		break;
	}
	case FGI:
	{
		break;
	}
	case FVG:
	{
		break;
	}
	case FIG:
	{
		break;
	}
	case FIV:
	{
		break;
	}
	case GFV:
	{
		break;
	}
	case GFI:
	{
		break;
	}
	case GVF:
	{
		break;
	}
	case GVI:
	{
		break;
	}
	case GIF:
	{
		break;
	}
	case GIV:
	{
		break;
	}
	case VFG:
	{
		break;
	}
	case VFI:
	{
		break;
	}
	case VGF:
	{
		break;
	}
	case VGI:
	{
		break;
	}
	case VIF:
	{
		break;
	}
	case VIG:
	{
		break;
	}
	case IFG:
	{
		break;
	}
	case IFV:
	{
		break;
	}
	case IGF:
	{
		break;
	}
	case IGV:
	{
		break;
	}
	case IVF:
	{
		break;
	}
	case IVG:
	{
		break;
	}
	}
}

void VolcanoScene::saveScene()
{
	/*int rootsize;
	std::string name;
	std::fstream jsonData;
	std::ofstream jsonDataOut;
	Json::Value root;
	Json::Value nameNode;
	Json::Reader reader;
	Json::customJsonWriter writer;
	jsonData.open("assets/data/map1.json");
	reader.parse(jsonData, root);
	for (int i = 0; i < (int)root["map"].size(); i++)
	{
		root["map"][i]["MapTileNo"] = mv_mapTiles[i]->m_tileNo;
		root["map"][i]["SpriteNo"] = mv_mapTiles[i]->m_spriteNo;
		root["map"][i]["Collision"] = mv_mapTiles[i]->m_colision;
	}
	rootsize = root["map"].size();
	for (int i = 8882; i < 28800; i += 480)
	{
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i;
		root["map"][rootsize]["SpriteNo"] = 191;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 1;
		root["map"][rootsize]["SpriteNo"] = 54;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 2;
		root["map"][rootsize]["SpriteNo"] = 55;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 3;
		root["map"][rootsize]["SpriteNo"] = 22;
		root["map"][rootsize]["Collision"] = true;
		rootsize++;

		root["map"][rootsize]["MapTileNo"] = i + 240;
		root["map"][rootsize]["SpriteNo"] = 191;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 241;
		root["map"][rootsize]["SpriteNo"] = 62;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 242;
		root["map"][rootsize]["SpriteNo"] = 63;
		root["map"][rootsize]["Collision"] = false;
		rootsize++;
		root["map"][rootsize]["MapTileNo"] = i + 243;
		root["map"][rootsize]["SpriteNo"] = 20;
		root["map"][rootsize]["Collision"] = true;
	}

	jsonData.close();
	jsonDataOut.open("assets/data/map4.json");
	writer.write(jsonDataOut, root);
	jsonDataOut.close();*/
}
