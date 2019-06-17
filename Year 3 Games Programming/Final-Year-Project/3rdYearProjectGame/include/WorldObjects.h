#pragma once
#include<SFML\Graphics.hpp>
#include "GameObject.h"
#include "defines.h"

class worldObject : public GameObject
{
public:
	void onUpdate(std::map<std::string, bool>* storyTriggers, unsigned short frameNo);
	void onMessage(const std::string message);
	void onCollision(const std::string direction, const float correction, ColliderType type);
	void onDraw(sf::RenderWindow* window);
protected:
	bool m_isTriggered;
	virtual void trigger(std::map<std::string, bool>* storyTriggers);
	DirectionState m_direction;
	ObjectState m_state;
	ObjectAtrib m_atrib;
};

class ShrubObject : public worldObject
{
public:
	ShrubObject(sf::Image* image, int posX, int posY);
};

class LightStoneObject : public worldObject
{
public:
	LightStoneObject(sf::Image* image, int posX, int posY);
};

class HeavyStoneObject : public worldObject
{
public:
	HeavyStoneObject(sf::Image* image, int posX, int posY);
};

class SignObject : public worldObject
{
public:
	SignObject(sf::Image* image, int posX, int posY);
};

class GrassObject : public worldObject
{
public:
	GrassObject(sf::Image* image, int posX, int posY);
};

class GrassCoveredPitObject : public worldObject
{
public:
	GrassCoveredPitObject(sf::Image* image, int posX, int posY);
};

class StumpObject : public worldObject
{
public:
	StumpObject(sf::Image* image, int posX, int posY);
};

class BreakableStoneObject : public worldObject
{
public:
	BreakableStoneObject(sf::Image* image, int posX, int posY);
};

class PressurePlate : public worldObject
{
public:
	PressurePlate(sf::Image* image, int posX, int posY, ObjectAtrib atrib);
};

class FirePitObject : public worldObject
{
public:
	FirePitObject(sf::Image* image, int posX, int posY);
};

class WoodBenchObject : public worldObject
{
public:
	WoodBenchObject(sf::Image* image, int posX, int posY);
};

class LargeLightStoneObject : public worldObject
{
public:
	LargeLightStoneObject(sf::Image* image, int posX, int posY);
};

class LargeHeavyStoneObject : public worldObject
{
public:
	LargeHeavyStoneObject(sf::Image* image, int posX, int posY);
};

class PierObject : public worldObject
{
public:
	PierObject(sf::Image* image, int posX, int posY);
};

class LargeStumpObject : public worldObject
{
public:
	LargeStumpObject(sf::Image* image, int posX, int posY);
};

class LargeBreakableStoneObject : public worldObject
{
public:
	LargeBreakableStoneObject(sf::Image* image, int posX, int posY);
};

class TentObject : public worldObject
{
public:
	TentObject(sf::Image* image, int posX, int posY);
};

class CattleBonesObject : public worldObject
{
public:
	CattleBonesObject(sf::Image* image, int posX, int posY);
};

class CactusObject : public worldObject
{
public:
	CactusObject(sf::Image* image, int posX, int posY);
};