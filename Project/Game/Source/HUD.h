#ifndef __MODULE_HUD_H__
#define __MODULE_HUD_H__

#include "Module.h"
#include "Animation.h"


struct SDL_Texture;

class ModuleHUD : public Module
{
public:
	//Constructor
	ModuleHUD(bool enabled);

	//Destructor
	~ModuleHUD();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	void Reset();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update(float dt);

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate();

	bool CleanUp();

	void DrawPauseMenu();

public:
	bool pauseEnabled = false;

	SDL_Rect heart1,
		heart2,
		heart3,
		inventory,
		soul1,
		soul2,
		soul3,
		soul4,
		soul5,
		soul6;

	SDL_Texture* InventoryTex = nullptr;

	SDL_Texture* FullHeartTex = nullptr;

	SDL_Texture* EmptyHeartTex = nullptr;

	SDL_Texture* DarkSoul = nullptr;


	// HUD & Foreground Animations
	/*Animation
		HUDP1,
		HUDP1InsertCoins,
		HUDP234,
		insertCoinP1,
		insertCoinP2,
		insertCoinP3,
		insertCoinP4,
		lifeP1,
		smallTurtle,
		pressStart;*/

	// Font score index
	/*uint scoreP1 = 000;
	uint scoreP234 = 000;
	uint lifes = 000;
	int scoreFont = -1;
	int lifeFont = -1;
	char scoreTextP1[10] = { "\0" };
	char scoreTextP234[10] = { "\0" };
	char lifeText[10] = { "\0" };*/

	// Sound effects indices
	uint lifeIncrease = 0;
	int lifes = 3;
	int soulCounter = 0;
	int GameFont = -1;

};


#endif //__MODULE_HUD_H__
