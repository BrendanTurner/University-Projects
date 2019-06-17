#pragma once
#include <iostream>
#include <algorithm>
#include "defines.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "SpriteComponents.h"
#include "CollisionComponent.h"
#include "TransitionComponent.h"

CollisionManager::CollisionManager()
{
	m_exit = nullptr;
}

TransitionComponent* CollisionManager::handleCollisions()
{
	dynamicOnMap();
	dynamicOnStatic();
	dynamicOnDynamic();
	staticOnMap();
	return dynamicOnTrigger();
}

void CollisionManager::dynamicOnMap()
{
	colliderProcess(mv_dynamicObjects, mv_mapTilesWithColliders);
}

void CollisionManager::dynamicOnStatic()
{
	colliderProcess(mv_dynamicObjects, mv_staticObjects);
}

void CollisionManager::dynamicOnDynamic()
{
	colliderProcess(mv_dynamicObjects, mv_dynamicObjects);
}

void CollisionManager::staticOnMap()
{
	colliderProcess(mv_staticObjects, mv_mapTilesWithColliders);
}

TransitionComponent* CollisionManager::dynamicOnTrigger()
{
	colliderProcess(mv_dynamicObjects, mv_triggerObjects);
	for (int i = 0; i < (int)mv_triggerObjects.size();i++)
		if (mv_triggerObjects[i]->getComponent<InteractComponent>()->getType() == changeScene)
		{
			m_exit = mv_triggerObjects[i]->getComponent<TransitionComponent>();
		}
	return m_exit;
}

void CollisionManager::colliderProcess(std::vector<GameObject*> colliders1, std::vector<GameObject*>colliders2)
{
	for (int i = 0; i < (int)colliders1.size(); i++)
	{
		for (int j = 0; j < (int)colliders2.size(); j++)
		{
			if (!(colliders1 == colliders2 && i == j))
			{
				if (colliders1[i]->m_hasMoved || colliders2[j]->m_hasMoved)
				{
					sf::FloatRect collider1 = colliders1[i]->getComponent<CollisionComponent>()->getRect();
					sf::FloatRect collider2 = colliders2[j]->getComponent<CollisionComponent>()->getRect();
					ColliderType type1 = colliders1[i]->getComponent<CollisionComponent>()->getType();
					ColliderType type2 = colliders2[j]->getComponent<CollisionComponent>()->getType();

					if (collider1.intersects(collider2))
					{
						float rightOverlap = collider1.left + collider1.width - collider2.left;
						float leftOverlap = collider2.left + collider2.width - collider1.left;
						float topOverlap = collider2.top + collider2.height - collider1.top;
						float bottomOverlap = collider1.top + collider1.height - collider2.top;

						if (rightOverlap < leftOverlap)
						{
							if (rightOverlap < topOverlap)
							{
								if (rightOverlap < bottomOverlap)
								{
									colliders1[i]->onCollision("right", rightOverlap, type2);
									colliders2[j]->onCollision("left", rightOverlap, type1);
								}
								else
								{
									colliders1[i]->onCollision("bottom", bottomOverlap, type2);
									colliders2[j]->onCollision("top", bottomOverlap, type1);
								}
							}
							else if (topOverlap < bottomOverlap)
							{
								colliders1[i]->onCollision("top", topOverlap, type2);
								colliders2[j]->onCollision("bottom", topOverlap, type1);
							}
							else
							{
								colliders1[i]->onCollision("bottom", bottomOverlap, type2);
								colliders2[j]->onCollision("top", bottomOverlap, type1);
							}
						}
						else if (leftOverlap < topOverlap)
						{
							if (leftOverlap < bottomOverlap)
							{
								colliders1[i]->onCollision("left", leftOverlap, type2);
								colliders2[j]->onCollision("right", leftOverlap, type1);
							}
							else
							{
								colliders1[i]->onCollision("bottom", bottomOverlap, type2);
								colliders2[j]->onCollision("top", bottomOverlap, type1);
							}
						}
						else if (topOverlap < bottomOverlap)
						{
							colliders1[i]->onCollision("top", topOverlap, type2);
							colliders2[j]->onCollision("bottom", topOverlap, type1);
						}
						else
						{
							colliders1[i]->onCollision("bottom", bottomOverlap, type2);
							colliders2[j]->onCollision("top", bottomOverlap, type1);
						}
					}
					if (colliders1[i]->getComponent<InteractComponent>() != nullptr)
					{
						sf::FloatRect interact1 = colliders1[i]->getComponent<InteractComponent>()->getRect();
						sf::FloatRect collider3 = colliders2[j]->getComponent<CollisionComponent>()->getRect();
						ColliderType interactType = colliders1[i]->getComponent<InteractComponent>()->getType();
						if (interactType != empty)
						{
							if (interact1.intersects(collider3))
							{
								float rightOverlap = interact1.left + interact1.width - collider3.left;
								float leftOverlap = collider3.left + collider3.width - interact1.left;
								float topOverlap = collider3.top + collider3.height - interact1.top;
								float bottomOverlap = interact1.top + interact1.height - collider3.top;

								if (rightOverlap < leftOverlap)
								{
									if (rightOverlap < topOverlap)
									{
										if (rightOverlap < bottomOverlap)
										{
											colliders2[j]->onCollision("left", rightOverlap, interactType);
										}
										else
										{
											colliders2[j]->onCollision("top", bottomOverlap, interactType);
										}
									}
									else if (topOverlap < bottomOverlap)
									{
										colliders2[j]->onCollision("bottom", topOverlap, interactType);
									}
									else
									{
										colliders2[j]->onCollision("top", bottomOverlap, interactType);
									}
								}
								else if (leftOverlap < topOverlap)
								{
									if (leftOverlap < bottomOverlap)
									{
										colliders2[j]->onCollision("right", leftOverlap, interactType);
									}
									else
									{
										colliders2[j]->onCollision("top", bottomOverlap, interactType);
									}
								}
								else if (topOverlap < bottomOverlap)
								{
									colliders2[j]->onCollision("bottom", topOverlap, interactType);
								}
								else
								{
									colliders2[j]->onCollision("top", bottomOverlap, interactType);
								}
							}
						}
					}
				}
			}
		}
	}
}