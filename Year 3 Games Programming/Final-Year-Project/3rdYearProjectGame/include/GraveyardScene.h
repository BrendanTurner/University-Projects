#pragma once
#include "Scene.h"
class GraveyardScene : public Scene
{
public:
	GraveyardScene();
	~GraveyardScene();
	void setSceneVariables();
	void saveScene()override;
};