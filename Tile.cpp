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
		tiles.resize(textureTile.getSize().y/sizeTile);
		for (int w = 0; w < tiles.size(); w++)
			tiles[w].resize(textureTile.getSize().x / sizeTile);

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

int Tile::getNb()
{
	return maxTiles;
}

Tile::~Tile()
{
}

void Tile::Draw(int x, int y, int nb)
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
			/*std::cout << "row " << (it - tiles.begin())
				<< ", col " << (found - (*it).begin()) << '\n';*/
			tRect.left = (found - (*it).begin())*sizeTile;
			tRect.top = (it - tiles.begin())*sizeTile;
			tRect.width = sizeTile;	tRect.height = sizeTile;
			temp.setTextureRect(tRect);
			temp.setPosition(x*sizeTile, y*sizeTile);
			App.draw(temp);
			break;
		}
	}
}

void Tile::DrawMouse(int nb)
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
			temp.setPosition(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
			App.draw(temp);
			break;
		}
	}
}