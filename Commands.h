#ifndef COMMANDS_H
#define COMMANDS_H

#if defined _MSC_VER
	#include <direct.h>
	#include "dirent.h" 
#elif defined __GNUC__
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Map.h"

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