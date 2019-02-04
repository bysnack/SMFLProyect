#include "pch.h"
#include "EntityManager.h"
#include "Components.h"
#include <iostream>
#include <iterator>

EntityManager::EntityManager(World* currentWorld)
{
	world = currentWorld;

	//initialazing entities in memory
	for (Entity entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		world->mask[entity] = COMPONENT_NONE;
	}
}

unsigned int EntityManager::placeEntity()
{
	Entity entity;
	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if (world->mask[entity] == COMPONENT_NONE)
		{
			return entity;
		}
	}
	std::cout << "No more place for entities left in memory" << std::endl;
	return ENTITY_COUNT;
}

void EntityManager::destroyEntity(Entity entity)
{
	world->mask[entity] = COMPONENT_NONE;
}

unsigned int EntityManager::createEntity(const EntityComponents components, std::string name)
{
	Entity entity = placeEntity();

	world->entityName[entity] = name;

	world->mask[entity] = components;

	return entity;
}

std::vector<std::pair<Entity, std::string>> EntityManager::getEntitiesByComponents(std::vector<Component> components)
{
	std::vector<std::pair<Entity, std::string>> entityVector;
	int componentSelection = COMPONENT_NONE;
	for (auto it = components.begin(); it != components.end(); it++)
	{
		componentSelection |= *it;
	}

	for (Entity entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if ((world->mask[entity] & componentSelection) == componentSelection)
		{
			entityVector.push_back(std::make_pair(entity, world->entityName[entity]));
			std::cout << " index "<< entity << " " << world->entityName[entity] << " found." << std::endl;
		}
	}

	if (entityVector.empty())
		std::cout << "There are no entities with those components" << std::endl;

	return entityVector;
}