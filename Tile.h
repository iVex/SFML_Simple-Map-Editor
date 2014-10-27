#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

// Load the tileset, add a number to every case
class Tile
{
public:
	Tile();
	Tile(std::string tileset, int size);
	~Tile();
	void setTileset(std::string tileset, int size);
	void Draw(int x, int y, int nb);
	void DrawMouse(int nb);
	int getNb();
private:
	sf::Texture textureTile;
	int sizeTile;
	std::vector<std::vector<int>> tiles;
	std::vector<std::vector<sf::Sprite>> tileS;
	int maxTiles;
};

#endif