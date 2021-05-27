#pragma once
#include <fbxsdk.h>
#include <iostream>
#include <stack>

class Checks {
private:
	//Check Names utils
	bool badName = false, goodName = true;
	std::stack<std::string> badNamesStack;
	int numTabs = 0;

public:
	bool checkAttributes(FbxNode* node);
	void checkScaling(FbxNode* node);
	void checkTranslation(FbxNode* node);
	void checkRotation(FbxNode* node);
	void checkName(const char* node);
	void checkNgons(FbxNode* node);
	void completeCheck(FbxScene* scene);

private:
	void processNode(FbxNode* node);
	void printTabs();
};

