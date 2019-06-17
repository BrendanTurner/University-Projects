#include "InputCommands.h"
#include "GameObject.h"

void PlayerUp::execute(GameObject& gameObject)
{
	gameObject.onMessage("playerUp");
}

void PlayerDown::execute(GameObject& gameObject)
{
	gameObject.onMessage("playerDown");
}

void PlayerLeft::execute(GameObject& gameObject)
{
	gameObject.onMessage("playerLeft");
}

void PlayerRight::execute(GameObject& gameObject)
{
	gameObject.onMessage("playerRight");
}