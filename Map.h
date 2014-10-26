#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "Tile.h"

class Map
{
public:
	Map();
	Map(int x, int y, int size);
	~Map();
	void createMap(int x, int y, int size);
	void drawBorder();
	void drawMap();
	void changeTile(int posWheel);
	int getTiles();
	std::string export();
	void import(std::string content);
private:
	std::vector<std::vector<int>> _map;
	int sizeX;
	int sizeY;
	int tileSize;
	std::vector<std::vector<sf::RectangleShape>> barsV;
	std::vector<std::vector<sf::RectangleShape>> barsH;
	Tile tileset;
};

#endif