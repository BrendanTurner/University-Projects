#pragma once
#include "Scene.h"
class VolcanoScene : public Scene
{
public:
	VolcanoScene();
	~VolcanoScene();
	void setSceneVariables();
	void saveScene()override;
};