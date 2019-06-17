#pragma once
#include "Component.h"
#include "defines.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>

class GameObject//!a virtual class
{
public:
	template <typename T>
	T* getComponent()//!search the object for a component of specified type
	{

		auto iter = m_components.find(typeid(T));//!iterate through the map until a match is found

		if (iter != std::end(m_components))
		{
			// if found dynamic cast the component pointer and return it
			return dynamic_cast<T*>(iter->second);
		}

		// return null if we don't have a component of that type
		return nullptr;

	}

	template <typename T>
	void addComponent(T* comp)//!add a component to the object of a specified type
	{
		// add the component to an unoredered map with hash of its typeid
		m_components[typeid(T)] = comp;
	}
	virtual void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo) = 0;//!process this each update
	virtual void onMessage(const std::string m) = 0;//!process this when a message is passed
	virtual void onCollision(const std::string direction, const float correction, ColliderType type) = 0;
	virtual void onDraw(sf::RenderWindow* window) = 0;
	bool m_hasMoved;
protected:
	unsigned short m_animationcounter=0;
	unsigned short m_lastAnimatedFrame = 0;
private:
	std::unordered_map<std::type_index, Component*> m_components;//!an unordered map to store a pointer to a component and an id for it to be found within this class
};
