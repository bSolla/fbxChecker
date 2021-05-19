#pragma once
#include "Reader.h"
#include <iostream>
#include <string>

class Menu
{
public:
	Menu();
	~Menu();
	void init();

private:
	Reader* r;
	std::string read;
	const char* filename;
};
