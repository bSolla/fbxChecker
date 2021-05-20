#include "Reader.h"
#include <iostream>

FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) {
    switch (type) {
    case FbxNodeAttribute::eUnknown: return "unidentified";
    case FbxNodeAttribute::eNull: return "null";
    case FbxNodeAttribute::eMarker: return "marker";
    case FbxNodeAttribute::eSkeleton: return "skeleton";
    case FbxNodeAttribute::eMesh: return "mesh";
    case FbxNodeAttribute::eNurbs: return "nurbs";
    case FbxNodeAttribute::ePatch: return "patch";
    case FbxNodeAttribute::eCamera: return "camera";
    case FbxNodeAttribute::eCameraStereo: return "stereo";
    case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
    case FbxNodeAttribute::eLight: return "light";
    case FbxNodeAttribute::eOpticalReference: return "optical reference";
    case FbxNodeAttribute::eOpticalMarker: return "marker";
    case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
    case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
    case FbxNodeAttribute::eBoundary: return "boundary";
    case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
    case FbxNodeAttribute::eShape: return "shape";
    case FbxNodeAttribute::eLODGroup: return "lodgroup";
    case FbxNodeAttribute::eSubDiv: return "subdiv";
    default: return "unknown";
    }
}

Reader::Reader()
{   
    lSdkManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);
    lImporter = FbxImporter::Create(lSdkManager, "");
}

Reader::~Reader()
{
}

bool Reader::correctFile(const char* filenmame)
{
    if (!lImporter->Initialize(filenmame, -1, lSdkManager->GetIOSettings())) {
        printf("Call to FbxImporter::Initialize() failed.\n");
        printf("Archivo no encotrado o nombre incorrecto\n");
        printf("Introduzca nombre valido:\n");
        return false;
    }
    else
    {
        lScene = FbxScene::Create(lSdkManager, "myScene");
        lImporter->Import(lScene);
        lImporter->Destroy();
        return true;
    }
}
void Reader::printNodesScene()
{
    FbxNode* lRootNode = lScene->GetRootNode();
    if (lRootNode) {
        for (int i = 0; i < lRootNode->GetChildCount(); i++) {
            PrintNode(lRootNode->GetChild(i));
            checkScaling(lRootNode->GetChild(i));
        }
    }
}

void Reader::checkScaling(FbxNode* pNode)
{
    const char* nodeName = pNode->GetName();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // Check if the scale is equal in all axis
    if (scaling[0] == scaling[1] == scaling[2]) {

        // Scale is equal to 1
        if (scaling[0] == 1 && scaling[1] == 1 && scaling[2] == 1) {
            std::cout << nodeName << ":\tOK\n";
        }
        else {
            std::cout << nodeName << ":\tWarning: Scale is equal in all axis but differs from unit\n";
            return;
        }
    }
    else
    {
        std::cout << nodeName << ":\tNeeds Fixing: Scale is different in axis\n";
        return;
    }


    // Recursively checks all childs scaling
    for (int i = 0; i < pNode->GetChildCount(); i++) {
        checkScaling(pNode->GetChild(i));
    }

}

void Reader::PrintNode(FbxNode* pNode)
{
    PrintTabs();
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get();
    FbxDouble3 rotation = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
        nodeName,
        translation[0], translation[1], translation[2],
        rotation[0], rotation[1], rotation[2],
        scaling[0], scaling[1], scaling[2]
    );
  
    numTabs++;

    for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
        PrintAttribute(pNode->GetNodeAttributeByIndex(i));

    for (int j = 0; j < pNode->GetChildCount(); j++)
        PrintNode(pNode->GetChild(j));

    numTabs--;
    PrintTabs();
    printf("</node>\n");
}

void Reader::PrintAttribute(FbxNodeAttribute* pAttribute)
{
    if (!pAttribute) return;

    FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
    FbxString attrName = pAttribute->GetName();
    PrintTabs();
    
    printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());

    if (typeName =="camera" || typeName == "light")
    {
        printf("Needs Fixing\n");
        printf("\n");
    
    }
}

void Reader::PrintTabs()
{
    for (int i = 0; i < numTabs; i++)
        printf("\t");
}


