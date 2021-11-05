#include "ModuleCollisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Player.h"
#include "SString.h"
#include "SDL/include/SDL_Scancode.h"

#include "Log.h"


ModuleCollisions::ModuleCollisions()
{
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Collider ModuleCollisions::AddCollider(int x, int y, int w, int h)
{
	colliderBody.x = x;
	colliderBody.y = y;
	colliderBody.w = w;
	colliderBody.h = h;

	//origin = iPoint(colliderBody.x + colliderBody.w / 2, colliderBody.y + colliderBody.h / 2);

	return Collider(colliderBody);
}