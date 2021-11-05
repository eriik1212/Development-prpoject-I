#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Module.h"
#include "Point.h"
#include "App.h"

#include <math.h>

enum CollidersType
{
	PLAYER = 0, //0
	WALL, // 1
	DEAD, // 2
	WIN //3
};

class Collider
{
public:
	Collider(SDL_Rect& body);
	~Collider();

	bool CheckCollision(Collider& other, float push, CollidersType type);

	void Move(float dx, float dy) 
	{ 
		body.x += dx; 
		body.y += dy;
	}
	
	iPoint GetPosition() { return iPoint(body.x + body.w / 2, body.y + body.h / 2); }
	iPoint GetHalfSize() { return iPoint(body.w / 2, body.h / 2); }

	// Draws all existing colliders with some transparency
	// PLAYER = 0, WALL = 1, DEAD = 2, WIN = 3
	void DebugDraw(SDL_Rect body, int type);
private:
	SDL_Rect& body;
};

#endif // !__COLLIDER_H__

