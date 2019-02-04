#pragma once
#include "SFML/Graphics.hpp"
#include "Components.h"

namespace sf
{
	class RenderWindow;
}

struct World;
enum Component;

class SystemManager
{
public:
	void loadLayer1(const char* tileSetPath);
	void loadBody(const char* tileSetPath);
	void loadHead(const char* tileSetPath);
	SystemManager(World* currentWorld);
	void renderScreen();
private:
	bool isMoving();
	bool isBody(Entity& entity) { return (findEntity(EntityComponents::Body) == entity); };
	bool isHead(Entity& entity) { return (findEntity(EntityComponents::Head) == entity); };
	void setHeadGrhPos(Entity& entity, DrawingData::Data& drawingData);
	void setBodyGrhPos(Entity& entity, DrawingData::Data& drawingData);
	void refreshAnimation(sf::Clock& refreshClock, Entity entity);
	void setTexture(const char* texturePath, Entity entity);
	void loadTileMap(const char* tileSetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	unsigned int findEntity(const EntityComponents components);
	World* world;
};

