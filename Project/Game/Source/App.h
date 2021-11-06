#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class LogoScreen;
class Player;
class TitleScreen;
//class ModuleCollisions;
class ModuleFadeToBlack;
class GameOverScreen;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // Methods to request Load / Save
	void LoadGameRequest();
	void LoadConfigRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool LoadGameFromConfig();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Map* map;
	LogoScreen* logo;
	TitleScreen* title;
	Player* play;
	ModuleFadeToBlack* fade;
	//ModuleCollisions* collisions;
	GameOverScreen* gameOver;
	
private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;


	uint frames;
	float dt;

	mutable bool saveGameRequested;
	bool loadGameRequested;
	bool loadConfigRequested;
};

extern App* app;

#endif	// __APP_H__
