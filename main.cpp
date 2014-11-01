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
	int mapX = 200;
	int mapY = 100;
	
	App.create(sf::VideoMode(20*tileSize, 20*tileSize), "Editor");
	map.createMap(mapX, mapY, tileSize, "assets/test_foreground.png", 3);

	sf::View view(sf::Vector2f((20 * (float)tileSize)/2, (20*(float)tileSize)/2), sf::Vector2f(20 * (float)tileSize, 20 * (float)tileSize));
	float centerX = (20 * (float)tileSize) / 2, centerY = ((float)20*(float)tileSize) / 2, zoom = 1;

	// posWheel -> item selected on the mouse scroll wheel
	int posWheel = 2;
	int plan = 0;
	// Launching the thread
	sf::Thread thread(&ask);
	thread.launch();
	sf::Font font;
	font.loadFromFile("assets/font.ttf");
	sf::Text a_plan;
	a_plan.setFont(font);

	float speed = 300;

	sf::Clock clock;

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
				//thread.terminate();
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
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A)
				{
					plan = 0;
				}
				if (event.key.code == sf::Keyboard::Z)
				{
					plan = 1;
				}
				if (event.key.code == sf::Keyboard::E)
				{
					plan = 2;
				}
			}
		}

		float T = clock.getElapsedTime().asSeconds();
		clock.restart();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && centerX>320)
			centerX -= speed * T;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && centerX<2880)
			centerX += speed * T;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && centerY>320)
			centerY -= speed * T;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && centerY<2880)
			centerY += speed * T;

		a_plan.setString(std::to_string(plan));


		sf::Vector2f posMouse = App.mapPixelToCoords(sf::Mouse::getPosition(App));

		view.setCenter(sf::Vector2f(centerX, centerY));
		// Applying the view
		App.setView(view);

		a_plan.setPosition(App.getSize().x / 2 + centerX - 20, centerY - App.getSize().x / 2);

		// Background color
		App.clear(sf::Color(25, 120, 130));

		// Drawing the map, the item selected, and the borders (if dispBorders==true)
		map.drawMap();
		map.changeTile(posWheel, posMouse, plan);
		if (dispBorders)
			map.drawBorder();

		App.draw(a_plan);
		// Displays the things
		App.display();
	}

	return 0;
}