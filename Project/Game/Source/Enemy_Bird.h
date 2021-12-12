#ifndef __ENEMY_BIRD_H__
#define __ENEMY_BIRD_H__

#include "Enemy.h"
#include "ModuleCollisions.h"
#include "Point.h"

class Enemy_Bird : public Enemy, public Module
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Bird(bool enabled, int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//void Bird_Movement();

private:
	// The path that will define the position in the world
	
	iPoint positionEnemy;

	// Enemy animations
	Animation leftStandB,
		rightStandB,
		leftFlyB,
		rightFlyB,
		rightAttackB,
		leftAttackB;

	uint coolDownBird = 0;

};

#endif // __ENEMY_BIRD_H__
