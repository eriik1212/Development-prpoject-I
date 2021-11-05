#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#include "Module.h"
#include "Collider.h"

class ModuleCollisions
{
public:
	ModuleCollisions();
	~ModuleCollisions();

	Collider AddCollider(int x, int y, int w, int h);
	Collider GetCollider() { return Collider(colliderBody); }

	iPoint origin;

private:

	SDL_Rect colliderBody;
};

#endif // __MODULE_COLLISIONS_H__