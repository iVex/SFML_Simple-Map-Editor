#include "Map.h"

extern sf::RenderWindow App;

Map::Map()
{
}

Map::Map(int x, int y, int size)
{
	this->createMap(x, y, size);
}

Map::~Map()
{
}

void Map::createMap(int x, int y, int size)
{
	tileset.setTileset("assets/tileset2.png", size);
	sizeX = x;
	sizeY = y;
	tileSize = size;
	_map.resize(sizeY);
	for (int n = 0; n < _map.size(); n++)
		_map[n].resize(sizeX);

	for (int i = 0; i < sizeY; i++)
	{
		for (int n = 0; n < sizeX; n++)
		{
			_map[i][n] = 0;
		}
	}

	barsV.resize(sizeY);
	for (int w = 0; w < barsV.size(); w++)
		barsV[w].resize(sizeX);

	barsH.resize(sizeY);
	for (int w = 0; w < barsV.size(); w++)
		barsH[w].resize(sizeX);

	for (int i = 0; i < sizeY; i++)
	{
		for (int n = 0; n < sizeX; n++)
		{
			barsV[i][n].setSize(sf::Vector2f(1, tileSize));
			barsV[i][n].setPosition((float)n * tileSize, (float)i * tileSize);
			barsV[i][n].setFillColor(sf::Color::White);
			barsH[i][n].setSize(sf::Vector2f(tileSize, 1));
			barsH[i][n].setPosition((float)n * tileSize, (float)i * tileSize);
			barsH[i][n].setFillColor(sf::Color::White);
		}
	}
}

void Map::drawBorder()
{
	for (int i = 0; i < barsV.size(); i++)
	{
		for (int n = 0; n < barsV[i].size(); n++)
		{
			App.draw(barsV[i][n]);
		}
	}
	for (int i = 0; i < barsH.size(); i++)
	{
		for (int n = 0; n < barsH[i].size(); n++)
		{
			App.draw(barsH[i][n]);
		}
	}
}

void Map::drawMap()
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int n = 0; n < _map[i].size(); n++)
		{
			if (_map[i][n]!=0)
			{
				tileset.Draw(n, i, _map[i][n]);
			}
		}
	}
}

int Map::getTiles()
{
	return tileset.getNb()-1;
}

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

std::string Map::export()
{
	std::string exported;
	for (int i = 0; i < _map.size(); i++)
	{
		for (int n = 0; n < _map[i].size(); n++)
		{
			exported += std::to_string(_map[i][n]) + ",";
		}
		exported += "\n";
	}
	return exported;
}

void Map::import(std::string content)
{
	std::stringstream ss(content);
	std::string word;
	int i = 0;
	for (int i = 0; i < _map.size(); i++)
	{
		for (int n = 0; n < _map[i].size(); n++)
		{
			std::getline(ss, word, ',');
			_map[i][n] = std::stoi(word);
			std::cout << "[" << i << "][" << n << "]: " << std::stoi(word) << std::endl;
		}
	}
}