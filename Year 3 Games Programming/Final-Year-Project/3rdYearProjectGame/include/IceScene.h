#pragma once
#include "Scene.h"
class IceScene : public Scene
{
public:
	IceScene();
	~IceScene();
	void setSceneVariables();
	void saveScene()override;
};