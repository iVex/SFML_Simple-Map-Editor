#include "Commands.h"

extern sf::RenderWindow App;
extern Map map;
extern bool dispBorders;

Commands::Commands()
{
	this->drawHelp();
}


Commands::~Commands()
{
}

void Commands::execute(std::string command)
{
	if (command == "exit")
	{
		App.close();
		std::exit(0);
	}
	else if (command == "save" || command == "export")
	{
		//std::cout << map.export() << std::endl;
		std::string filename;
		std::cout << "Name of the file (no extension): ";
		std::cin >> filename;
		filename = "map/" + filename + ".txt";
		std::ofstream file(filename, std::ios::trunc);
		if (file)
		{
			file << map.export() << std::endl;
		}
	}
	else if (command == "open")
	{
		std::string filename;
		std::cout << "Name of the file (no extension): ";
		std::cin >> filename;
		filename = "map/" + filename + ".txt";
		std::ifstream file(filename);
		if (file)
		{
			std::string line;
			std::string content;
			while (std::getline(file, line))
			{
				content += line;
			}

			map.import(content);
		}
	}
	else if (command == "border")
	{
		if (dispBorders)
		{
			dispBorders = false;
			std::cout << "Disabled." << std::endl;
		}
		else
		{
			dispBorders = true;
			std::cout << "Enabled." << std::endl;
		}
	}
	else
	{
		std::cout << "Unknown command... dumbass...\n" << std::endl;
		this->drawHelp();
	}
}

void Commands::drawHelp()
{
	std::cout << "Help:\n	No arguments needed\n	save/export : Save the map in the map folder.\n	open : Open a map in the map folder." << std::endl;
	std::cout << "	border : Enable or Disable the borders." << std::endl;
	std::cout << "	exit : Quit this program and the editor." << std::endl;
	std::cout << std::endl;
}