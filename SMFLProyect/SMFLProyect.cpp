#include "pch.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <sstream>
#include <vector>
#include "EntityManager.h"
#include "SystemManager.h"

int main()
{
	World world;

	SystemManager sManager(&world);
	EntityManager eManager(&world);

	eManager.createEntity(EntityComponents::FirstLayer, "vertices");
	sManager.loadLayer1("Graphics/15.png");
	eManager.createEntity(EntityComponents::Body, "body");
	sManager.loadBody("Graphics/17.png");
	eManager.createEntity(EntityComponents::Head, "head");
	sManager.loadHead("Graphics/16.png");
	sManager.renderScreen();

	return 0;
}
