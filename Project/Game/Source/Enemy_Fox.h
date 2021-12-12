#ifndef __ENEMY_FOX_H__
#define __ENEMY_FOX_H__

#include "Enemy.h"
#include "Point.h"

class Enemy_Fox : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Fox(int x, int y);

	float coolDown = 8.0f;
	float coolTime = 0.0f;
	float velociti = 1.0f;

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world


	iPoint positionEnemy;

	// Enemy animations
	Animation FoxWalkL,
		FoxWalkR,
		FoxIdleR,
		FoxIdleL;



};

#endif // __ENEMY_FOX_H__
