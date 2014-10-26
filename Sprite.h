#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

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