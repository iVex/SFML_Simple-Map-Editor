#ifndef COMMANDS_H
#define COMMANDS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "dirent.h" // Got on the internet, for linux user, use <dirent.h>
#include "Map.h"
#include "settings.h"

// Allow the secondary thread to run commands, to interact with the main thread.
class Commands
{
public:
	Commands();
	void execute(std::string command);
	void drawHelp();
	void getFiles();
};

#endif