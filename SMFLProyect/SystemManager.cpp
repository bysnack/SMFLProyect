#include "pch.h"
#include "SystemManager.h"
#include "SFML/Graphics.hpp"
#include "EntityManager.h"
#include"SFML/System/Clock.hpp"
#include <iostream>

constexpr float SCREEN_WIDTH = 1080;
constexpr float SCREEN_HEIGHT = 768;

SystemManager::SystemManager(World* currentWorld)
{
	world = currentWorld;
}

Entity SystemManager::findEntity(const EntityComponents components)
{
	for (Entity entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if (world->mask[entity]  == components)
		{
			return entity;
		}
	}
	std::cout << "Entity not found";
	return ENTITY_COUNT;
}

void SystemManager::setTexture(const char* texturePath, Entity entity)
{
	if (world->mask[entity] != ENTITY_COUNT)
	{
		sf::Texture& texture = (world->drawing[entity]).texture;
		sf::Sprite& sprite = (world->drawing[entity]).sprite;
		std::string& path = (world->drawing[entity]).path;
		path = texturePath;
		if (!texture.loadFromFile(path))
		{
			std::cout << "Texture failed loading from: " << path;
		}
		texture.setSmooth(true);
		texture.setRepeated(true);
		sprite.setTexture(texture);
	}
}

void SystemManager::loadTileMap(const char* tileSetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
}

void SystemManager::loadLayer1(const char* tileSetPath)
{
	Entity entity = findEntity(EntityComponents::FirstLayer);
	if (entity == ENTITY_COUNT)
		return;

	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(0.f, 0.f);
	quad[1].position = sf::Vector2f(SCREEN_WIDTH, 0.f);
	quad[2].position = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	quad[3].position = sf::Vector2f(0.f, SCREEN_HEIGHT);

	quad[0].texCoords = sf::Vector2f(0.f, 0.f);
	quad[1].texCoords = sf::Vector2f(1024.f, 0.f);
	quad[2].texCoords = sf::Vector2f(1024.f, 768.f);
	quad[3].texCoords = sf::Vector2f(0.f, 768.f);

	(world->vertices[entity]).vertexArray = quad;

	sf::Texture& texture = (world->vertices[entity]).texture;
	texture.setRepeated(true);

	if (!texture.loadFromFile(tileSetPath))
		return;
}

void SystemManager::loadBody(const char* tileSetPath)
{
	Entity entity = findEntity(EntityComponents::Body);
	if (entity == ENTITY_COUNT)
		return;

	sf::Texture& texture = (world->vertices[entity]).texture;

	if (!texture.loadFromFile(tileSetPath))
		return;

	(world->rPosition[entity]).y = 45.f;
	(world->rPosition[entity]).speed = (float)(0.05);

	float& rPosX = (world->rPosition[entity]).x;
	rPosX = 0.f;


	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(487.f, 359.f);
	quad[1].position = sf::Vector2f(512.f, 359.f);
	quad[2].position = sf::Vector2f(512.f, 400.f);
	quad[3].position = sf::Vector2f(487.f, 400.f);

	quad[0].texCoords = sf::Vector2f(rPosX, 0.f);
	quad[1].texCoords = sf::Vector2f(rPosX + 25.f, 0.f);
	quad[2].texCoords = sf::Vector2f(rPosX + 25.f, 45.f);
	quad[3].texCoords = sf::Vector2f(rPosX, 45.f);

	(world->vertices[entity]).vertexArray = quad;
}

void SystemManager::loadHead(const char* tileSetPath)
{
	Entity entity = findEntity(EntityComponents::Head);
	if (entity == ENTITY_COUNT)
		return;

	sf::Texture& texture = (world->vertices[entity]).texture;

	if (!texture.loadFromFile(tileSetPath))
		return;

	(world->rPosition[entity]).y = 0;
	(world->rPosition[entity]).speed = (float)(0.05);

	float& rPosX = (world->rPosition[entity]).x;
	rPosX = 0.f;


	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(487.f, 359.f);
	quad[1].position = sf::Vector2f(512.f, 359.f);
	quad[2].position = sf::Vector2f(512.f, 400.f);
	quad[3].position = sf::Vector2f(487.f, 400.f);

	quad[0].texCoords = sf::Vector2f(rPosX, 0.f);
	quad[1].texCoords = sf::Vector2f(rPosX + 16.f, 0.f);
	quad[2].texCoords = sf::Vector2f(rPosX + 16.f, 17.f);
	quad[3].texCoords = sf::Vector2f(rPosX, 17.f);

	(world->vertices[entity]).vertexArray = quad;
}

void SystemManager::renderScreen()
{
	sf::RenderWindow window(sf::VideoMode((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT), "MainView");
	sf::Clock clock;
	unsigned int i = 0;
	sf::Clock refreshClock;
	sf::Clock headRefreshClock;
	Entity entity;
	while (window.isOpen())
	{
		//fps
		float fps = sf::seconds(1.f) / clock.getElapsedTime();
		std::cout << fps << std::endl;
		system("cls");
		clock.restart();

		//main rendering
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		entity = findEntity(EntityComponents::FirstLayer);
		window.draw((world->vertices[entity]).vertexArray, &(world->vertices[entity]).texture);
		entity = findEntity(EntityComponents::Body);
		window.draw((world->vertices[entity]).vertexArray, &(world->vertices[entity]).texture);
		refreshAnimation(refreshClock, entity);
		entity = findEntity(EntityComponents::Head);
		window.draw((world->vertices[entity]).vertexArray, &(world->vertices[entity]).texture);
		refreshAnimation(headRefreshClock, entity);

		window.display();
	}
}

void SystemManager::refreshAnimation(sf::Clock& refreshClock, Entity entity)
{
	//Handdle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		world->heading[entity].heading = H_NORTH;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		world->heading[entity].heading = H_SOUTH;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		world->heading[entity].heading = H_EAST;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		world->heading[entity].heading = H_WEST;

	//Speed
	sf::Time elapsedTime = refreshClock.getElapsedTime();
	float& refreshRate = (world->rPosition[entity]).speed;
	sf::Time speed = sf::seconds(refreshRate);

	if (elapsedTime < speed)
		return;

	//Set Positions
	float& rPosY = (world->rPosition[entity]).y;
	float& rPosX = (world->rPosition[entity]).x;

	DrawingData::Data drawingData;

	if (isHead(entity))
		setHeadGrhPos(entity, drawingData);

	else if (isBody(entity))
		setBodyGrhPos(entity, drawingData);

	//Set vertex
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(drawingData.pos.pos1, drawingData.pos.pos2);
	quad[1].position = sf::Vector2f(drawingData.pos.pos3, drawingData.pos.pos2);
	quad[2].position = sf::Vector2f(drawingData.pos.pos3, drawingData.pos.pos4);
	quad[3].position = sf::Vector2f(drawingData.pos.pos1, drawingData.pos.pos4);

	quad[0].texCoords = sf::Vector2f(rPosX, rPosY);
	quad[1].texCoords = sf::Vector2f(rPosX + drawingData.offSet.x, rPosY);
	quad[2].texCoords = sf::Vector2f(rPosX + drawingData.offSet.x, rPosY + drawingData.offSet.y);
	quad[3].texCoords = sf::Vector2f(rPosX, rPosY + drawingData.offSet.y);

	(world->vertices[entity]).vertexArray = quad;

	//Reset
	elapsedTime = sf::microseconds(0);
	refreshClock.restart();
}

void SystemManager::setBodyGrhPos(Entity& entity, DrawingData::Data& drawingData)
{
	drawingData.pos.pos1 = 487.f;
	drawingData.pos.pos2 = 359.f;
	drawingData.pos.pos3 = 512.f;
	drawingData.pos.pos4 = 400.f;
	drawingData.offSet.x = 25.f;
	drawingData.offSet.y = 45.f;

	if (!isMoving())
	{
		(world->rPosition[entity]).x = 0;
		switch (world->heading[entity].heading)
		{
		case H_NORTH:
			(world->rPosition[entity]).y = 45;
			break;
		case H_SOUTH:
			(world->rPosition[entity]).y = 0;
			break;
		case H_EAST:
			(world->rPosition[entity]).y = 135;
			break;
		case H_WEST:
			(world->rPosition[entity]).y = 90;
			break;
		default:
			break;
		}
			

	}
	else
	{
		switch (world->heading[entity].heading)
		{
		case H_NORTH:
			(world->rPosition[entity]).y = 45;
			if ((world->rPosition[entity]).x < 125)
				(world->rPosition[entity]).x += 25.f;
			else
				(world->rPosition[entity]).x = 0.f;
			break;
		case H_SOUTH:
			(world->rPosition[entity]).y = 0;
			if ((world->rPosition[entity]).x < 125)
				(world->rPosition[entity]).x += 25.f;
			else
				(world->rPosition[entity]).x = 0.f;
			break;
		case H_EAST:
			(world->rPosition[entity]).y = 135;
			if ((world->rPosition[entity]).x < 100)
				(world->rPosition[entity]).x += 25.f;
			else
				(world->rPosition[entity]).x = 0.f;
			break;
		case H_WEST:
			(world->rPosition[entity]).y = 90;
			if ((world->rPosition[entity]).x < 100)
				(world->rPosition[entity]).x += 25.f;
			else
				(world->rPosition[entity]).x = 0.f;
			break;
		default:
			break;
		}
	}
}

void SystemManager::setHeadGrhPos(Entity& entity, DrawingData::Data& drawingData)
{
	drawingData.pos.pos1 = 491.f;
	drawingData.pos.pos2 = 359.f;
	drawingData.pos.pos3 = 507.f;
	drawingData.pos.pos4 = 376.f;
	drawingData.offSet.x = 16.f;
	drawingData.offSet.y = 17.f;

	(world->rPosition[entity]).y = 0;

	switch (world->heading[entity].heading)
	{
	case H_NORTH:
		(world->rPosition[entity]).x = 51.f;
		break;
	case H_SOUTH:
		(world->rPosition[entity]).x = 0.f;
		break;
	case H_EAST:
		(world->rPosition[entity]).x = 17.f;
		break;
	case H_WEST:
		(world->rPosition[entity]).x = 34.f;
		break;
	default:
		break;
	}
}

bool SystemManager::isMoving()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
}