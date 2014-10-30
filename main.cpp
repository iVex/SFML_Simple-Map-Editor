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
bool dispBorders=false;

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
	int mapX = 100;
	int mapY = 20;
	std::cout << "height: ";
	std::cin >> mapY;

	App.create(sf::VideoMode(20*tileSize, mapY*tileSize), "Editor");
	map.createMap(mapX, mapY, tileSize, "assets/bricks.png");

	sf::View view(sf::Vector2f((20 * (float)tileSize)/2, (mapY*(float)tileSize)/2), sf::Vector2f(20 * (float)tileSize, mapY * (float)tileSize));
	float centerX = (20 * (float)tileSize) / 2, centerY = ((float)mapY*(float)tileSize) / 2, zoom = 1;

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
				posWheel -= (int)event.mouseWheel.delta;
				if (posWheel>map.getTiles())
				{
					posWheel = 0;
				}
				else if (posWheel < 0)
				{
					posWheel = map.getTiles();
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && centerX>320)
			centerX -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && centerX<2880)
			centerX += 1;


		sf::Vector2f posMouse = App.mapPixelToCoords(sf::Mouse::getPosition(App));

		view.setCenter(sf::Vector2f(centerX, centerY));
		// Applying the view
		App.setView(view);

		// Background color
		App.clear(sf::Color(25, 120, 130));
		// Drawing the map, the item selected, and the borders (if dispBorders==true)
		map.drawMap();
		map.changeTile(posWheel, posMouse);
		if (dispBorders)
			map.drawBorder();

		// Displays the things
		App.display();
	}

	return 0;
}