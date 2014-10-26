#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Commands.h"

const int mapX = 25;
const int mapY = 20;
const int tileSize = 32;

sf::RenderWindow App(sf::VideoMode(mapX*tileSize, mapY*tileSize), "Editor");
Map map(mapX, mapY, tileSize);
bool dispBorders=true;

void ask()
{
	Commands commands;
	while (true)
	{
		std::string command;
		std::cout << "command> ";
		std::cin >> command;
		commands.execute(command);
	}
}

int main(int argc, char *argv[])
{
	int posWheel = 2;

	sf::Thread thread(&ask);
	thread.launch();

	while (App.isOpen())
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				App.close();
				thread.terminate();
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				posWheel += (int)event.mouseWheel.delta;
				if (posWheel>map.getTiles())
				{
					posWheel = 1;
				}
				else if (posWheel < 1)
				{
					posWheel = map.getTiles();
				}
			}
		}

		App.clear(sf::Color(0, 170, 170, 255));

		map.drawMap();
		map.changeTile(posWheel);
		if (dispBorders)
			map.drawBorder();

		App.display();
	}

	return 0;
}