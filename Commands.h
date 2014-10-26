#ifndef COMMANDS_H
#define COMMANDS_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Map.h"

class Commands
{
public:
	Commands();
	~Commands();
	void execute(std::string command);
	void drawHelp();
};

#endif