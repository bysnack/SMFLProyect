#pragma once
#include "SFML/Graphics.hpp"
#include <string>

using Entity = unsigned int;

namespace DrawingData
{
	struct Position
	{
		float pos1;
		float pos2;
		float pos3;
		float pos4;
	};

	struct OffSet
	{
		float x;
		float y;
	};

	struct Data
	{
		Position pos;
		OffSet offSet;
	};
};

enum HeadTo
{
	H_NORTH,
	H_SOUTH,
	H_EAST,
	H_WEST,
};

struct EntityName
{
	std::string name;
};

struct Position
{
	float x = 0;
	float y = 0;
};

struct Drawing
{
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int grhIndex = 0;
	std::string path;
};

struct Heading
{
	HeadTo heading = H_SOUTH;
};

struct RelativePosition
{
	float x;
	float y;
	float speed;
};

struct Vertices
{
	sf::VertexArray vertexArray;
	sf::Texture texture;
};

enum Component
{
	COMPONENT_NONE = 0,
	COMPONENT_POSITION = 1 << 0,
	COMPONENT_DRAWING = 1 << 1,
	COMPONENT_HEADING = 1 << 2,
	COMPONENT_LAYER1 = 1 << 3,
	COMPONENT_RELATIVE_POSITION = 1 << 4,
	COMPONENT_VERTICES = 1 << 5,
	COMPONENT_HEAD = 1 << 6,
	COMPONENT_BODY = 1 << 7,
};

enum EntityComponents
{
	Body = COMPONENT_VERTICES | COMPONENT_RELATIVE_POSITION | COMPONENT_HEADING | COMPONENT_BODY,
	FirstLayer = COMPONENT_VERTICES,
	Spell = COMPONENT_VERTICES | COMPONENT_RELATIVE_POSITION,
	Head = COMPONENT_VERTICES | COMPONENT_RELATIVE_POSITION | COMPONENT_HEADING | COMPONENT_HEAD,
};