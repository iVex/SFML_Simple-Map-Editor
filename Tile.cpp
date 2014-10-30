#include "Tile.h"

extern sf::RenderWindow App;

Tile::Tile()
{
}

Tile::Tile(std::string tileset, int size)
{
	this->setTileset(tileset, size);
}

void Tile::setTileset(std::string tileset, int size)
{
	sizeTile = size;
	if (!textureTile.loadFromFile(tileset)){	
	}
	else
	{
		// Resize the tiles vector (texture size / tile size)
		tiles.resize(textureTile.getSize().y/sizeTile);
		for (int w = 0; w < tiles.size(); w++)
			tiles[w].resize(textureTile.getSize().x / sizeTile);

		// Add a number to the tiles
		int z = 0;
		for (int i = 0; i < textureTile.getSize().y/sizeTile; i++)
		{
			for (int n = 0; n < textureTile.getSize().x / sizeTile; n++)
			{
				tiles[i][n] = z;
				z += 1;
			}
		}
		maxTiles = z;
	}
}

// Return the number of tiles (used in map.cpp)
int Tile::getNb()
{
	return maxTiles;
}

Tile::~Tile()
{
}

void Tile::Draw(int x, int y, int nb)
{
	// Create a temporary sprite
	sf::Sprite temp;
	// Add the all texture to the sprite
	temp.setTexture(textureTile);
	sf::IntRect tRect;

	// Search for nb in the tiles vector
	typedef std::vector< std::vector<int> >::iterator iter;
	for (iter it = tiles.begin(), end = tiles.end(); it != end; ++it)
	{
		typedef std::vector<int>::iterator iter2;
		iter2 found = std::find((*it).begin(), (*it).end(), nb);
		// if the item is found:
		if (found != it->end())
		{
			// Resize the texture
			tRect.left = (found - (*it).begin())*sizeTile;
			tRect.top = (it - tiles.begin())*sizeTile;
			tRect.width = sizeTile;	tRect.height = sizeTile;
			temp.setTextureRect(tRect);
			temp.setPosition(x*sizeTile, y*sizeTile);
			// Draw the sprite on the screen, at the chosen position
			App.draw(temp);
			break;
		}
	}
}

// Same as this->Draw(), unless this time, it draws it on the mouse pointer, with the sprite origin = (tile size / 2, tile size / 2)
void Tile::DrawMouse(int nb, sf::Vector2f posMouse)
{
	sf::Sprite temp;
	temp.setTexture(textureTile);
	sf::IntRect tRect;
	typedef std::vector< std::vector<int> >::iterator iter;
	for (iter it = tiles.begin(), end = tiles.end(); it != end; ++it)
	{
		typedef std::vector<int>::iterator iter2;
		iter2 found = std::find((*it).begin(), (*it).end(), nb);
		if (found != it->end())
		{
			tRect.left = (found - (*it).begin())*sizeTile;
			tRect.top = (it - tiles.begin())*sizeTile;
			tRect.width = sizeTile;	tRect.height = sizeTile;
			temp.setTextureRect(tRect);
			temp.setOrigin(sizeTile / 2, sizeTile / 2);
			temp.setPosition(posMouse.x, posMouse.y);
			App.draw(temp);
			break;
		}
	}
}