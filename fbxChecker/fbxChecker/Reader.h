#pragma once
#include <iostream>
#include "Checks.h"

class Reader
{
private:
	int numTabs = 0;
	FbxManager* _sdkManager;
	FbxImporter* _importer;
	FbxScene* _scene;

public:
	Reader();
	~Reader();

	bool correctFile(const char* filenmame);

	void processScene();

	//clean and reset the scene
	void clear();
};

