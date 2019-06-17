#pragma once

class GameObject;

class InputCommand
{
public:
	virtual void execute(GameObject& gameObject) = 0;
};

class PlayerUp : public InputCommand
{
	void execute(GameObject& gameObject);
};

class PlayerDown : public InputCommand
{
	void execute(GameObject& gameObject);
};

class PlayerLeft : public InputCommand
{
	void execute(GameObject& gameObject);
};

class PlayerRight : public InputCommand
{
	void execute(GameObject& gameObject);
};