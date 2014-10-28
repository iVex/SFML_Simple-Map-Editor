#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Commands.h"

const int tileSize = 32;

// Window and map, globals, to be accessed by other files
sf::RenderWindow App;
Map map;
bool dispBorders=true;

// Thread executing commands (commands.h & commands.cpp) 
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
	/* Asking for the size */
	int mapX = 20;
	int mapY = 20;
	std::cout << "X: ";
	std::cin >> mapX;
	std::cout << "Y: ";
	std::cin >> mapY;

	App.create(sf::VideoMode(mapX*tileSize, mapY*tileSize), "Editor");
	map.createMap(mapX, mapY, tileSize, "assets/tilesss.png");

	// posWheel -> item selected on the mouse scroll wheel
	int posWheel = 2;

	// Launching the thread
	sf::Thread thread(&ask);
	thread.launch();

	// Main loop (SFML App)
	while (App.isOpen())
	{
		// Event "manager"
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				App.close();
				thread.terminate();
				std::exit(0);
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

		// Background color
		App.clear(sf::Color(0, 170, 170, 255));
		// Drawing the map, the item selected, and the borders (if dispBorders==true)
		map.drawMap();
		map.changeTile(posWheel);
		if (dispBorders)
			map.drawBorder();

		// Displays the things
		App.display();
	}

	return 0;
}