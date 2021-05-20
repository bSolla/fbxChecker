#include "Menu.h"

#include <filesystem>
#include <stack>
//C++17
namespace fs = std::filesystem;

Menu::Menu()
{
	r = new Reader();
}

Menu::~Menu()
{
}

void Menu::init()
{
	//Check the .exe folder and put in a string's stack the fbx object's names
	std::stack<std::string> s;
	std::cout << "		-FBX ANALYZER-\n";
	for (const auto& entry : fs::directory_iterator(fs::current_path().root_name())) {
		if (entry.path().extension().string() == ".fbx")
		{
			s.push(entry.path().filename().string());
		}
	}

	//parameters only for the loading graphic interface
	float percent = 50.0f / s.size(),
		loaded = 0;
	std::string percentStr = "",
		emptyStr = "";

	//go through the stack
	while (!s.empty())
	{
		//things for the render
		loaded += percent;
		std::cout << "\n------------------------------------------------------\n";
		std::cout << "		" + s.top() + " \n";
		std::cout << "------------------------------------------------------\n ";

		//Reader routine
		if (r->correctFile(s.top().c_str())) {
			r->printNodesScene();
			r->clear();
		}

		//loading interface render
		std::string load = "";
		for (int i = 0; i < 50.0f; i++)
		{
			if (i < loaded)
				load += "/";
			else
				load += " ";
		}
		std::cout << "\nCHEKING: \n[" + load + "] \n\n";
		s.pop();
	}
}
