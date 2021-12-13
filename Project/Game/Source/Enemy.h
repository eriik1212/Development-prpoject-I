#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Animation.h"
#include "Point.h"
#include "Collider.h"
#include "ModuleCollisions.h"

#define MAX_LIFE 3
#define MAX_LIFE_BOSS 15

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	void UpdateLifesBird(unsigned short* lifes, unsigned short damage);
	void UpdateLifesFox(unsigned short* lifes, unsigned short damage);

	// Handle Movement
	iPoint FlyingPath();
	iPoint FloorPath();
	bool moving;
	iPoint movingTo;
	float vel = 3.5f;

	// Called before quitting
	bool CleanUp();

public:
	// The current position in the world
	iPoint position;

	SDL_Rect birdBody;
	ModuleCollisions birdCollider;

	SDL_Rect foxBody;
	ModuleCollisions foxCollider;

	int direcction = 0;

	unsigned short lifes[MAX_LIFE];

	bool isFox = false;
	bool isBird = false;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;
	int damageFX = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;
	Collider* HIT = nullptr;
	Collider* SEE = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__
