#ifndef COMMANDS_H
#define COMMANDS_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "dirent.h"
#include "Map.h"

class Commands
{
public:
	Commands();
	void execute(std::string command);
	void drawHelp();
	void getFiles();
};

#endif