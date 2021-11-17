#ifndef __MODULE_TITLESCREEN_H__
#define __MODULE_TITLESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Scene.h"



struct SDL_Texture;

class TitleScreen : public Module
{
public:
	//Constructor
	TitleScreen(bool enabled);

	//Destructor
	~TitleScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update(float dt);

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;


public:
	// Members Texture
	SDL_Texture* Title;
	SDL_Texture* NewGamePressed;
	SDL_Texture* NewGameUnpressed;
	SDL_Texture* ContinuePressed;
	SDL_Texture* ContinueUnpressed;

	uint changeFX;
	uint enterFX;
	int option=1;
	uint TitleMusic;
	SDL_Rect backgroundTitle, NewGameRect, ContinueRect;
	bool cont;

};

#endif //__MODULE_MEMBERS_H__

