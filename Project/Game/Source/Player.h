#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Render.h"

struct SDL_Texture;

struct PlayerData
{
	int width, height;
	int	x, y;

	int xVel;
	int gravity;
};

class Player : public Module
{
public:

	Player();

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

	bool jumping = false;
	bool canJumpAgain = false;
	int playerYVel;


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
		idleAnimR;

	int direction; //1 if player looks right, 0 if player looks left
};
#endif // __PLAYER_H__