#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "Collider.h"

struct SDL_Texture;
struct Collider;

struct PlayerData
{
	// The player's body
	SDL_Rect playerBody;

	int xVel, yVel;
	int gravity;

	bool jumping;
	bool canJumpAgain;

	bool isColliding, isCollidingUp, isCollidingDown, isCollidingL, isCollidingR;

	int direction; //1 if player looks right, 0 if player looks left

	Collider GetCollider() { return Collider(playerBody); }

};

class Player : public Module
{
public:

	Player(bool enabled);

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;



	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

private:
	SDL_Texture* img;

	// Load player general properties
	bool LoadPlayer(pugi::xml_node player);

public:
	PlayerData playerData;

	SDL_Texture* playerTex = nullptr;
	Animation walkR,
		walkL,
		jumpR,
		jumpL,
		idleAnimL,
		idleAnimR,
		deathAnimR,
		deathAnimL;

};
#endif // __PLAYER_H__