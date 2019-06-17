#pragma once
#include "Scene.h"
class TownScene : public Scene
{
public:
	TownScene();
	~TownScene();
	void setSceneVariables();
	void saveScene()override;
};