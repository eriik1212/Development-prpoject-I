#ifndef __MODULE_TITLESCREEN_H__
#define __MODULE_TITLESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Scene.h"
#include "GuiButton.h"


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

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	void DrawOptionsMenu();

public:
	// Members Texture
	SDL_Texture* Title;
	SDL_Texture* NewGamePressed;
	SDL_Texture* NewGameUnpressed;
	SDL_Texture* ContinuePressed;
	SDL_Texture* ContinueUnpressed;
	SDL_Texture* exitGameUnpressed;
	SDL_Texture* exitGamePressed;
	SDL_Texture* settingsUnpressed;
	SDL_Texture* settingsPressed;
	SDL_Texture* creditsUnpressed;
	SDL_Texture* creditsPressed;
	SDL_Texture* exitOptions;
	SDL_Texture* exitOptionsFocused;
	SDL_Texture* exitOptionsPressed;
	SDL_Texture* SelectArrow;

	uint changeFX;
	uint enterFX;

	int option=1;
	uint TitleMusic;
	SDL_Rect backgroundTitle,
		NewGameRect,
		ContinueRect,
		settingsRect,
		creditsRect,
		exitGameRect,
		exitOptionsRect;

	bool cont;

	bool optionsEnabled = false;
	bool exitButtonCreated = false;

	bool exitGameRequest = false;

private:
	GuiButton* newGameButton;
	GuiButton* continueButton;
	GuiButton* settingsButton;
	GuiButton* creditsButton;
	GuiButton* exitGameButton;
	GuiButton* exitOptionsButton;
};

#endif //__MODULE_MEMBERS_H__

