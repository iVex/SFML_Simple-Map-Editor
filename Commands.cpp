#include "Commands.h"

extern sf::RenderWindow App;
extern Map map;
extern bool dispBorders;

Commands::Commands()
{
	this->drawHelp();
}

void Commands::execute(std::string command)
{
	if (command == "exit") // Exit the App, and the thread
	{
		std::exit(0);
		App.close();
	}
	else if (command == "save" || command == "export") // Save the map on a .txt file, in the map/ folder
	{
		//std::cout << map.export() << std::endl;
		std::string filename;
		std::cout << "Name of the file (no extension): ";
		std::cin >> filename;
		#if defined _MSC_VER
			_mkdir(("map/" + filename).c_str());
		#elif defined __GNUC__
			mkdir(("map/" + filename).c_str(), 0777);
		#endif
		filename = "map/" + filename + "/" + "level.txt";
		std::ofstream file(filename, std::ios::trunc);
		if (file)
		{
			file << map.exportM() << std::endl;
		}
	}
	else if (command == "open") // Open a map on a .txt file, in the map/ folder
	{
		this->getFiles();
		std::string filename;
		std::cout << "Name of the file (no extension): ";
		std::cin >> filename;
		filename = "map/" + filename + "/" + "level.txt";
		std::ifstream file(filename);
		if (file)
		{
			std::string line, sizes;
			std::string content;
			int size[3];

			std::getline(file, sizes);
			std::stringstream ss(sizes);
			for (int i = 0; std::getline(ss, sizes, ','); i++)
			{
				size[i] = stoi(sizes);
			}
			
			while (std::getline(file, line))
			{
				content += line;
			}

			map.import(content, size);
		}
	}
	else if (command == "border") // Enable or Disable the borders on the map (change the dispBorders value in main.cpp)
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
	else if (command == "clear") // Clear the map (with confirmation)
	{
		std::string answer;
		std::cout << "Sure (y/n): ";
		std::cin >> answer;
		if (answer=="y" || answer=="Y")
		{
			map.clear();
		}
	}
	else if (command == "help") // Draw the Help
	{
		this->drawHelp();
	}
	else if (command == "yeah") // Working on a settings parser
	{
		settings settings("settings.txt");
		std::string key;
		std::string type;

		std::cout << "Key: ";
		std::cin >> key;
		std::cout << "Type: ";
		std::cin >> type;
		if (type=="string")
		{
			std::cout << settings.getValue(key) << std::endl;
		}
		else if (type == "int")
		{
			std::cout << settings.getValue(key) << std::endl;
		}
	}
	else // If any of the previous commands isn't executed, draw this and the help
	{
		std::cout << "Unknown command...\n" << std::endl;
		this->drawHelp();
	}
}

// Draw the Help, at object declaration, and when the command "help" is called
void Commands::drawHelp()
{
	std::cout << "Help:\n	No arguments needed\n	save/export : Save the map in the map folder.\n	open : Open a map in the map folder." << std::endl;
	std::cout << "	border : Enable or Disable the borders." << std::endl;
	std::cout << "	clear : Erase all the map." << std::endl;
	std::cout << "	exit : Quit this program and the editor." << std::endl;
	std::cout << std::endl;
}

// Display all the files in "gamepath/map/"
void Commands::getFiles()
{
	// dirent.h is used in this function and works fine
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("map/")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
}
