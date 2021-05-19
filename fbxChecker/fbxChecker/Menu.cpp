#include "Menu.h"

Menu::Menu()
{
	r = new Reader();
}

Menu::~Menu()
{
}

void Menu::init()
{
	printf("Analizador de archivos FBX \n");
	printf("Introduzca el nombre del archivo:\n");
	std::cin >> read;
	filename = read.c_str();
	while (!r->correctFile(filename))
	{
		std::cin >> read;
		filename = read.c_str();
	}
	r->printNodesScene();
}
