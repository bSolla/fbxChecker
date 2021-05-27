#include "Checks.h"
#include <filesystem>
#include <fstream>

//C++17
namespace fs = std::filesystem;

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


void Checks::checkAttributes(FbxNodeAttribute* pAttribute) {
    if (!pAttribute) return;

    FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
    FbxString attrName = pAttribute->GetName();
    printTabs();

    printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());

    if (typeName == "camera" || typeName == "light") {
        printf("Needs Fixing\n");
        printf("\n");

    }
}

void Checks::checkScaling(FbxNode* pNode) {
    const char* nodeName = pNode->GetName();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // Check if the scale is equal in all axis
    if (scaling[0] == scaling[1] && scaling[0] == scaling[2]) {

        // Scale is equal to 1
        if (scaling[0] == 1 && scaling[1] == 1 && scaling[2] == 1) {
            std::cout << nodeName << ":\tOK\n";
        }
        else {
            std::cout << nodeName << ":\tWarning: Scale is equal in all axis but differs from unit\n";
            return;
        }
    }
    else {
        std::cout << nodeName << ":\tNeeds Fixing: Scale is different in axis\n";
        return;
    }
}

void Checks::checkTranslation(FbxNode* pNode) {
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get();

    if (translation[0] == 0 && translation[1] == 0 && translation[2] == 0) {
        std::cout << nodeName << ":\tOK\n";
    }
    else {
        std::cout << nodeName << ":\tWarning: Translation is not equal to zero= (" << translation[0] << ", " << translation[1] << ", " << translation[2] << ")\n";
    }
}

void Checks::checkRotation(FbxNode* pNode) {
    FbxDouble3 rotation = pNode->LclRotation.Get();
    const char* nodeName = pNode->GetName();

    if (abs(rotation[0] - rotation[1]) < 0.01 && abs(rotation[0] - rotation[2]) < 0.01) {
        std::cout << nodeName << ":\tOK\n";
    }
    else {
        std::cout << nodeName << ":\tWarning: Rotation is different in some axis= (" << rotation[0] << ", " << rotation[1] << ", " << rotation[2] << ")\n";
    }
}


void Checks::checkName(const char* nNode) {
    //We use this as a string because is more easy :D
    std::string name = nNode, util;
    //if the stack is empty read the text and 
    if (badNamesStack.empty()) {
        char textChain[128];
        std::ifstream fe(fs::current_path().root_name().string() + "BadNames.txt");
        if (fe.is_open()) {
            while (!fe.eof()) {
                fe >> util;
                badNamesStack.push(util);
            }
            fe.close();
        }
    }
    //Save the stack in other, we dont need to read the file 
    //more than one time
    std::stack<std::string> saveStack;
    bool actualBadName = false;
    while (!badNamesStack.empty() && !actualBadName) {
        if (name.find(badNamesStack.top()) != std::string::npos) {
            std::cout << name << ":\tWarning: Bad name, please change it \n";
            goodName = false;
            actualBadName = true;
        }
        saveStack.push(badNamesStack.top());
        badNamesStack.pop();
    }
    if (!actualBadName) {
        std::cout << name << ":\tGood name \n";
        badName = false;
    }
    while (!saveStack.empty()) {
        badNamesStack.push(saveStack.top());
        saveStack.pop();
    }
}

void Checks::completeCheck(FbxScene* scene) {
    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode) {

        badName = true;
        goodName = true;

        for (int i = 0; i < rootNode->GetChildCount(); i++) {
            processNode(rootNode->GetChild(i));
        }

        std::cout << "\n-Final name check\n";
        if (badName)
            std::cout << rootNode->GetName() << " child names:\tNeeds Fixing: all the node's names are bad \n";
        else if (goodName)
            std::cout << rootNode->GetName() << " child names:\tOK\n";
        else
            std::cout << rootNode->GetName() << " child names:\tWarning: some names are names are bad \n";
    }
}

void Checks::processNode(FbxNode* node) {
    printTabs();

    const char* nodeName = node->GetName();
    FbxDouble3 translation = node->LclTranslation.Get();
    FbxDouble3 rotation = node->LclRotation.Get();
    FbxDouble3 scaling = node->LclScaling.Get();

    printf("\n<node \nname='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
        nodeName,
        translation[0], translation[1], translation[2],
        rotation[0], rotation[1], rotation[2],
        scaling[0], scaling[1], scaling[2]
    );

    numTabs++;

    std::cout << "\n-Checking Translation\n";
    checkTranslation(node);
    std::cout << "\n-Checking Scale\n";
    checkScaling(node);
    std::cout << "\n-Checking Rotation\n";
    checkRotation(node);
    std::cout << "\n-Checking Name\n";
    checkName(node->GetName());

    for (int j = 0; j < node->GetChildCount(); j++) {
        processNode(node->GetChild(j));
        checkTranslation(node->GetChild(j));
        checkScaling(node->GetChild(j));
        checkRotation(node->GetChild(j));
        checkName(node->GetChild(j)->GetName());
    }

    for (int i = 0; i < node->GetNodeAttributeCount(); i++)
        checkAttributes(node->GetNodeAttributeByIndex(i));

    numTabs--;
    printTabs();

    printf("</node>\n");
}


void Checks::printTabs() {
    for (int i = 0; i < numTabs; i++)
        printf("\t");
}
