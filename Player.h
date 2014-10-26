#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player
{
public:
	Player();
	Player(std::string filename, std::map<std::string, int> settings);
	~Player();
	void setTexture(std::string filename, std::map<std::string, int> settings);
	void Draw();
private:
	Sprite playerSprite;
};

#endif