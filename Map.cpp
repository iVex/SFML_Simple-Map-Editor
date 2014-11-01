#include "Map.h"

extern sf::RenderWindow App;

using namespace std;

Map::Map()
{
}

Map::Map(int x, int y, int size, std::string tilesetFile, int nbPlans)
{
	this->createMap(x, y, size, tilesetFile, nbPlans);
}

Map::~Map()
{
}

void Map::createMap(int x, int y, int size, std::string tilesetFile, int nbPlans)
{
	tilename = tilesetFile;
	// Open the tileset
	tileset.setTileset(tilesetFile, size);
	sizeX = x;
	sizeY = y;
	tileSize = size;
	plansNb = nbPlans;

	// Resizing the _map vector to the size of the Map
	_map.resize(plansNb);
	for (size_t n = 0; n < _map.size(); n++)
	{
		_map[n].resize(sizeY);
		for (size_t i = 0; i < _map[n].size(); i++)
		{
			_map[n][i].resize(sizeX);
		}
	}
	
	// Setting every case to be empty (item: 0)
	for (int z = 0; z < plansNb; z++)
	{
		for (int i = 0; i < sizeY; i++)
		{
			for (int n = 0; n < sizeX; n++)
			{
				_map[z][i][n] = (-1);
			}
		}
	}
	
	_map[0][0][sizeX-1] = 1;

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
	for (int z = 0; z < plansNb; z++)
	{
		for (size_t i = 0; i < _map[z].size(); i++)
		{
			for (size_t n = 0; n < _map[z][i].size(); n++)
			{
				if (_map[z][i][n] != (-1))
				{
					tileset.Draw(n, i, _map[z][i][n]);
				}
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
void Map::changeTile(int posWheel, sf::Vector2f posMouse, int plan)
{
	tileset.DrawMouse(posWheel, posMouse);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posMouse.x <= tileSize*sizeX && (posMouse.y <= tileSize*sizeY) && posMouse.x >= 0 && posMouse.y >= 0)
	{
		_map[plan][(int)posMouse.y / tileSize][(int)posMouse.x / tileSize] = posWheel;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && posMouse.x <= tileSize*sizeX && (posMouse.y <= tileSize*sizeY) && posMouse.x >= 0 && posMouse.y >= 0)
	{
		_map[plan][(int)posMouse.y / tileSize][(int)posMouse.x / tileSize] = (-1);
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
	exported += std::to_string(plansNb) + ", " + std::to_string(sizeX) + "," + std::to_string(sizeY)+"\n";
	for (int z = 0; z < plansNb; z++)
	{
		for (size_t i = 0; i < _map[z].size(); i++)
		{
			for (size_t n = 0; n < _map[z][i].size(); n++)
			{
				exported += std::to_string(_map[z][i][n]) + ","; // Linux users: have to use -std=c++0x
			}
			exported += "\n";
		}
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
void Map::import(std::string content, int size[3])
{
	std::stringstream ss(content);
	std::string word;
	if (size[0]==plansNb && size[1]==sizeX && size[2]==sizeY)
	{
		for (int z = 0; z < plansNb; z++)
		{
			for (size_t i = 0; i < _map[z].size(); i++)
			{
				for (size_t n = 0; n < _map[z][i].size(); n++)
				{
					std::getline(ss, word, ',');
					_map[z][i][n] = stoi(word);
				}
			}
		}	
	}
	else if (size[1]<=sizeY)
	{
		for (int i = 0; i < size[2]; i++)
		{
			for (int n = 0; n < size[1]; n++)
			{
				std::getline(ss, word, ',');
				_map[0][i][n] = stoi(word);
			}
		}
		for (int z = 0; z < plansNb; z++)
		{
			for (size_t i = 0; i < _map[z].size(); i++)
			{
				for (size_t n = 0; n < _map[z][i].size(); n++)
				{
					std::getline(ss, word, ',');
					_map[z][i][n] = stoi(word);
				}
			}
		}
	}
	else
	{
		std::cout << "Wrong size. Need: " << size[0] << "x" << size[1] << "x" << size[2] << std::endl;

	}
	
}

// Destroy every items (with a confirmation in the commands class)
void Map::clear()
{
	for (int z = 0; z < plansNb; z++)
	{
		for (size_t i = 0; i < _map[z].size(); i++)
		{
			for (size_t n = 0; n < _map[z][i].size(); n++)
			{
				_map[z][i][n] = (-1);
			}
		}
	}
}