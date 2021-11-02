#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Module.h"
#include "Point.h"

#include <math.h>

class Collider
{
public:
	Collider(SDL_Rect& body);
	~Collider();

	bool CheckCollision(Collider& other, float push);

	void Move(float dx, float dy) 
	{ 
		body.x += dx; 
		body.y += dy;
	}
	
	iPoint GetPosition() { return iPoint(body.x + body.w / 2, body.y + body.h / 2); }
	iPoint GetHalfSize() { return iPoint(body.w / 2, body.h / 2); }
private:
	SDL_Rect& body;
};

#endif // !__COLLIDER_H__

