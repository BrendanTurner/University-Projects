#pragma once
#include "TransitionComponent.h"
TransitionComponent::TransitionComponent(MapEntrance exit, MapName destination)
{
	m_destination = destination;
	m_entrance = exit;
}
void TransitionComponent::onUpdate(float dt)
{
}
void TransitionComponent::onMessage(const std::string message)
{
}
MapEntrance TransitionComponent::getEntrance()
{
	return m_entrance;
}

MapName TransitionComponent::getDestination()
{
	return m_destination;
}