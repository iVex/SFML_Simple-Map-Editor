#include "Player.h"


Player::Player()
{
}

Player::Player(std::string filename, std::map<std::string, int> settings)
{
	this->setTexture(filename, settings);
}

Player::~Player()
{
}

void Player::setTexture(std::string filename, std::map<std::string, int> settings)
{
	playerSprite.setTexture(filename, settings);
}

void Player::Draw()
{
	playerSprite.Draw();
}
