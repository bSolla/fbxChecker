// fbxChecker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fbxsdk.h>

int main()
{
    std::cout << "Hello World!\n";
    const char* lFilename = "sadface.fbx";

    // Initialize the SDK manager. This object handles memory management.
    FbxManager* lSdkManager = FbxManager::Create();

    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create an importer using the SDK manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Use the first argument as the filename for the importer.
    if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) {
        printf("Call to FbxImporter::Initialize() failed.\n");
        printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
        exit(-1);
    }
        // Create a new scene so that it can be populated by the imported file.
        FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

        // Import the contents of the file into the scene.
        lImporter->Import(lScene);

        // The file is imported, so get rid of the importer.
        lImporter->Destroy();
        // Print the nodes of the scene and their attributes recursively.
  // Note that we are not printing the root node because it should
  
  // not contain any attributes.
     
    

}
   
    
