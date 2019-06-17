#pragma once
#include "Scene.h"
class ForestScene : public Scene
{
public:
	ForestScene();
	~ForestScene();
	void setSceneVariables();
	void saveScene()override;
};