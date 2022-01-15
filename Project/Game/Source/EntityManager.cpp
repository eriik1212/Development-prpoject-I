#include "EntityManager.h"

#include "App.h"
#include "Item.h"
#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module(true)
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//L13: TODO 6: Initialize Entities from XML 
	pugi::xml_node entityNode;
	for (entityNode = config.child("entity"); entityNode != NULL; entityNode = entityNode.next_sibling())
	{
		uint32 id = entityNode.attribute("id").as_int();
		SString type = entityNode.attribute("type").as_string();
		int posX = entityNode.attribute("x").as_int();
		int posY = entityNode.attribute("y").as_int();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, int id, SDL_Rect bounds)
{
	Entity* entity = nullptr;

	//L13: TODO 1: Create an Entity and add it to the list of Entities
	switch (type)
	{

	case EntityType::ITEM:
		entity = new Item(id, bounds);
		break;
		//resto de casos aqui
	default: break;
	}
	if (entity != nullptr)entities.add(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.del(item);
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if (entity != nullptr) entities.add(entity);
}

bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	if (doLogic)
	{
		for (item = entities.start; item != NULL && ret == true; item = item->next)
		{
			pEntity = item->data;

			if (pEntity->active == false) continue;
			ret = item->data->Update(dt);
		}
	}

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->LoadState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

bool EntityManager::SaveState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		data.append_child(item->data->name.GetString());
		ret = item->data->SaveState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

bool EntityManager::Draw() {

	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Draw(app->render);
	}

	return ret;

}