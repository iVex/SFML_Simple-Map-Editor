#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

// Class sprite, easier way to load and manage a sprite. Unused at the moment.
class Sprite
{
public:
	Sprite();
	Sprite(std::string filename, std::map<std::string, int> settings);
	~Sprite();
	void setTexture(std::string filename, std::map<std::string, int> settings);
	void Draw();
private:
	std::string path;
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif