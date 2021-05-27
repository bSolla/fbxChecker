#include "Reader.h"
#include <iostream>


Reader::Reader()
{   
    _sdkManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(_sdkManager, IOSROOT);
    _sdkManager->SetIOSettings(ios);
    _importer = FbxImporter::Create(_sdkManager, "");
}

Reader::~Reader()
{
    clear();
}

bool Reader::correctFile(const char* filenmame)
{
    if (!_importer->Initialize(filenmame, -1, _sdkManager->GetIOSettings())) {
        std::cout << "Call to FbxImporter::Initialize() failed.\n";
        std::cout << "File not found or wrong name\n";
        std::cout << "Input a valid name.\n";
        return false;
    }
    else
    {
        _scene = FbxScene::Create(_sdkManager, "myScene");
        _importer->Import(_scene);
        _importer->Destroy();
        return true;
    }
}

void Reader::processScene()
{
    Checks checker;
    checker.completeCheck(_scene);
}

void Reader::clear()
{
    _sdkManager = nullptr;
    _importer = nullptr;
    _scene = nullptr;

    _sdkManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(_sdkManager, IOSROOT);
    _sdkManager->SetIOSettings(ios);
    _importer = FbxImporter::Create(_sdkManager, "");
}


