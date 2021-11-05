#ifndef __MODULE_GAMEOVERSCREEN_H__
#define __MODULE_GAMEOVERSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Scene.h"



struct SDL_Texture;

class GameOverScreen : public Module
{
public:
	//Constructor
	GameOverScreen(bool enabled);

	//Destructor
	~GameOverScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update(float dt);

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp();
	
public:
	// Members Texture
	SDL_Texture* GameOverTex;
	//uint LostGameFX;
	
};

#endif //__MODULE_MEMBERS_H__

