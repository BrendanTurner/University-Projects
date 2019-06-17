#pragma once
#include<vector>
#include "TransitionComponent.h"

class GameObject;

class CollisionManager
{
public:
	std::vector<GameObject*> mv_staticObjects;
	std::vector<GameObject*> mv_dynamicObjects;
	std::vector<GameObject*> mv_mapTilesWithColliders;
	std::vector<GameObject*> mv_triggerObjects;
	TransitionComponent* m_exit;
	CollisionManager();
	TransitionComponent* handleCollisions();
	void dynamicOnMap();
	void dynamicOnStatic();
	void dynamicOnDynamic();
	void staticOnMap();
	TransitionComponent* dynamicOnTrigger();
	void colliderProcess(std::vector<GameObject*> colliders1, std::vector<GameObject*>colliders2);
};