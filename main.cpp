#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "Commands.h"

const int mapX = 20;
const int mapY = 20;
const int tileSize = 32;

// Window and map Creation
sf::RenderWindow App(sf::VideoMode(mapX*tileSize, mapY*tileSize), "Editor");
Map map(mapX, mapY, tileSize, "assets/tilesss.png");
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