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

	//clean and reset the scene
	void clear();

private:
	void checkScaling(FbxNode* pNode);
	void checkTranslation(FbxNode* pNode);
	void PrintNode(FbxNode* pNode);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	void PrintTabs();

	int numTabs = 0;
	FbxManager* lSdkManager;
	FbxImporter* lImporter;
	FbxScene* lScene;
};

