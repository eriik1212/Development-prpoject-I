#ifndef __MODULE_HUD_H__
#define __MODULE_HUD_H__

#include "Module.h"
#include "Animation.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"


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

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

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

	SDL_Texture* exitOptions;
	SDL_Texture* exitOptionsFocused;
	SDL_Texture* exitOptionsPressed;

	SDL_Texture* settingsUnpressed;
	SDL_Texture* settingsPressed;

	SDL_Texture* SelectArrow;

	SDL_Texture* exitGameUnpressed;
	SDL_Texture* exitGamePressed;

	SDL_Texture* titleUnpressed;
	SDL_Texture* titlePressed;

	SDL_Texture* resumeUnpressed;
	SDL_Texture* resumePressed;

	SDL_Rect resumeRect,
		titleRect,
		exitRect,
		settingsRect,
		exitOptionsRect,
		fullscreenRect,
		vsyncRect,
		volumeRect,
		fxRect,
		sliderVolRect,
		sliderFXRect;

	GuiButton* resumeButton;
	GuiButton* titleButton;
	GuiButton* exitButton;
	GuiButton* settingsButton;
	GuiButton* exitOptionsButton;

	GuiCheckBox* fullscreenToggle;
	GuiCheckBox* vsyncToggle;

	GuiSlider* volumeSlider;
	GuiSlider* fxSlider;
	
	bool exitGameRequest = false;
	bool optionsEnabled = false;

	// Sound effects indices
	uint lifeIncrease = 0;
	int lifes = 3;
	int soulCounter = 0;
	int GameFont = -1;

};


#endif //__MODULE_HUD_H__
