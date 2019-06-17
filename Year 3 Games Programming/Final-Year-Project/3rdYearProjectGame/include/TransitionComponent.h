#pragma once
#include "defines.h"
#include "Component.h"

class TransitionComponent : public Component
{
public:
	TransitionComponent(MapEntrance exit, MapName destination);
	void onUpdate(float dt) override;
	void onMessage(const std::string message) override;
	MapEntrance getEntrance();
	MapName getDestination();
private:
	MapEntrance m_entrance;
	MapName m_destination;
};