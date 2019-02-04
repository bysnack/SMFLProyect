#pragma once
#include "Components.h"
#include <memory>
#include <string>
#include <vector>

constexpr auto ENTITY_COUNT = 100;;

struct World
{
	std::string entityName[ENTITY_COUNT];
	int mask[ENTITY_COUNT];

	Vertices vertices[ENTITY_COUNT];
	RelativePosition rPosition[ENTITY_COUNT];
	Position position[ENTITY_COUNT];
	Drawing drawing[ENTITY_COUNT];
	Heading heading[ENTITY_COUNT];
};

class EntityManager
{
public:
	EntityManager(World* world);
	Entity createEntity(const EntityComponents components, std::string name);
	void destroyEntity(Entity entity);
	std::vector<std::pair<Entity, std::string>> getEntitiesByComponents(std::vector<Component> components);

private:
	unsigned int placeEntity();
	World* world;
};

