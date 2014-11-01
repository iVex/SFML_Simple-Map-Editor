#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "Tile.h"

// Create the map, using the Tile class to Draw tiles on screen
class Map
{
public:
	Map();
	Map(int x, int y, int size, std::string tilesetFile, int nbPlans);
	~Map();
	void createMap(int x, int y, int size, std::string tilesetFile, int nbPlans);
	void drawBorder();
	void drawMap();
	void changeTile(int posWheel, sf::Vector2f posMouse, int plan);
	int getTiles();
	std::string exportM();
	void import(std::string content, int size[2]);
	void clear();
private:
	std::vector< std::vector< std::vector< int > > > _map;
	int sizeX;
	int sizeY;
	int tileSize;
	std::vector< std::vector< sf::RectangleShape > > barsV;
	std::vector< std::vector< sf::RectangleShape > > barsH;
	Tile tileset;
	std::string tilename;
	int plansNb;
};

#endif