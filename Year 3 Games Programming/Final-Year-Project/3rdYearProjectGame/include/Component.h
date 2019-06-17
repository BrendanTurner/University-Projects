#pragma once
#include <string>

class Component//!a virtual class
{
public:
	virtual void onUpdate(float dt) = 0;//!process this each update
	virtual void onMessage(const std::string message) = 0;//!process this when a message is passed

};

