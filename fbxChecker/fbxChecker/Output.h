#pragma once
#include <iostream>

class Output
{
public:
    /**
    Put the init text in the string

    */
    static void init();

    /**
    Write the fbx init text

    @param fbxName (std::string) name of the fbx that will be checked
    */
    static void newFbx(std::string fbxName);

    /**
    Write the fbx problem text
    @param problemLvl (int) 1 = Warning / 2 = Need To Fix
    */
    static void newFbxProblem(int problemLvl, std::string message);

    /**
    End the Fbx <div>

    */
    static void endFbx();

    /**
    Write the final html

    */
    static void end();

private:

    static int warnings, needToFixes, fbxNumber;

    static std::string 
        actualFile, problemsInfo,
        initText ,
        time_Init,
        span_Finish,
        names_Init,
        name_Init,
        name_Finish,
        body_Init,
        warning,
        needToFix,
        succes,
        numberSpan,
        div_Finish,
        endFile;
};

