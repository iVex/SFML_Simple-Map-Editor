#include "Map.h"

extern sf::RenderWindow App;

using namespace std;

Map::Map()
{
}

Map::Map(int x, int y, int size, std::string tilesetFile)
{
	this->createMap(x, y, size, tilesetFile);
}

Map::~Map()
{
}

void Map::createMap(int x, int y, int size, std::string tilesetFile)
{
	tilename = tilesetFile;
	// Open the tileset
	tileset.setTileset(tilesetFile, size);
	sizeX = x;
	sizeY = y;
	tileSize = size;

	// Resizing the _map vector to the size of the Map
	_map.resize(sizeY);
	for (size_t n = 0; n < _map.size(); n++)
		_map[n].resize(sizeX);

	// Setting every case to be empty (item: 0)
	for (int i = 0; i < sizeY; i++)
	{
		for (int n = 0; n < sizeX; n++)
		{
			_map[i][n] = 0;
		}
	}

	// Creating the borders vectors
	barsV.resize(sizeY);
	for (size_t w = 0; w < barsV.size(); w++)
		barsV[w].resize(sizeX);

	barsH.resize(sizeY);
	for (size_t w = 0; w < barsV.size(); w++)
		barsH[w].resize(sizeX);

	// Graphic settings for the bars.
	for (int i = 0; i < sizeY; i++)
	{
		for (int n = 0; n < sizeX; n++)
		{
			barsV[i][n].setSize(sf::Vector2f(1.0f, (float)tileSize));
			barsV[i][n].setPosition((float)n * tileSize, (float)i * tileSize);
			barsV[i][n].setFillColor(sf::Color::White);
			barsH[i][n].setSize(sf::Vector2f((float)tileSize, 1.0f));
			barsH[i][n].setPosition((float)n * tileSize, (float)i * tileSize);
			barsH[i][n].setFillColor(sf::Color::White);
		}
	}
}

// This will only draw borders
void Map::drawBorder()
{
	for (size_t i = 0; i < barsV.size(); i++)
	{
		for (size_t n = 0; n < barsV[i].size(); n++)
		{
			App.draw(barsV[i][n]);
		}
	}
	for (size_t i = 0; i < barsH.size(); i++)
	{
		for (size_t n = 0; n < barsH[i].size(); n++)
		{
			App.draw(barsH[i][n]);
		}
	}
}

// This will only draw the items installed
void Map::drawMap()
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t n = 0; n < _map[i].size(); n++)
		{
			if (_map[i][n]!=0)
			{
				tileset.Draw(n, i, _map[i][n]);
			}
		}
	}
}

// Get the number of tiles (Used in main.cpp for the wheel selection of the item)
int Map::getTiles()
{
	return tileset.getNb()-1;
}

// Update the _map vector with the item selected (used in main.cpp)
void Map::changeTile(int posWheel)
{
	tileset.DrawMouse(posWheel);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(App).x <= tileSize*sizeX && (sf::Mouse::getPosition(App).y <= tileSize*sizeY) && sf::Mouse::getPosition(App).x >= 0 && sf::Mouse::getPosition(App).y >= 0)
	{
		_map[(int)sf::Mouse::getPosition(App).y / tileSize][(int)sf::Mouse::getPosition(App).x / tileSize] = posWheel;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Mouse::getPosition(App).x <= tileSize*sizeX && (sf::Mouse::getPosition(App).y <= tileSize*sizeY) && sf::Mouse::getPosition(App).x >= 0 && sf::Mouse::getPosition(App).y >= 0)
	{
		_map[(int)sf::Mouse::getPosition(App).y / tileSize][(int)sf::Mouse::getPosition(App).x / tileSize] = 0;
	}
}

/*
	Return a string as:
		_map[0][0], _map[0][1], ... \n
		_map[1][0], _map[1][1], ... \n
		...
*/
std::string Map::exportM()
{
	std::string exported;
	exported += std::to_string(sizeX) + "," + std::to_string(sizeY)+"\n";
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t n = 0; n < _map[i].size(); n++)
		{
			exported += std::to_string(_map[i][n]) + ","; // Linux users: have to use -std=c++0x
		}
		exported += "\n";
	}
	return exported;
}

/*
	Read a string as:
		_map[0][0], _map[0][1], ... \n
		_map[1][0], _map[1][1], ... \n
		...
	and set the values in the _map vector.
*/
void Map::import(std::string content, int size[2])
{
	std::stringstream ss(content);
	std::string word;
	if (size[0]==sizeX && size[1]==sizeY)
	{
		for (size_t i = 0; i < _map.size(); i++)
		{
			for (size_t n = 0; n < _map[i].size(); n++)
			{
				std::getline(ss, word, ',');
				_map[i][n] = stoi(word);
			}
		}
	}
	else
	{
		std::cout << "Wrong size. Need: " << size[0] << "x" << size[1] << std::endl;
	}
	
}

// Destroy every items (with a confirmation in the commands class)
void Map::clear()
{
	for (size_t i = 0; i < _map.size(); i++)
	{
		for (size_t n = 0; n < _map[i].size(); n++)
		{
			_map[i][n] = 0;
		}
	}
}