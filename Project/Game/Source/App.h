#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PerfTimer.h"
#include "Timer.h"

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
class Level2;
class Map;
class LogoScreen;
class Player;
class TitleScreen;
class ModuleEnemies;
class ModuleHUD;
class Enemy_Bird;
class Enemy_Fox;
class ModuleFonts;
class EntityManager;
//class ModuleCollisions;
class ModuleFadeToBlack;
class GameOverScreen;
class GuiManager;

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
	void LoadInitialGameRequest();
	void SaveGameRequest() const;
	void SaveInitialGameRequest() const;


	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;
private:

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
	bool LoadInitialGame();
	bool SaveGame() const;
	bool SaveInitialGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Level2* level2;
	Map* map;
	LogoScreen* logo;
	TitleScreen* title;
	Player* play;
	ModuleEnemies* enemies;
	ModuleHUD* hud;
	Enemy_Bird* bird_enemy;
	Enemy_Fox* fox_enemy;
	ModuleFadeToBlack* fade;
	ModuleFonts* font;
	EntityManager* entityManager;
	//ModuleCollisions* collisions;
	GameOverScreen* gameOver;
	GuiManager* guiManager;

	bool lowFPS = false;
	int timer = 0;
	char textTimer[10] = { "\0" };
private:

	int argc;
	char** args;
	SString title1;
	SString organization;

	List<Module *> modules;

	
	uint frames;
	

	mutable bool saveGameRequested;
	mutable bool saveInitialGameRequested;
	bool loadGameRequested;
	bool loadInitialGameRequested;
	

	float averageFps = 0.0f;
	float dt = 0.0f;
	int maxFrameRate;
	PerfTimer* frameDuration;

	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;
};

extern App* app;

#endif	// __APP_H__
