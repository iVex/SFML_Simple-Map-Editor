#include "Sprite.h"

extern sf::RenderWindow App;

Sprite::Sprite()
{
}

Sprite::Sprite(std::string filename, std::map<std::string, int> settings)
{
	this->setTexture(filename, settings);
}

Sprite::~Sprite()
{
}

// Load the texture, the settings (in a std::map)
void Sprite::setTexture(std::string filename, std::map<std::string, int> settings)
{
	if (!texture.loadFromFile(filename))
	{
		std::ofstream log("crash_dump.txt");
		if (log)
		{
			log << "Can't load texture. ERR_FILE: " << filename << std::endl;
		}
		else
		{
			std::cout << "Nope, log won't create..." << std::endl;
		}
	}
	else
	{
		if (settings["smooth"] == 1)
			texture.setSmooth(true);
		else
			texture.setSmooth(false);
		sprite.setTexture(texture);
		if (settings.find("posX") == settings.end() && settings.find("posY") == settings.end())
			std::cout << "no." << std::endl;
		else
			sprite.setPosition((float)settings["posX"], (float)settings["posY"]);
	}
}

void Sprite::Draw()
{
	App.draw(sprite);
}