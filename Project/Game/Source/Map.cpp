
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Scene.h"
#include "Player.h"
#include "ModuleCollisions.h"
#include "Enemies.h"
#include "Enemy_Bird.h"
#include "Enemy.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map(bool enabled) : Module(enabled), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());


    return ret;
}

void Map::ResetPath()
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	path.Clear();

	
	frontier.Push(iPoint(5, 4), 0);
	visited.add(iPoint(5, 4));
	breadcrumbs.add(iPoint(5, 4));
	
	memset(costSoFar, 0, sizeof(uint) * COST_MAP_SIZE * COST_MAP_SIZE);
}

void Map::DrawPath()
{
	iPoint point;

	// Draw visited
	ListItem<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(301);

		SDL_Rect rec = tileset->GetTileRect(301);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(pathfinding, pos.x, pos.y, true, &rec);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(302);

		SDL_Rect rec = tileset->GetTileRect(302);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(pathfinding, pos.x, pos.y, true, &rec);
	}

	// Draw path
	for (uint i = 0; i < path.Count(); ++i)
	{
		iPoint pos = MapToWorld(path[i].x, path[i].y);
		app->render->DrawTexture(tileX, pos.x, pos.y, true);
	}

}

bool Map::IsWalkable(int x, int y) const
{
	// L10: DONE 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)

	bool isWalkable = false;

	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	while (mapLayerItem != NULL) {
		if (x >= 0 && y >= 0 && x < mapData.width && y < mapData.height) {

			//gets the second layer
			MapLayer* layer = mapData.layers.start->next->data;
			int tileId = layer->Get(x, y);
			if (mapLayerItem->data->properties.GetProperty("Navigation") != 1) isWalkable = true;
		}
		return isWalkable;
	}
}

void Map::ComputePath(int x, int y)
{
	path.Clear();
	iPoint goal = WorldToMap(x, y);

	// L11: TODO 2: Follow the breadcrumps to goal back to the origin
	// add each step into "path" dyn array (it will then draw automatically)
	
	path.PushBack(goal);
	int index = visited.find(goal);

	if (index == -1)
	{
		app->play->inEnemyView = false;

	}
	else
	{
		app->play->inEnemyView = true;

	}

	while ((index >= 0) && (goal != breadcrumbs[index]))
	{

		goal = breadcrumbs[index];
		path.PushBack(goal);
		index = visited.find(goal);

	}
}

void Map::PropagateBFS()
{
	// L10: DONE 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors
	iPoint curr;
	if (frontier.Pop(curr))
	{
		// L10: DONE 2: For each neighbor, if not visited, add it
		// to the frontier queue and visited list
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			if (IsWalkable(neighbors[i].x, neighbors[i].y))
			{
				if (visited.find(neighbors[i]) == -1)
				{
					frontier.Push(neighbors[i], 0);
					visited.add(neighbors[i]);

					// L11: TODO 1: Record the direction to the previous node 
					// with the new list "breadcrumps"
					breadcrumbs.add(curr);
				}
			}
		}
	}
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	while (mapLayerItem != NULL) {
		
		if (mapLayerItem->data->properties.GetProperty("Draw") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y, true,
							&r);
					}

				}
			}
		}

		if (mapLayerItem->data->properties.GetProperty("Navigation") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						if (app->play->collidersOn)
						{
							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y + (32 - r.h), true,
								&r);
						}

						if (pos.x < (app->play->playerData.playerBody.x + 50) && pos.x >(app->play->playerData.playerBody.x - 50))
						{
							tilesColliders.AddCollider(pos.x, pos.y + (32 - r.h), r.w, r.h);

							tilesColliders.GetCollider().CheckCollision(app->play->playerData.GetCollider(), 1.0f, WALL);

							if (app->play->collidersOn)
							{
								tilesColliders.GetCollider().DebugDraw({ pos.x, pos.y + (32 - r.h), r.w, r.h }, WALL);
							}
						}

					}

				}
			}
		}

		if (mapLayerItem->data->properties.GetProperty("DieSensors") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						if (app->play->collidersOn)
						{
							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y + (32 - r.h), true,
								&r);
						}

						if (pos.x < (app->play->playerData.playerBody.x + 50) && pos.x >(app->play->playerData.playerBody.x - 50))
						{
							dieColliders.AddCollider(pos.x, pos.y + (32 - r.h), r.w, r.h);

							dieColliders.GetCollider().CheckCollision(app->play->playerData.GetCollider(), 0.0f, DEAD);

							if (app->play->collidersOn)
							{
								dieColliders.GetCollider().DebugDraw({ pos.x, pos.y + (32 - r.h), r.w, r.h }, DEAD);
							}
						}
					}

				}
			}
		}

		if (mapLayerItem->data->properties.GetProperty("WinSensors") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						if (app->play->collidersOn)
						{
							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y + (32 - r.h), true,
								&r);
						}

						if (pos.x < (app->play->playerData.playerBody.x + 50) && pos.x >(app->play->playerData.playerBody.x - 50))
						{
							winColliders.AddCollider(pos.x, pos.y + (32 - r.h), r.w, r.h);

							winColliders.GetCollider().CheckCollision(app->play->playerData.GetCollider(), 0.0f, WIN);

							if (app->play->collidersOn)
							{
								winColliders.GetCollider().DebugDraw({ pos.x, pos.y + (32 - r.h), r.w, r.h }, WIN);
							}
						}
					}

				}
			}
		}

		if (mapLayerItem->data->properties.GetProperty("Leader") == 1) {

			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//now we always use the firt tileset in the list
						//TileSet* tileset = mapData.tilesets.start->data;
						TileSet* tileset = GetTilesetFromTileId(gid);

						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						if (app->play->collidersOn)
						{
							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y + (32 - r.h), true,
								&r);
						}

						if (pos.x < (app->play->playerData.playerBody.x + 50) && pos.x >(app->play->playerData.playerBody.x - 50))
						{
							leaderColliders.AddCollider(pos.x, pos.y + (32 - r.h), r.w, r.h);

							leaderColliders.GetCollider().CheckCollision(app->play->playerData.GetCollider(), 0.0f, LEADER);

							if (app->play->collidersOn)
							{
								leaderColliders.GetCollider().DebugDraw({ pos.x, pos.y + (32 - r.h), r.w, r.h }, LEADER);
							}
						}
					}

				}
			}
		}

		mapLayerItem = mapLayerItem->next;

		if (app->play->collidersOn)
		{
			DrawPath();
			
		}
	}

}

iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapData.tileWidth / 2);
		ret.y = (x + y) * (mapData.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapData.tileWidth * 0.5f;
		float half_height = mapData.tileHeight * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);
	tileX = app->tex->Load("Assets/maps/x.png");
	pathfinding = app->tex->Load("Assets/maps/pathfinding.png");

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
    if(ret == true)
    {
        //LOG all the data loaded iterate all tilesets and LOG everything

		// LOG the info for each loaded layer
    }

    mapLoaded = ret;

    return ret;
}

bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// L05: DONE 1: Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// L03: DONE 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}

	return ret;
}

// Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 4: Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();

	//L06: TODO 6 Call Load Propoerties
	LoadProperties(node, layer->properties);

	//Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		//add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
	{
		Properties::Property *p = new Properties::Property();
		p->name = propertieNode.attribute("name").as_string();
		p->value = propertieNode.attribute("value").as_int();

		properties.list.add(p);
	}
	
	return ret;
}

bool Map::LoadState(pugi::xml_node& data)
{
	//Load Map Level
	app->play->lastLevel = data.child("level").attribute("num").as_int();

	return true;
}

bool Map::SaveState(pugi::xml_node& data) const
{
	//Save Map Level
	pugi::xml_node map = data.append_child("level");

	map.append_attribute("num") = app->play->lastLevel;

	return true;
}