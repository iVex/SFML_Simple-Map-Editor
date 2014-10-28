#ifndef SETTINGS_H
#define SETTINGS_H
#include <iostream>
#include <fstream>
#include <sstream>

// Parser tests
class settings
{
public:
	settings();
	settings(std::string filename);
	~settings();
    void loadFile(std::string filename);
    std::string getValue(std::string key);
private:
    std::string fileS;
    std::string type;
};

#endif