#pragma once
#include <iostream>

class Output
{
public:

    static void init();

    static void newFbx(std::string fbxName);

    static void newFbxProblem(int problemLvl, std::string message);

    static void endFbx();

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
        endFile,
        date;
};

