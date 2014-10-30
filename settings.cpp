#include "settings.h"

settings::settings()
{
}


settings::~settings()
{
}

settings::settings(std::string filename)
{
	this->loadFile(filename);
}

void settings::loadFile(std::string filename)
{
	fileS = filename;
}

std::string settings::getValue(std::string key)
{
	std::ifstream file(fileS);
	if (file)
	{
		std::string table[2];
		std::string words;
		std::getline(file, words);
		std::stringstream ss(words);
		while (getline(ss, words, '='))
		{
			if (words == key)
			{
				getline(ss, words, '='); // Split the string w/ '='
				table[1] = words; // Result (after the '=') [dont work for line>1]
				break;
			}
		}

		return table[1];
	}
	else
	{
		return 0;
	}
}