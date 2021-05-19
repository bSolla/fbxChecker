#pragma once
#include <iostream>
#include <fbxsdk.h>


class Reader
{
public:
	Reader();
	~Reader();

	bool correctFile(const char* filenmame);

	void printNodesScene();
private:
	void PrintNode(FbxNode* pNode);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	void PrintTabs();

	int numTabs = 0;
	FbxManager* lSdkManager;
	FbxImporter* lImporter;
	FbxScene* lScene;
};

